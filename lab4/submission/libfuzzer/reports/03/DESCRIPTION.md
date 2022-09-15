## Name
Memory Leak

## Description
A used pointer is never freed which in the end leaks the memory.


## Affected Lines
In `pngparser.c:535`

## Expected vs Observed
We expect the program to free all the pointers without leaking memory. 
We observed that the pointer `plte_chunk->chunk_data` is never freed in `load_png`.


## Steps to Reproduce

### Command

```
./fuzzer_load_png  ./reports/03/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/03/poc)

## Suggested Fix Description
In both `error` and `success`, check whether `plte_chunk` and `plte_chunk->chunk_data` is NULL. 
If it's not, freed it before returning.
```
if (plte_chunk) {    
  if (plte_chunk->chunk_data) {
      free(plte_chunk->chunk_data);
  }

  free(plte_chunk);
}
```