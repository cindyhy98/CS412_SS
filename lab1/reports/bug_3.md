# BUG-3
## Category
Stack Buffer Overflow 

## Description
Using `strcpy()` function to copy a large character array into a smaller one is dangerous

## Affected Lines in the original program
In `filter.c:244-246`

## Expected vs Observed
We expect `strcpy()` to copy argv[4] to arg without modifying any other variable on the stack. Yet the copy is only safe when len(argv[4]) is shorter than len(arg), otherwise it will overflow other data(e.g. radius) on the stack or create a segmantation fault. (Since `strcpy()` doesn't check the length of the copied data)
## Steps to Reproduce

### Command

```
./filter test_imgs/test_img.png test_imgs/test_out_fake.png blur 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Use `strncpy()` and add a '\0' at the end of the copied string manually 
