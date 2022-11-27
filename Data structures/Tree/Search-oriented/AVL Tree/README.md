# AVL Tree (Balanced Binary Search Tree)
* Supported operations and their computational complexity: With $n$ being the number of elements,
    * **SEARCH**: `AVLTree::search(element)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **INSERT**: `AVLTree::insert(element)` 
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **DELETE**: `AVLTree::remove(iterator)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **MINIMUM**: `AVLTree::minimum()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **MAXIMUM**: `AVLTree::maximum()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **SUCCESSOR**: `AVLTree::successor()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **PREDECESSOR**: `AVLTree::predecessor()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
* Other technical:
    * Only works with elements of `TriviallyCopyableType`.
    * This implementation stores in each node its height to detect imbalance, could've stored balance factor instead.