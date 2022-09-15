## Name
Double Freeing 

## Description
`current_chunk->chunk_data` is never initialized to NULL, leading to it being freed in the error handling code.


## Affected Lines
In `pngparser.c:544`

## Expected vs Observed
We expect the program not to not free a memory twice. Yet, we observed a a double free.

## Steps to Reproduce

### Command

```
./fuzzer_load_png ./reports/00/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/00/poc)

## Suggested Fix Description
Init current_chunk->chunk_data to zero
```
  current_chunk->chunk_data = NULL;
```