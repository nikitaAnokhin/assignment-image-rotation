#include "image.h"
#include <stdlib.h>


struct image rotate( struct image const source ) {
    struct image output = {0};

    output.width = source.height;
    output.height = source.width;
    output.data = malloc(sizeof(struct pixel)*source.width*source.height);

    for (uint64_t i = 0; i < source.width; i++) {
        for (uint64_t j = 0; j < source.height; j++) {
            output.data[i * output.width + j] =  source.data[(source.height-1-j) * source.width + i];
        }
    }
    return output;

}
