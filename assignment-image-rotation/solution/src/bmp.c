#include "bmp.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>


enum read_status from_bmp( FILE* in, struct image* img ){
    struct bmp_header* header = malloc(sizeof(struct bmp_header));

    fread(header, sizeof(struct bmp_header), 1, in);

    printf("bfType %d\n", header->bfType);
    printf("bfileSize %d %lu\n", header->bfileSize, (sizeof(struct bmp_header) + header->biHeight* header->biWidth * sizeof(struct pixel) + header->biHeight* ((header->biWidth* sizeof(struct pixel))%4)));
    printf("bfReserved %d\n", header->bfReserved);
    printf("bOffBits %d\n", header->bOffBits);
    printf("biSize %d\n", header->biSize);
    printf("biPlanes %d\n", header->biPlanes);
    printf("biBitCount %d\n", header->biBitCount);
    printf("biCompression %d\n", header->biCompression);
    printf("biSizeImage %u\n", header-> biSizeImage);
    printf("biXPelsPerMeter %d\n", header->biXPelsPerMeter);
    printf("biYPelsPerMeter %d\n", header->biYPelsPerMeter);
    printf("biClrUsed %d\n", header->biClrUsed);
    printf("biClrImportant %d\n", header->biClrImportant);


    img->data = malloc(sizeof(struct pixel)*header->biWidth*header->biHeight);
    img->height = header->biHeight;


    for(uint32_t i=0; i< header->biHeight; i++) {
        fread(&(img->data[i*img->width]), sizeof(struct pixel), header->biWidth, in);
        fseek( in, header->biWidth%4, SEEK_CUR);
    }

    free(header);

    return READ_OK;
}


enum write_status to_bmp( FILE* out, struct image const* img ) {


    struct bmp_header header = {
            .bfType = 0x4D42,
            .bfileSize = (sizeof(struct bmp_header)
                          + img->height* img->width * sizeof(struct pixel)
                          + img->height* ((img->width)%4)),
            .bfReserved = 0, 
            .bOffBits = sizeof(struct bmp_header),
            .biSize = 40,
            .biWidth = img->width,
            .biHeight = img->height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = img->height * img->width * sizeof(struct pixel) + (img->width % 4)*img->height,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };

    fwrite(&header, sizeof(struct bmp_header), 1, out);


    const size_t fill = 0;

    for(uint32_t h=0; h< img->height; h++) {
        fwrite(&(img->data[h*img->width]),sizeof(struct pixel), img->width, out);
        fwrite(&fill, 1, img->width % 4, out);
    }
    return WRITE_OK;
}

