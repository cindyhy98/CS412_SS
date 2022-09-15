# BUG-26
## Category
Unchecked system call returning code

## Description
Didn't check the return value of `malloc`

## Affected Lines in the original program
In `solid.c:11` 

## Expected vs Observed
We expect to check if the malloc is successful. Yet, it doesn't check
## Steps to Reproduce

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Check the return code of malloc.