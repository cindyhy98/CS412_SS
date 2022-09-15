#include <stdio.h>
#include "pngparser.h"

int main(int argc, char *argv[])
{
    struct image *img = NULL;

    if (argc != 2) {
        return 1;
    }

    /* Name the arguments */

    const char *input_name = argv[1];

    if (load_png(input_name, &img)) {
        return 1;
    }

    printf("Image dimensions: %hux%hu\n", img->size_x, img->size_y);
    if(img->px != NULL)
        free(img->px);
    //is it the right way to fix this?
    if(img->size_x != 0 || img->size_y != 0)
        free(img);
    return 0;
}