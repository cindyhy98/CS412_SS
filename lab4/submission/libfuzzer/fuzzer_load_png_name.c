#include "pngparser.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>

int is_name_valid(const uint8_t *Data, size_t size){

    // invalid size return 1
    if(size > NAME_MAX || size == 0)
        return 1;

    for(int i = 0; i < size; i++){
        if(Data[i] == '\0' || Data[i] == '/' || Data[i] > 127)
            return 1;
    }

    return 0;
}
// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    struct image *test_img;

    if(is_name_valid(Data, Size))
        return 0;


    char filename[NAME_MAX+1] = {0};
    strncpy(filename, (char *)Data, Size);
    // printf("filename = %s\n", filename);

    load_png(filename, &test_img);

    // printf("hello!\n");
    // Always return 0
    return 0;
}