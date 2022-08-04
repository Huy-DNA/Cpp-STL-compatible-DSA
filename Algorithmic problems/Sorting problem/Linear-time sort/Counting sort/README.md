# Counting sort
Notes about this implementation of counting sort:
* Assumptions: 
    * Every element is of some integral type or has an integral-typed field named 'key'.
    * Every element or its 'key' value lies within [0, k], for some non-negative integer k.
* Time complexity:
    * Average-case running time: $\Theta(n + k)$
    * Best-case running time: $\Theta(n + k)$
    * Worst-case running time: $\Theta(n + k)$
* Space complexity: $\Theta(2n)$ (there could be some room for improvement here)
* Other technical:
    * Stable
    * NOT in-place
    * Only works with random-access iterators (in C++ terminology)