# BUG-20
## Category
Iteration Errors

## Description
It hasn't iterate through all the pixels since the `i++` is done before `j++`. Also it hasn't initialized `i` in each loop 

## Affected Lines in the original program
In `rect.c:63-83` 

## Expected vs Observed
We expect `i` to be initialized to 0 in each round and also be incremented after looping to all j. Yet, in the code we hasn't initialized i in each round

## Steps to Reproduce

### Command

```
./rect /test_imgs/test_img.png out.png 0 0 5 5 ffffff
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Move `i++` out the inner loop and also init it in each round
