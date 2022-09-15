## Name
Deference NULL pointer 

## Description
There is no type check before deferencing a pointer.


## Affected Lines
In `pngparser.c:143`

## Expected vs Observed
We expect `is_png_ihdr_valid` to deference on non-NULL pointer `ihdr` and check if it's a valid `png_ihdr`. Yet, we observe a segfault when the `ihdr` pointer is NULL

## Steps to Reproduce

### Command

```
./size ./reports/01/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/01/poc)

## Suggested Fix Description
Before deferencing, check if the pointer is NULL or not. Add the following code in the beginning of function `is_png_ihdr_valid`   
```
if(ihdr == NULL)
    return 0;
```