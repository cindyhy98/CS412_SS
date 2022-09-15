# BUG-11
## Category
Wrong Operator

## Description
Access to the wrong location of argv 

## Affected Lines in the original program
In `rect.c:34` `rect.c:35`


## Expected vs Observed
We expect to store `argv[6]` in `hex_color`. Yet, we use the wrong index and then causes segmentation fault

## Steps to Reproduce

### Command

```
./rect test_imgs/test_img.png test_imgs/test_out.png 0 0 5 5 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change `argv[7]` to `argv[6]`
