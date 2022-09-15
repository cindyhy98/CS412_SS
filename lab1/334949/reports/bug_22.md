# BUG-22
## Category
Unchecked system call returning code

## Description
Didn't check the return value of `system(command)`

## Affected Lines in the original program
In `solid.c:125` 

## Expected vs Observed
We expect `system(command)` to perform normally and execute the command. Yet there are several special situations when the system call may fail (according to the documentation). 

## Steps to Reproduce

It is not easy to reproduce this bug. Yet, in certain situations, you can observe the bug happens. For example,when there are insufficient resources to create another process, or the maximum number of processes you can run has been reached. (errno: EAGAIN)

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
The normal way to fix an unchecked system call is to check it. Yet, this bug also leads to command injection, so I simply get rid of `system(command)` and call on `stat` instead. 