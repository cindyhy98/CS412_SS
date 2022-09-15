# BUG-7
## Category
Heap Overflow 

## Description
The allocated memory hasn't been freed after using. This results in a memory leak.

## Affected Lines in the original program
In `circle.c:52-68`, `circle.c:75-91`

## Expected vs Observed
We expect the allocated memory be freed everytime after it is used; otherwise, the non-freed memory on the heap can reduce the performance of the computer.


## Steps to Reproduce

### Command
`./filter test_imgs/test_img.png test_imgs/test_neg.png negative`


### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Allocate memory before the loop and free it after the loop.