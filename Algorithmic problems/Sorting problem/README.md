# Sorting problem

* Input: A sequence of $n$ elements $\lt e_1, e_2, \cdots, e_n \gt$.
* Output: A permutation of the sequence $\lt \sigma_1, \sigma_2, \cdots, \sigma_n \gt$ such that
$\sigma_1 \le \sigma_2 \le \cdots \sigma_n$.

A sorting algorithm is said to be:
* **stable**, if $\sigma_i = \sigma_j$ implies $i' < j' \iff i < j$ for all $i \neq j$. (with $e_{i'}$ corresponds to $\sigma_i$, $e_{j'}$ corresponds to $\sigma_j$)
* **in-place**, if the algorithm uses only $\Theta(1)$ auxiliary space. A $O(\lg n)$ space algorithm can sometimes be acceptable as an in-place algorithm.
