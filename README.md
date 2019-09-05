# Multiprocessing-Sorter
Introduction

The basic parts and dataflow for the project are the same as the previous. The CSV file with movie
metadata will remain the same. The sorting algorithm will also remain the same. If you properly
modularized your code in Project 0, you should be able to reuse almost all of your code.
In this project, you will read in a directory name and walk through the directory structure to find all
.csv files. There may be multiple levels of directories that you will need to recurse through. For each
directory you find you should fork() a child process that will sort each of the files in it and output the
results to a different file. You should NOT use exec for this project. You should write one program that,
when copied from the parent to the child process, will continue running. You can use the return value of
fork() in a conditional to choose different blocks of code to run within your code. You will want to
make sure to prevent zombie and orphan child processes. You will also want to make sure you to not
create fork bombs that will bring down machines. In all cases of bad input, you should fail gracefully
(e.g. no segfaults).

You will output metadata about your processes to STDOUT. This metadata will show the total number
of processes created and the pids of all created processes.
Methodology

a. Parameters
Your code will read in a set of parameters via the command line. Records will be stored in .csv files in
the provided directory. As mentioned above, directory structures may have multiple levels and you
must find all .csv files. Your code should ignore non .csv files and .csv files that do not have the format
of the movie_metadata csv (e.g. comma-separated heading list followed by same numer of commaseparated values in records).
Your code must take in a command-line parameter to determine which value type (column) to sort on.
If that parameter is not present your code should output an error, deallocate any memory in use and
shut down gracefully. The first flag your program must recognize will be '-c' to indicate sorting by
column and the second will be the column name:
./sorter -c food

Be sure to check that the flag exists. Your code should output an error and shut down if the '-c'
flag is not present. Be sure to check the column heading specified is in each CSV. If not, output an
error, but continue scanning and sorting files.
For this phase you'll extend your flags from one to three. The second flag your program must recognize
will be ‘-d’ indicating the directory the program should search for .csv files. If this parameter is not
specified, your code should continue without error and search the current directory.
./sorter -c food -d thisdir/thatdir
The third parameter to your program will be ‘-o’ indicating the output directory for the sorted versions
of the input file. If this parameter is not specified, your code should continue without error and send its
output to the same directoty as the source file.
 ./sorter -c movie_title -d thisdir -o thatdir

b. Operation
Your code will be reading in and traversing the entire directory. In order to run your code to test it, you
will need to open each CSV and read it for processing:
 ./sorter -c movie_title -d thisdir -o thatdir
Your code's output will be a series of new CSV files outputted to the file whose name is the name of the
CSV file sorted, with "-sorted-<fieldname>" postpended to the name.
 e.g: 'movie_metadata.csv' sorted on the field 'movie_title' will result in a file named
"movie_metadata-sorted-movie_title.csv".
On each new file in a directory you encounter, you should fork() a child process to do the actual
sorting.
On each new directory you encounter, you should fork() a child process to process the directory.
To STDOUT, output the following metadata in the shown order:
Initial PID: XXXXX
PIDS of all child processes: AAA,BBB,CCC,DDD,EEE,FFF, etc
Total number of processes: ZZZZZ
You may assume the total number of files and directories will not exceed 255.
c. Structure
Your code should use Mergesort to do the actual sorting of records. It is a powerful algorithm with an
excellent average case. You should write your own Mergesort code.
Results

Document your design, assumptions, difficulties you had and testing procedure. Include any test CSV
files you used in your documentation. Be sure to also include a short description of how to use your
code. Look at the man pages for suggestions on format and content.
