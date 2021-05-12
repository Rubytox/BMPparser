#include "parser.h"

BMP_header *extract_BMP_header(FILE *picture)
{
    BMP_header *ret = calloc(1, sizeof(BMP_header));

    /*
     * It appears it is not really possible to know whether
     * the read worked or not...
     */
    fread(ret, 1, sizeof(BMP_header), picture);

    return ret;
}

BITMAPINFOHEADER *extract_DIB_header(FILE *picture)
{
    BITMAPINFOHEADER *ret = calloc(1, sizeof(BITMAPINFOHEADER));

    fread(ret, 1, sizeof(BITMAPINFOHEADER), picture);

    return ret;
}

int to_int(uint8_t *bytes, int nb_bytes)
{
    int value = 0;
    memcpy(&value, bytes, nb_bytes);
    return value;
}


//returns HEADER_VALID if header is maybe valid, HEADER_INVALID if header is for sure not valid and HEADER_NOT_SUPPORTED if it is not supported
header_validity is_header_valid(BMP_picture *picture){
    // only possibilities for header field are BM/BA/CI/CP/IC/PT
    if (!( (picture->bmp_header->format[0] == 'B' && picture->bmp_header->format[1] == 'M') || 
    (picture->bmp_header->format[0] == 'B' && picture->bmp_header->format[1] == 'A' ) ||  
    (picture->bmp_header->format[0] == 'C' && picture->bmp_header->format[1] == 'I') ||
    (picture->bmp_header->format[0] == 'C' && picture->bmp_header->format[1] == 'P') ||
    (picture->bmp_header->format[0] == 'I' && picture->bmp_header->format[1] == 'C') ||
    (picture->bmp_header->format[0] == 'P' && picture->bmp_header->format[1] == 'T')
    )){
        return HEADER_INVALID;
    }

    // not implemented yet :: to_int(picture->bmp_header->size, 4) needs to be equal to output of "du image -b"

    // only possible header sizes
    int size = to_int(picture->dib_header->header_size, 4);
    if (size == 52 || size == 56 || size == 64){
        return HEADER_NOT_SUPPORTED;
    }

    if (size!= 12  && size!= 16 && size!= 40 && size!= 108 && size!= 124){
        return HEADER_INVALID;
    }
    
    // seems that plantes must always be 1 ??
    if (to_int(picture->dib_header->planes, 2) != 1){
        return HEADER_INVALID;
    }

    // further parsing is allowed
    if (size != 12 && size != 16){

        // number of bits per pixel must be in {1,4,8,16,24,32}
        if( to_int(picture->dib_header->bits_per_pixel, 2) != 1 && 
        to_int(picture->dib_header->bits_per_pixel, 2) != 4 && 
        to_int(picture->dib_header->bits_per_pixel, 2) != 8 &&
        to_int(picture->dib_header->bits_per_pixel, 2) != 16 && 
        to_int(picture->dib_header->bits_per_pixel, 2) != 24 && 
        to_int(picture->dib_header->bits_per_pixel, 2) != 32  ){
            return HEADER_INVALID;
        }

        //check validity of compression method
        int compression_method = to_int(picture->dib_header->compression_method,4);
        if (compression_method < 0 || compression_method >=14){
            return HEADER_INVALID;
        }

        // not finished yet

    }
    return HEADER_VALID;
}


void print_header(BMP_header *header)
{
    if (header == NULL) {
        printf("Header is NULL\n");
        exit(-1);
    }

    printf("Format: %02x %02x\n", header->format[0], header->format[1]);

    printf("Size: %d\n", to_int(header->size, 4));

    printf("Offset: %x\n", to_int(header->contents_offset, 4));
}

void print_DIB_header(BITMAPINFOHEADER *header)
{
    if (header == NULL) {
        printf("Header is NULL\n");
        exit(-1);
    }

    printf("Header size: %d\n", to_int(header->header_size, 4));
    printf("Width: %d\n", to_int(header->width, 4));
    printf("Height: %d\n", to_int(header->height, 4));
    printf("Number of planes: %d\n", to_int(header->planes, 2));
    printf("Bits per pixel: %d\n", to_int(header->bits_per_pixel, 2));
    printf("Image size: %d\n", to_int(header->image_size, 4));
    printf("Horizontal resolution: %d\n", to_int(header->h_resolution, 4));
    printf("Vertical resolution: %d\n", to_int(header->v_resolution, 4));
    printf("Number of colors: %d\n", to_int(header->nb_colors, 4));
    printf("Number of important colors: %d\n", to_int(header->nb_important_colors, 4));

    printf("Compression method: ");
    switch ((compression_methods) to_int(header->compression_method, 4)) {
	case BI_RGB:
        printf("no compression\n");
        break;

	case BI_RLE8:
        printf("RLE 8-bit/pixel\n");
        break;

	case BI_RLE4:
        printf("RLE 4-bit/pixel\n");
        break;

	case BI_BITFIELDS:
        printf("Huffman 1D\n");
        break;

	case BI_JPEG:
        printf("RLE-24\n");
        break;

	case BI_PNG:
        printf("PNG\n");
        break;

	case BI_ALPHABITFIELDS:
        printf("RGBA bit field masks\n");
        break;

	case BI_CMYK:
        printf("no compression (Windows Metafile)\n");
        break;

	case BI_CMYRKLE8:
        printf("RLE 8-bit/pixel (Windows Metafile)\n");
        break;

    case BI_CMYRKLE4:
        printf("RLE 4-bit/pixel (Windows Metafile)\n");
        break;

    }
}

BMP_picture *parse_picture(const char *path)
{
    BMP_picture *ret = calloc(1, sizeof(BMP_picture));

    FILE *picture = fopen(path, "rb");

    ret->bmp_header = extract_BMP_header(picture);
    ret->dib_header = extract_DIB_header(picture);

    fclose(picture);

    return ret;
}

void free_picture(BMP_picture **p_picture)
{
    BMP_picture *element = *p_picture;
    free(element->bmp_header);
    free(element->dib_header);
    free(element);
    *p_picture = NULL;
}
