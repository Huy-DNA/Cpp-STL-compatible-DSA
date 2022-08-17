# Randomized select algorithm
> The last part of this algorithm (where you modify begin and end) was kinda tricky to me. I hate these kinds of situation in general though --- off by one and BAM! you are dead.

Notes about this implementation of select algorithm:
* Time complexity:
    * Expected-case running time: $\Theta(n)$
    * Best-case running time: $\Theta(n)$
    * Worst-case running time: $\Theta(n^2)$
* Space complexity: $\Theta(1)$
* Other technical:
    * Only works with random-access iterator (in C++ terminology)

Notes:
* This algorithm uses the same idea as Quick sort.
* There exists an algorithm that yields the worst-case running time of $\Theta(n)$ but this algorithm is usually preferred in practice.