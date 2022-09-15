# BUG-16
## Category
Temporal Safety Violation

## Description
Double freeing the memory for img.

## Affected Lines in the original program
In `checkerboard.c:91`


## Expected vs Observed
We only expect to free the memory once.

## Steps to Reproduce
Make your system running out of memory.

### Command


### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Delete the `free(img)` in line 91.
