#include "pngparser.h"
#include <stdio.h>
#include <string.h>
// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    struct image test_img;

    if(Size < 440){ //image data + palette
        return 0;
    }

    test_img.size_x = 10;
    test_img.size_y = 10;
    uint8_t size_palette = 10;

    test_img.px = Data; //10*10*4 bytes of images data

    struct pixel *palette = Data + 10*10*4; // palette -> 10*4 bytes


    store_png("test_img_palette.png", &test_img, palette, size_palette);

    // Always return 0
    return 0;
}