## Name
Temporal Safety Violation (Double Free)

## Description
`chunk_data` has already been freed in `error` in `read_png_chunk`. But then it encounters another free in `error` in `load_png`


## Affected Lines
In `pngparser.c:274`

## Expected vs Observed
We expect the program to free the memory only once. Yet, we observe a double free

## Steps to Reproduce

### Command

```
./size ./reports/00/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/00/poc)

## Suggested Fix Description
Add `chunk->chunk_data = NULL` after the `free(chunk->chunk_data)`, preventing the reuse of `chunk_data` 