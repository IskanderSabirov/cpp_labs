#include "bmp_helper.h"
#include <string.h>

void free_bmp(bmp_t *bmp) {
    free(bmp->dib_header);
    free(bmp->file_header);
    free(bmp->data);
}

int main(int argc, char **argv) {

    for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);

    if (argc != 8 || strcmp("crop-rotate", argv[1]) != 0) {
        return 1;
    }

    bmp_t bmp;

    if (load_bmp(&bmp, argv[2])) {
        return 2;
    }

    if (bmp.dib_header->bit_count != 24) {
        return 3;
    }

    int32_t x = atoi(argv[4]);
    int32_t y = atoi(argv[5]);
    int32_t w = atoi(argv[6]);
    int32_t h = atoi(argv[7]);
    int32_t W = bmp.dib_header->width;
    int32_t H = bmp.dib_header->height;

    if ((x < 0) || (y < 0) || (w < 0) || (h < 0) || (w + x > W) || (h + y > H)) {
        return 4;
    }

    if (crop_bmp(&bmp, x, y, w, h)) {
        return 5;
    }

    if (rotate_bmp(&bmp)) {
        return 6;
    }

    if (save_bmp(&bmp, argv[3])) {
        return 7;
    }

    free_bmp(&bmp);

    return 0;
}

