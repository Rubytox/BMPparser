#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc  != 2) {
        printf("Usage: %s path_to_file\n", argv[0]);
        return -1;
    }

    char *filename = argv[1];
    BMP_picture *picture = parse_picture(filename);
    printf("BMP header\n");
    printf("==========\n");
    print_header(picture->bmp_header);

    printf("\n");
    printf("DIB header\n");
    printf("==========\n");
    print_DIB_header(picture->dib_header);

    printf("Is header valid ? ");
    switch ( is_header_valid(picture)){
        case HEADER_NOT_SUPPORTED : printf("not supported \n"); break;
        case HEADER_INVALID: printf("not valid \n"); break;
        case HEADER_VALID : printf("valid \n"); break;
    }

    free_picture(&picture);

    printf("Value of ptr picture: %p\n", picture);

    return 0;
}
