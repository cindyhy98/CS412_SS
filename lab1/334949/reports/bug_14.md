# BUG-14
## Category
Wrong Operator

## Description
Using the wrong operator (`+`instead of`*`) for`malloc()`

## Affected Lines in the original program
In `resize.c:48`


## Expected vs Observed
We expect to multiply the number of pixels with the size of one pixel. Yet, here uses a wrong operator `+`.

## Steps to Reproduce

### Command

```
./resize test_imgs/test_img.png out.png 0.5
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change `+` to `*`
