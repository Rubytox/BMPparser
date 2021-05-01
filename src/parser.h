#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/**
 * The header is of the following format:
 * - 2 bytes(0): magic number ;
 * - 4 bytes(2): size of file in bytes ;
 * - 2 bytes(6): reserved ;
 * - 2 bytes(8): reserved ;
 * - 4 bytes(10): offset of the contents.
 */
typedef struct {
    uint8_t format[2];
    uint8_t size[4];
    uint8_t reserved1[2];
    uint8_t reserved2[2];
    uint8_t contents_offset[4];
} BMP_header;

typedef struct {
    uint8_t header_size[4];
    uint8_t width[4];
    uint8_t height[4];
    uint8_t planes[2];
    uint8_t bits_per_pixel[2];
    uint8_t compression_method[4];
    uint8_t image_size[4];
    uint8_t h_resolution[4];
    uint8_t v_resolution[4];
    uint8_t nb_colors[4];
    uint8_t nb_important_colors[4];
} BITMAPINFOHEADER;

typedef struct {
    BMP_header *bmp_header;
    BITMAPINFOHEADER *dib_header;
} BMP_picture;

BMP_header *extract_BMP_header(FILE *picture);
BITMAPINFOHEADER *extract_DIB_header(FILE *picture);

void print_header(BMP_header *header);
void print_DIB_header(BITMAPINFOHEADER *header);

BMP_picture *parse_picture(const char *path);
void free_picture(BMP_picture **p_picture);
#endif // PARSER_H
