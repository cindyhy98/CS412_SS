# BUG-8
## Category
Command Injection

## Description
The format of `output_name` hasn't been sanitized, thus creates a vulnerability for performing command injection(e.g. any `;` can terminate the command and start a new command right behind)

## Affected Lines in the original program
In `solid.c:123-125`

## Expected vs Observed
We expect the program to print out the file size directly. Yet, an unsanitized `output_name` appending can lead to command injection.

## Steps to Reproduce

### Command

```
./solid test_img.png;ls
```

### Proof-of-Concept Input (if needed)


## Suggested Fix Description
Use the `stat` function to retrieve the information of the file. (Instesd of execute `stat -c %s` directly through the command line)