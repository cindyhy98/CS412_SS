# BUG-5
## Category
Iteration Errors

## Description
The iteration bound `img->size_y` and `img->size_x` shouldn't be included in the interation; otherwise, it will result in a segmentation fault. 

## Affected Lines in the original program
In `filter.c:118` `filter.c:119`

## Expected vs Observed
We expect the nested loop to iterate through all pixels in the image. Yet, it access to the pixel out of boundry and lead to a segmentation fault. 

## Steps to Reproduce

### Command

```
./filter fakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakee.png out.png blur 3
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change the `<=` in line 118 and 119 to `<`
