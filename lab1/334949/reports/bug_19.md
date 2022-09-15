# BUG-19
## Category
Heap Overflow 

## Description
Access to invalid memory and lead to a heap overflow.

## Affected Lines in the original program
In `circle.c:52-68`, `circle.c:75-91`

## Expected vs Observed
We expect to access only the valid area within the picture, which means the whole circle needs to be in the picture. 


## Steps to Reproduce

### Command
`./circle test_imgs/test_img.png out.png -100 -100 10 ffffff`


### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Put constraint on `center_x`, `center_y` and `radius`