# Merge sort
Notes about this implementation of merge sort:
* Time complexity:
    * Average-case running time: $\Theta(\lg n)$
    * Best-case running time: $\Theta(\lg n)$
    * Worst-case running time: $\Theta(\lg n)$
* Space complexity: $\Theta(\lg n)$
* Other technical:
    * Stable
    * NOT in-place
    * Only works with random-access iterators (in C++ terminology)

Observations:
* Merge sort's code is not tight so the hidden constant in $O(\lg n)$ is actually large. That's why Heap sort of Quick sort is usually preferred and also why Merge sort is much slower when sorting small arrays compared to Insertion sort.
