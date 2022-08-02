# Quick sort
Notes about this implementation of quick sort:
* Time complexity:
    * Average-case running time: $\Theta(n\lg n)$
    * Best-case running time: $\Theta(n\lg n)$
    * Worst-case running time: $\Theta(n^2)$
* Space complexity: 
    * Worst-case: $\Theta(n)$
* Other technical:
    * Unstable
    * In-place
    * Only works with random-access iterators (in C++ terminology)

Observations:
* The technique (pick a pivot then compare it to other elements in order to partition the array) used in Quick sort can be applied to other sorts of problems, such as Selection problem.