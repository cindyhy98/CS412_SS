# BUG-2
## Category
String vulnerability

## Description
The function `strncpy(char *dest, const char *src, size_t n)` won't add character '\0' in the end of the string when len(src) is bigger than n. Thus, it is a string vulnerability. 

## Affected Lines in the original program
In `filter.c:219-221`

## Expected vs Observed
When the length of argv[1], argv[2], argv[3] is smaller then ARG_SIZE, which 255 byte, then it can be copied into input, output and command correctly and successfully. Yet, if the length exceeds 255, since there is no '\0' in the end of the copied string, program will read out things from the stack until it finds a '\0'

## Steps to Reproduce

### Command

```
./filter fakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakefakeeee out.png grayscale
```
### Proof-of-Concept Input (if needed)


## Suggested Fix Description
add a `'\0'` manually in the end of the copied string
 