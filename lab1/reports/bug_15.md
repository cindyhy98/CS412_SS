# BUG-15
## Category
Unchecked system call returning code

## Description
Hasn't check if the return value is 0 (which means it's a successful return) or other non-zero value (which means it's a fail return).

## Affected Lines in the original program
In `checkerboard.c:129`, `circle.c:93`, `filter.c:287`, `rect.c:85`, `resize.c:74`


## Expected vs Observed
We expect to goto error when we are not able to store the change in the output file. Yet, we do not check the return value, so the program will not report there is an error. 

## Steps to Reproduce

### Command

```
mkdir test
chmod 444
./checkerboard test/fake_output.png 100 100 2 000000 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Check the return value in the `if` statement and `goto `error when it's a fail return.
