# Quick sort
Notes about this implementation of quick sort:
* Time complexity:
    * Average-case running time: $\Theta(n\lg n)$
    * Expected running time: $\Theta(n\lg n)$
    * Best-case running time: $\Theta(n\lg n)$
    * Worst-case running time: $\Theta(n^2)$
* Space complexity: 
    * Worst-case: $\Theta(n)$
* Other technical:
    * This implementation is a randomized algorithm
    * Unstable
    * In-place
    * Only works with random-access iterators (in C++ terminology)

Notes:
* The technique (pick a pivot then compare it to other elements in order to partition the array) used in Quick sort can be applied to other sorts of problems, such as Selection problem.
* Although Quick sort isn't asymtotically the best sorting algorithm, it often beats Merge sort and Heap sort in practice due to its asymtotically optimal expected running time and tight code. Therefore, Quick sort is usually the opted choice for generic sorting purposes.