#include "bmp.h"
#include "image.h"
#include "rotate.h"
#include <stdlib.h>

int main( int argc, char** argv ) {
    (void) argc; (void) argv; 

    struct image img;
    struct image rotated_img;
    FILE *file = fopen(argv[1], "rb");
    FILE *new_file = fopen(argv[2], "wb");


    from_bmp(file, &img);
    rotated_img = rotate(img);
    to_bmp(new_file, &rotated_img);


    fclose(file);
    fclose(new_file);
    free(img.data);
    free(rotated_img.data);
    return 0;
}
