# BUG-23
## Category
Heap Overflow

## Description
The `square_width` is not divisible by either `width` or `height`

## Affected Lines in the original program
In `checkerboard.c:102-127` 

## Expected vs Observed
We expect all the accessed pixels are within the image. Yet, if `square_width` is not divisible by either `width` or `height`, we will access to the pixels outside the image, which create a heap overflow.


## Steps to Reproduce
```
./checkerboard checker.png 123 32 7 808080 800000
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Check if `square_width` is divisible by both `width` and `height`. If not, `goto error_squaresize`
