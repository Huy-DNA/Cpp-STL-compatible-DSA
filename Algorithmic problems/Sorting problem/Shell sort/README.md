# Shell sort
Notes about this implementation of shell sort:
* Time complexity:
    * Average-case running time: $???$
    * Best-case running time: $???$
    * Worst-case running time: $???$
* Space complexity: 
    * Worst-case: $O(1)$
* Other technical:
    * Unstable
    * In-place
    * Only works with random-access iterators (in C++ terminology)

Notes:
* This implementation uses the gap sequence ${1, 4, 13, 40, 121, 364}$. It's a cut-off version of Donald Knuth's sequence $(u_k): u_1 = 1, u_{n+1} = 3u_n + 1$.
