# Merge sort
Notes about both implementations of merge sort (one for random access iterator, one for bidirectional and forward iterator):
* Time complexity:
    * Average-case running time: $\Theta(n\lg n)$
    * Best-case running time: $\Theta(n\lg n)$
    * Worst-case running time: $\Theta(n\lg n)$
* Space complexity: $\Theta(n)$
* Other technical:
    * Stable
    * NOT in-place
    * Works with random-access, bidirectional, forward iterators (in C++ terminology)

Notes:
* Merge sort's code is not tight so the hidden constant in $O(n\lg n)$ is actually large. That's why Heap sort of Quick sort is usually preferred and also why Merge sort is much slower when sorting small arrays compared to Insertion sort.
* The random-access version is more optimized when working with data structures that expose random access iterators. However, the other version can be used to sort container data structures that don't support random accesses to elements such as Linked List.
