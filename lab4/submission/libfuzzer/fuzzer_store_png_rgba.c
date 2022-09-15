#include "pngparser.h"
#include <stdio.h>
#include <string.h>
// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    struct image test_img;
    // test_img = malloc(sizeof(struct image)); 

    if(Size != 400){ // at least 400 bytes
        return 0;
    }

    // char dataarr[400+1] = {0};
    // strncpy(dataarr, (char *)Data, 400);
    
    test_img.size_x = 10;
    test_img.size_y = 10;
    test_img.px = Data;
    
    // test_img->px = malloc(sizeof(struct pixel) * test_img->size_x * test_img->size_y);
    // for (uint8_t idy = 0; idy < 10; idy++) {
    
    //     for (uint8_t idx = 0; idx < 10; idx += 4) {
    //         uint8_t index = idy * test_img->size_x + idx;
    //         test_img.px[index].red = Data[index];
    //         test_img->px[index].green = Data[index+1];
    //         test_img->px[index].blue = Data[index+2];
    //         test_img->px[index].alpha = Data[index+3];
        
    //     }
    // }
    
    store_png("test_input.png", &test_img, NULL, 0);

    // Always return 0
    return 0;
}