# Merge-sort-threads-
Merge sort is an O (n log n) comparison-based sorting algorithm. It is a divide and
conquers algorithm. Conceptually, a merge sort works as follows:
If the list is of length 0 or 1, then it is already sorted. Otherwise:
1. Divide the unsorted list into two sub-lists of about half the size.
2. Sort each sub-list recursively by re-applying the merge sort.
3. Merge the two sub-lists back into one sorted list
So you are required to implement it using pthreads. Each time the list is divided; two
threads are created to do merge-sort on each half separately. This step is repeated
recursively until each sub-list has only one element.
The program should read two input matrices from a file in the following format:
[number of elements]
Array elements which are space separated.
example input:
10

100 20 15 3 4 8 7 -1 0 33

When the program finishes, it should print out the sorted array.
