# BUG-1
## Category
String vulnerability

## Description
It's a print without using formatted string.


## Affected Lines in the original program
In `filter.c:230`

## Expected vs Observed
We expect to print out the input string when there is an error loading a png image.  
Yet, if the variable input contains format specifiers (e.g. `%d`, `%s`), the function will read as many positions from the stack as indicated by these specifiers and print those on the screen.


## Steps to Reproduce

### Command

```
./filter fake_input%d fake_output.png grayscale
```
### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Print the input variable using formatted string `printf("%s ", input)`
