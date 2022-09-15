# BUG-18
## Category
Wrong Operator

## Description
Using the wrong operator(`==` instead of `=`) for assigning value to variable.

## Affected Lines in the original program
In `circle.c:61` `circle.c:84`


## Expected vs Observed
We expect to store value in variable using `=`. Yet, it uses `==`

## Steps to Reproduce

### Command

```
./circle test_imgs/test_img.png test_imgs/test_out.png 0 0 5 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change `==` to `=`
