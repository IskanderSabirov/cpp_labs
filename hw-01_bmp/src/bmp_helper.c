#include "bmp_helper.h"

static int get_padding(int x) {
    return pixel_size * x + (4 - pixel_size * x % 4) % 4;
}

int load_bmp(bmp_t *bmp, char *file) {

    FILE *f = fopen(file, "rb");

    if (f == NULL) {
        return 1;
    }

    void *dib_header = malloc(sizeof(dib_header_t));
    void *file_header = malloc(sizeof(info_header_t));

    if (file_header == NULL || dib_header == NULL) {
        return 1;
    }


    if (fread(file_header, sizeof(info_header_t), 1, f) == 0) {
        return 1;
    }

    fseek(f, (long) (sizeof(info_header_t)), SEEK_SET);
    if (fread(dib_header, sizeof(dib_header_t), 1, f) == 0) {
        return 1;
    }

    bmp->dib_header = dib_header;
    bmp->file_header = file_header;

    void *data = malloc(bmp->file_header->file_size - bmp->file_header->pixel_offset);

    if (data == NULL) {
        return 1;
    }

    bmp->data = data;

    fseek(f, (long) bmp->file_header->pixel_offset, SEEK_SET);
    fread(data, bmp->dib_header->size_image, 1, f);

    fclose(f);

    return 0;
}

int save_bmp(bmp_t *bmp, char *file) {

    FILE *f = fopen(file, "wb");
    if (f == NULL) {
        return 1;
    }

    if (fwrite(bmp->file_header, sizeof(info_header_t), 1, f) == 0) {
        return 1;
    }

    if (fwrite(bmp->dib_header, sizeof(dib_header_t), 1, f) == 0) {
        return 1;
    }

    if (fwrite(bmp->data, bmp->dib_header->size_image, 1, f) == 0) {
        return 1;
    }

    fclose(f);

    return 0;
}


int crop_bmp(bmp_t *image, int32_t x, int32_t y, int32_t w, int32_t h) {

    char *started_p = image->data;

    int32_t started_len = get_padding(image->dib_header->width);
    int32_t cropped_len = get_padding(w);

    char *new_pixels = (char *) calloc(h, cropped_len);
    if (new_pixels == NULL) {
        return 1;
    }


    /// с учётом хранения строк снизу вверх
    started_p += pixel_size * x + (image->dib_header->height - y - h) * started_len;

    for (int32_t i = 0; i < h; i++) {
        for (int32_t j = 0; j < w; j++) {
            for (int32_t p = 0; p < pixel_size; p++) {
                new_pixels[i * cropped_len + j * pixel_size + p] = started_p[i * started_len + j * pixel_size + p];
            }
        }
    }

    free(image->data);

    image->data = new_pixels;

    image->dib_header->x_per_meter *= (w / image->dib_header->width);
    image->dib_header->y_per_meter *= (h / image->dib_header->height);

    image->dib_header->size_image = cropped_len * h;

    image->file_header->file_size = image->dib_header->size_image + sizeof(dib_header_t) + sizeof(info_header_t);

    image->dib_header->width = w;
    image->dib_header->height = h;

    return 0;
}


int rotate_bmp(bmp_t *bmp) {

    int32_t old_width = get_padding(bmp->dib_header->width);
    int32_t new_width = get_padding(bmp->dib_header->height);

    char *new_pixels = calloc(bmp->dib_header->width, new_width);
    if (new_pixels == NULL) {
        return 1;
    }

    char *new_pos = new_pixels;

    for (int32_t x = 0; x < bmp->dib_header->width; x++) {

        char *cur_pos = bmp->data + pixel_size * (bmp->dib_header->width - x - 1);

        for (int32_t y = 0; y < bmp->dib_header->height; y++) {

            for (int32_t i = 0; i < pixel_size; i++) {
                new_pos[i] = cur_pos[i];
            }

            new_pos += pixel_size;
            cur_pos += old_width;
        }

        new_pos += bmp->dib_header->height % 4;
    }

    free(bmp->data);
    bmp->data = new_pixels;

    int32_t t = bmp->dib_header->width;
    bmp->dib_header->width = bmp->dib_header->height;
    bmp->dib_header->width = t;

    t = bmp->dib_header->x_per_meter;
    bmp->dib_header->x_per_meter = bmp->dib_header->y_per_meter;
    bmp->dib_header->y_per_meter = t;

    bmp->dib_header->size_image = new_width * bmp->dib_header->width;
    bmp->file_header->file_size = bmp->dib_header->size_image + sizeof(info_header_t) + sizeof(dib_header_t);

    return 0;
}

