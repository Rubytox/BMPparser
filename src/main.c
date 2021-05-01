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
    BMP_header *header = extract_header(filename);
    print_header(header);

    free(header);

    return 0;
}
