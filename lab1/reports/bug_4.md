# BUG-4
## Category
Local Persisting Pointers

## Description
The `struct pixel` pointer `*px` is declared in the function `get_pixel()`, which is a local variable.  Yet, the memory is freed after the function is called, which leads to an undifined behavior. 

## Affected Lines in the original program
In `filter.c:107-110`

## Expected vs Observed
We expect the `get_pixel()` to generate a memory for pixel which then later be used in the function `filter_negative()`. Yet, we receive a segmentation fault upon executing this function since we haven't allocate memory for this pixel.

## Steps to Reproduce

### Command

```
./filter test_imgs/test_img.png test_imgs/test_neg.png negative
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Use `malloc()` to allocate memory for the pixel pointer.
