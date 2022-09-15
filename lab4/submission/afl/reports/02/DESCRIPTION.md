## Name
Temporal Safety Violation (Double Free)

## Description
Double freeing img


## Affected Lines
In `size:22`

## Expected vs Observed
We expect the program to free the memory only once. Yet, we observe a double free

## Steps to Reproduce

### Command

```
./size ./reports/02/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/02/poc)

## Suggested Fix Description
Only do `free(img)` when it is not NULL
Add the checking before freeing
```
if(img->size_x != 0 || img->size_y != 0)
        free(img);
```