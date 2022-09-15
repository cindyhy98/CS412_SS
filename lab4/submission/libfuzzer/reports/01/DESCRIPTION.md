## Name
Memory Leak

## Description
A used pointer is never freed which in the end leaks the memory.


## Affected Lines
In `pngparser.c:867`

## Expected vs Observed
We expect the program to free all the pointers without leaking memory. 
We observed that the pointer `non_compressed_buf` is never freed in `store_idat_rgb_alpha`.


## Steps to Reproduce

### Command

```
./fuzzer_store_png_rgba  ./reports/01/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/01/poc)

## Suggested Fix Description
Free the memory before returning
```
if(non_compressed_buf){
    free(non_compressed_buf);
  }
```