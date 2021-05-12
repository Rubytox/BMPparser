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


/**
* Depending on "header_size" value, some fields must be ignored.
* For instance, if header_size = 16, every field staring from "compression_method" are not meaningful
* (!) the following headers are not taken into  account :
* *  OS/2 2.x OS22XBITMAPHEADER (header_size = 64)
* * BITMAPV2INFOHEADER, BITMAPV3INFOHEADER because not documented (header_size = 52,56)
*/
typedef struct {
    uint8_t header_size[4];
    uint8_t width[4];
    uint8_t height[4];
    uint8_t planes[2];
    uint8_t bits_per_pixel[2];
    // header size 16 : OS22XBITMAPHEADER
    uint8_t compression_method[4];
    uint8_t image_size[4];
    uint8_t h_resolution[4];
    uint8_t v_resolution[4];
    uint8_t nb_colors[4];
    uint8_t nb_important_colors[4];
    // header size 40 : BITMAPINFOHEADER
    uint8_t red_mask[4];
	uint8_t green_mask[4];
	uint8_t blue_mask[4];
	uint8_t alpha_mask[4];
	uint8_t cs_type[4]; // only 5 values
	uint8_t endpoints[9*4]; 
	uint8_t gamma_red[4];
	uint8_t gamma_green[4];
	uint8_t gamma_blue[4];
    // header size 108 : BITMAPV4HEADER
    uint8_t intent[4]; // only 4 values
    uint8_t profile_data[4];
    uint8_t profile_size[4]; // size in bytes of embedded profile data
    uint8_t reserved[4]; // must be 0
    //header size 124 : BITMAPV5HEADER
} BITMAPINFOHEADER;

typedef struct {
    BMP_header *bmp_header;
    BITMAPINFOHEADER *dib_header;
} BMP_picture;

typedef enum {
    BI_RGB = 0,
    BI_RLE8,
    BI_RLE4,
    BI_BITFIELDS,
    BI_JPEG,
    BI_PNG,
    BI_ALPHABITFIELDS,
    BI_CMYK,
    BI_CMYRKLE8,
    BI_CMYRKLE4
} compression_methods;

typedef enum{
    HEADER_NOT_SUPPORTED,
    HEADER_INVALID,
    HEADER_VALID
} header_validity;

BMP_header *extract_BMP_header(FILE *picture);
BITMAPINFOHEADER *extract_DIB_header(FILE *picture);

void print_header(BMP_header *header);
void print_DIB_header(BITMAPINFOHEADER *header);

BMP_picture *parse_picture(const char *path);
void free_picture(BMP_picture **p_picture);

header_validity is_header_valid(BMP_picture *picture);

#endif // PARSER_H
