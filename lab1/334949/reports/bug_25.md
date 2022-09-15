# BUG-25
## Category
String Vulnerability

## Description
The `atof()` will lead to an undefined behavior when the input value cannot be represented.

## Affected Lines in the original program
In `resize.c:19`

## Expected vs Observed
We expect `atof()` to turn string into the corresponding float. Yet, if the string is out of the double range, it will result in a undefined behavior.

## Steps to Reproduce

### Command

```
./filter test_imgs/test_img.png test_imgs/test_out_fake.png blur 1.70101010101010101
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Turn the data type of radius from int to long and use `strtod()` to replace `atof`
