# BUG-24
## Category
Arithmetic Overflow

## Description
Multiply two unsigned short number can cause overflow

## Affected Lines in the original program
In `resize.c:33-34`

## Expected vs Observed
We expect to have a 32 bits number when multiply two 16 bits number. Yet, if the datatype of `size_x` and `size_y` are both `uint16_t`, then when multipling a `double` with it can cause a overflow.

## Steps to Reproduce

### Command

```
./resize ./test_imgs/desert.png resize_desert.png 270
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Check if the input is in the range of `USHRT_MAX` / height or `USHRT_MAX` / width