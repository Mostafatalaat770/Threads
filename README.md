# Threads

## Matrix Multiplication

2 implementations were made:

- The computation of each element of the output matrix happens in a thread.
- The computation of each row of the output matrix happens in a thread.

Time difference was found between the two implementations.

| Element wise | Row wise  |
| ------------ | --------- |
| 0.003381s    | 0.000116s |

## Merge Sort

Merge sort is an O (n log n) comparison-based sorting algorithm. It is a divide and
conquer algorithm.

It was implemented using Pthreads.
Each time the list is divided;
two threads are created to do merge-sort on each half separately. This step is
repeated recursively until each sub-list has only one element.
