#include "parser.h"

BMP_header *extract_header(const char *path)
{
    BMP_header *ret = calloc(1, sizeof(BMP_header));

    FILE *picture = fopen(path, "rb");

    /*
     * It appears it is not really possible to know whether
     * the read worked or not...
     */
    fread(ret, 1, sizeof(BMP_header), picture);

    fclose(picture);

    return ret;
}

void print_header(BMP_header *header)
{
    if (header == NULL) {
        printf("Header is NULL\n");
        exit(-1);
    }

    printf("Format: %02x %02x\n", header->format[0], header->format[1]);

    /**
     * TODO: to check for convert byte array to int
     */
    int size = 0;
    memcpy(&size, header->size, 4);
    printf("Size: %d\n", size);

    int offset = 0;
    memcpy(&offset, header->contents_offset, 4);
    printf("Offset: %x\n", offset);

}
