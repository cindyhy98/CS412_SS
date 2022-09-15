# BUG-13
## Category
Type Error

## Description
Using the wrong type for the argument in `strtol()`. 

## Affected Lines in the original program
In `rect.c:34`


## Expected vs Observed
We expect to use a reference to an pointer as the second argument of `strtol()`. Yet, we only give it a pointer. 

## Steps to Reproduce

### Command

```
./rect test_imgs/test_img.png test_imgs/test_out.png 0 0 5 5 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change `end_ptr` to `&end_ptr`
