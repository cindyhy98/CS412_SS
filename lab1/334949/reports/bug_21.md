# BUG-21
## Category
Unchecked system call returning code

## Description
Didn't check the return value of `fflush(stdout)`

## Affected Lines in the original program
In `solid.c:122` 

## Expected vs Observed
We expect `fflush(stdout)` to perform normally and return 0, so that the program to output "Size " right away. Yet, `fflush()` may fail in certain situations specified in the documentation.

## Steps to Reproduce

It is not easy to reproduce this bug. Yet, in certain situations, you can observe the bug happens. For example, when an attempt was made to write a file that exceeds the maximum file size (errno: EFBIG) or the fflush() function was interrupted by a signal (errno: EINTR)

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Check if the return value of `fflush(stdout)` equals to zero.