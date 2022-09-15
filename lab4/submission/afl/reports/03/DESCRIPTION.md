## Name
Dereference NULL pointer 

## Description
There is no type check before deferencing a pointer.


## Affected Lines
In `pngparser.c:393`

## Expected vs Observed
We expect `convert_color_palette_to_image` to deference on non-NULL pointer `plte_chunk`. Yet, we observe a segfault when the `plte_chunk` pointer is NULL

## Steps to Reproduce

### Command

```
./size ./reports/03/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/03/poc)

## Suggested Fix Description
Add the following code before dereferencing `plte_chunk` in `convert_color_palette_to_image`   
```
if(plte_chunk == NULL)
    return NULL;
```