## Name
Bad Free

## Description
The program is trying to free on address which was not malloc()-ed


## Affected Lines
In `pngparser.c:939`

## Expected vs Observed
We expect the program to free on malloc()-ed memory. Yet, we observed a bad free.


## Steps to Reproduce

### Command

```
./fuzzer_store_png_palette  ./reports/06/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/06/poc)

## Suggested Fix Description
Free the actual malloc()-ed memory
```
if (non_compressed_buf) {
    free(non_compressed_buf);
}
```