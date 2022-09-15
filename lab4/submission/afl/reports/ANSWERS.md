1. Why did you need to change `is_png_chunk_valid`?
	- This function verify whether the CRC for this png is valid or not. Since building a valid CRC for each input is too tedious and do no good for the fuzzing process, we simply make the CRC valid for each input.

2. Why did you have to use `afl-clang` to compile the source (and not e.g. ordinary gcc)?
	- `afl-clang` will put (instrument) some information about jumps in the binary to help the fuzzer, so that we don't need to do black-box fuzzing. 
		
3. How many crashes in total did AFL produce? How many unique crashes?
	- It produces 13K crashes and there are 6 different crashes
	
4. Why are hangs counted as bugs in AFL? Which type of attack can they be used for?
	- (1) If a program hangs, it will terminate after a long period of time (or even not at all). Since this is not a attended behavior, it is considered as a bug.
	- (2) This can be used to create DOS attacks.
	
5. Which interface of `libpngparser` remains untested by AFL (take a look at `pngparser.h`)?
	- Everything that is used by `store_png` will not be tested.

	
