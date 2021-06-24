# file-sort
External merge sort of file's lines.

## Task

Task was to write a sort of lines in file which does not fit in memory.
The required memory should not depend on size of the file. The line length is reasonable, one line is 
much less than RAM. To check, there must be a generator of such files which takes number of lines and maximum length as parameters.
Programmimng language is not important. Recommended to spend no more than 4 hours.

## Solution

Generator is pretty simple (not very fast because of string generation, I know, how to fix). The implementation is
located in `src/file_generation.{h, cpp}`.

I've chosen merge sort as sorting algorithm for this task. My sort function takes input/output files (can be the same) and also
maximum amount of memory to use in bytes. It is approximate now, should be finalized, but still. 
Code is in `src/file_sorting.{h, cpp}`.

Don't use function with very large file and very small memory limit, now it is a bottleneck because of a limit of 
file descriptors. I calculated that 1GB limit is pretty good for every reasonable file size (up to 2-4 TB).

The algorithm is as follows: 

1) It goes throw the input file, processing block by block, sorting them internally and writing them to temporary files

2) It creates stream for every block (temporary file) and creates map of strings (at most one string from one block at the same time)
and numbers (block ids).

3) Then it just gets minimum element from map, writes it to output file, deletes element from the map and inserts next string from that
temporary file, which string it was, if possible
