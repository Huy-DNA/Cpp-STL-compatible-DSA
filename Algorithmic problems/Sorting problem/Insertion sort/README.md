# Insertion sort
Notes about this implementation of insertion sort:
* Time complexity:
    * Average-case running time: $\Theta(n^2)$
    * Best-case running time: $\Theta(n)$
    * Worst-case running time: $\Theta(n^2)$
* Space complexity: $\Theta(1)$
* Other technical:
    * Stable
    * In-place
    * Only works with random-access iterators (in C++ terminology)

Notes:
* Insertion sort has very tight code, so although it has poor worst-case running time, it still beats asymtotically faster sorting algorithms like Merge sort for arrays of small size. We can take advantage of this by, for example, making Insertion sort a subroutine of Merge sort when the array are splitted *small enough*.
* Insertion sort has really good asymtotic best-case running time so it's often used when the array are almost sorted. We can take advantage of this by making Insertion sort a subroutine of some other sorting algorithms (like Quick sort) when we are sure the array are partially sorted.
