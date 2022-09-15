## Name
Memory Leak

## Description
A used pointer is never freed which in the end leaks the memory.


## Affected Lines
In `pngparser.c:535`

## Expected vs Observed
We expect the program to free all the pointers without leaking memory. 
We observed that the pointer `iend_chunk->chunk_data` is never freed in `load_png`.


## Steps to Reproduce

### Command

```
./fuzzer_load_png  ./reports/04/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/04/poc)

## Suggested Fix Description
In both `error` and `success`, check whether `iend_chunk` and `iend_chunk->chunk_data` is NULL. 
If it's not, freed it before returning.
```
if (iend_chunk) {    
  if (iend_chunk->chunk_data) {
      free(iend_chunk->chunk_data);
  }

  free(iend_chunk);
}
```