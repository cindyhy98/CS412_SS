## Name
Write to missing file

## Description
The program is trying to write to a missing file.


## Affected Lines
In `pngparser.c:1001`, `pngparser.c:716`

## Expected vs Observed
We expect the program to handle missing files. Yet, we observed a segfault.


## Steps to Reproduce

### Command

```
./fuzzer_store_png_name  ./reports/05/poc
```
### Proof-of-Concept Input (if needed)
(attached: ./reports/05/poc)

## Suggested Fix Description
Add checking after `fopen()`.
```
if (!output) {
    return 1;
}
```