#ifndef LAB_05_C_IO_BMP_HELPER_H
#define LAB_05_C_IO_BMP_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static const int pixel_size = 3;

#pragma pack(push, 2)

/// BMP header
typedef struct bmp_header {
    uint16_t b_type;
    uint32_t file_size;
    uint32_t unused;
    uint32_t pixel_offset;
} info_header_t;

/// DIB header
typedef struct bmp_dib_header {
    uint32_t b_size;
    int32_t width, height;
    uint16_t color_planes, bit_count;
    uint32_t compression, size_image;
    int32_t x_per_meter, y_per_meter;
    uint32_t colors_count, imp_color_counts;
} dib_header_t;

/// bmp file
typedef struct bmp_image {
    info_header_t *file_header;
    dib_header_t *dib_header;
    char *data;
} bmp_t;

#pragma pack(pop)

int load_bmp(bmp_t *bmp, char *file);

int save_bmp(bmp_t *bmp, char *file);

int crop_bmp(bmp_t *image, int32_t x, int32_t y, int32_t w, int32_t h);

int rotate_bmp(bmp_t *bmp);

#endif //LAB_05_C_IO_BMP_HELPER_H
