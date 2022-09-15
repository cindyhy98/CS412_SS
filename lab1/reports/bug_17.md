# BUG-17
## Category
Arithmetic Overflow

## Description
Data type of `radius`is `int`, which is a 32 bits number. It can be overflowed with multipling two 32 bits number together.

## Affected Lines in the original program
In `circle.c:53`, `circle.c:61`, `circle.c:76`, `circle.c:84`

## Expected vs Observed
When multiplying two 32 bits number, we expect to receive a normal 64 bits number not a overflowed one.


## Steps to Reproduce

### Command

```
./circle /test_imgs/test_img.png out.png 10 10 2147483647 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Change the type of `x` and `y` to `long long int`. Cast `radius` to `long long int` when performing multiplication. 