#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// We'll se if we use this
/*
typedef enum _magic_number {
    BM,
    CI,
    CP,
    IC,
    PT
} magic_number;
*/

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

BMP_header *extract_header(const char *path);
void print_header(BMP_header *header);

char *format_to_string(char format[3]);

#endif // PARSER_H
