# Radix sort
Notes about this implementation of radix sort:
* Assumptions:
    * Every element is of some integral type or has an integral-typed field named 'key'.
    * Every element or its 'key' value lies within [0, k], for some non-negative integer k. (actually this information is used to infer how many bits are sufficient to represent every element, unlike Counting sort)
* Time complexity: Let $B$ be the number bits used to represent all of the elements,
    * Average-case running time: $\Theta(n + nB/\lfloor\lg n\rfloor)$
    * Best-case running time: $\Theta(n + nB/\lfloor\lg n\rfloor)$
    * Worst-case running time: $\Theta(n + nB/\lfloor\lg n\rfloor)$
* Space complexity: $\Theta(n)$
* Other technical:
    * Stable
    * NOT in-place
    * Only works with random-access iterators (in C++ terminology)

Notes:
* In general, Radix sort's worst-case running time is: $T(n) = \Theta(d(n+b))$, with $b$ being the base in which the numbers are being represented, $d$ being the maximum number of digits used to represent each of the numbers in base $b$, $n$ being the number of elements.
* With my implementation:
    * $b = 2^r$, $r = \lfloor\lg n \rfloor$.
    * Let $B$ be the maximum number of bits used to represent each of the numbers. Then, $d = \lceil B /r\rceil$.  
Taken all together, we have $T(n) = \Theta(\lceil B/r \rceil(n+2^{\lfloor \lg n \rfloor})) = \Theta(n+ nB/\lfloor \lg n \rfloor)$.
    * Let $k$ be the maximum number. If $k = \Theta(n^c)$ for some constant $c$, then $B = c \Theta(\lg n) = \Theta(\lg n)$ which implies $T(n) = \Theta(n)$. 
    
This is an improvement over Counting sort!!!

* Whether Radix sort or Quick sort is preferred depends: Radix sort does not utilize cache memory as efficiently as Quick sort and it does not sort in-place, although having asymtotically better worst-case running time.
