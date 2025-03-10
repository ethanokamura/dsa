To find the constant value, I used a script to automate tests (with sorted lists)

The script did the following:
  1. created an array of text files, constant sizes, and clock times (using clock_t)
  2. run an outer for loop to run the script against multiple lists
  3. run a loop to get the time from each tested constant value
    - measured using the units of entries per second
  4. run a loop to find the fastest time out of the constants tested
  5. output the index and constant value for the fastest time
  6. continue loop for larger datasets

After the script ran, I manually found the average of the fastest constant for each file size.
I then adjusted the range of constants in my array of constants to narrow the results.
After 5 runs (100 trials), I was able to find the average number was 25.
I tested this against the controlled value (entries/second) with no constant.
I found that the times with the constant read the files faster.
Data below.

First Set:
[trial 1] const: 20 for 9K.txt
[trial 2] const: 30 for 99K.txt
[trial 3] const: 25 for 999K.txt
[trial 4] const: 30 for 9M.txt
[trial 5] const: 25 for 9K.txt
[trial 6] const: 30 for 99K.txt
[trial 7] const: 20 for 999K.txt
[trial 8] const: 20 for 9M.txt
[trial 9] const: 20 for 9K.txt
[trial 10] const: 20 for 99K.txt
[trial 11] const: 20 for 999K.txt
[trial 12] const: 30 for 9M.txt
[trial 13] const: 20 for 9K.txt
[trial 14] const: 30 for 99K.txt
[trial 15] const: 30 for 999K.txt
[trial 16] const: 30 for 9M.txt
[trial 17] const: 30 for 9K.txt
[trial 18] const: 20 for 99K.txt
[trial 19] const: 25 for 999K.txt
[trial 20] const: 20 for 9M.txt
AVG: 24

Second Set:
[trial 1] const: 30 for 9K.txt
[trial 2] const: 30 for 99K.txt
[trial 3] const: 25 for 999K.txt
[trial 4] const: 25 for 9M.txt
[trial 5] const: 30 for 9K.txt
[trial 6] const: 30 for 99K.txt
[trial 7] const: 20 for 999K.txt
[trial 8] const: 30 for 9M.txt
[trial 9] const: 30 for 9K.txt
[trial 10] const: 20 for 99K.txt
[trial 11] const: 25 for 999K.txt
[trial 12] const: 20 for 9M.txt
[trial 13] const: 25 for 9K.txt
[trial 14] const: 30 for 99K.txt
[trial 15] const: 30 for 999K.txt
[trial 16] const: 20 for 9M.txt
[trial 17] const: 20 for 9K.txt
[trial 18] const: 30 for 99K.txt
[trial 19] const: 20 for 999K.txt
[trial 20] const: 20 for 9M.txt
AVG: 25

Third Set:
[trial 1] const: 30 for 9K.txt
[trial 2] const: 30 for 99K.txt
[trial 3] const: 25 for 999K.txt
[trial 4] const: 20 for 9M.txt
[trial 5] const: 30 for 9K.txt
[trial 6] const: 20 for 99K.txt
[trial 7] const: 20 for 999K.txt
[trial 8] const: 25 for 9M.txt
[trial 9] const: 30 for 9K.txt
[trial 10] const: 30 for 99K.txt
[trial 11] const: 20 for 999K.txt
[trial 12] const: 20 for 9M.txt
[trial 13] const: 20 for 9K.txt
[trial 14] const: 20 for 99K.txt
[trial 15] const: 25 for 999K.txt
[trial 16] const: 25 for 9M.txt
[trial 17] const: 30 for 9K.txt
[trial 18] const: 20 for 99K.txt
[trial 19] const: 20 for 999K.txt
[trial 20] const: 30 for 9M.txt
AVG: 24

Forth Set:
[trial 1] const: 27 for 9K.txt
[trial 2] const: 25 for 99K.txt
[trial 3] const: 25 for 999K.txt
[trial 4] const: 27 for 9M.txt
[trial 5] const: 27 for 9K.txt
[trial 6] const: 23 for 99K.txt
[trial 7] const: 25 for 999K.txt
[trial 8] const: 27 for 9M.txt
[trial 9] const: 27 for 9K.txt
[trial 10] const: 23 for 99K.txt
[trial 11] const: 23 for 999K.txt
[trial 12] const: 27 for 9M.txt
[trial 13] const: 23 for 9K.txt
[trial 14] const: 23 for 99K.txt
[trial 15] const: 23 for 999K.txt
[trial 16] const: 27 for 9M.txt
[trial 17] const: 25 for 9K.txt
[trial 18] const: 23 for 99K.txt
[trial 19] const: 25 for 999K.txt
[trial 20] const: 23 for 9M.txt
AVG: 24

[trial 1] const: 26 for 9K.txt
[trial 2] const: 26 for 99K.txt
[trial 3] const: 25 for 999K.txt
[trial 4] const: 26 for 9M.txt
[trial 5] const: 25 for 9K.txt
[trial 6] const: 26 for 99K.txt
[trial 7] const: 24 for 999K.txt
[trial 8] const: 25 for 9M.txt
[trial 9] const: 26 for 9K.txt
[trial 10] const: 25 for 99K.txt
[trial 11] const: 24 for 999K.txt
[trial 12] const: 24 for 9M.txt
[trial 13] const: 24 for 9K.txt
[trial 14] const: 25 for 99K.txt
[trial 15] const: 24 for 999K.txt
[trial 16] const: 24 for 9M.txt
[trial 17] const: 26 for 9K.txt
[trial 18] const: 25 for 99K.txt
[trial 19] const: 24 for 999K.txt
[trial 20] const: 26 for 9M.txt
AVG: 25
