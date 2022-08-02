# Quick sort (Tail recursion)
Notice that in the normal implementation of Quick sort, we make a recursion call 2 times, one of which is the last statement of the function. **Tail recursion** is an optimization technique, that is to turn the last recursion call into a loop. As function calls are more expensive than a simple iteration both memory-wise and performance-wise, using this technique we can squeeze out more performance and save memory:

* Time complexity:
    * Expected running time: $\Theta(n\lg n)$ (same)
    * Worst-case running time: $\Theta(n^2)$ (same)
* Space complexity:
    * Worst-case: $\Theta(\lg n)$ (improved!)
