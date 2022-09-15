# BUG-6
## Category
String Vulnerability

## Description
The `atoi()` will lead to an undefined behavior when the input value cannot be represented.

## Affected Lines in the original program
In `filter.c:248`, `rect.c:23-27`, `circle.c:21-25`

## Expected vs Observed
We expect `atoi()` to turn string into the corresponding int. Yet, if the string is out of the int range (e.g. 2147483648), it will result in a undefined behavior.

## Steps to Reproduce

### Command

```
./filter test_imgs/test_img.png test_imgs/test_out_fake.png blur 2147483648
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Turn the data type of radius from int to long and use `strtol()` to replace `atoi`
