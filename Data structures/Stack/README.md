# Stack
Notes about this implementation of Stack (`Stack`):
* Supported operations and their computational complexity:
    * **INSERT**: `Stack::push(element)`
        * Worst-case auxiliary space: $\Theta(n)$
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `Stack::pop()`
        * Worst-case auxiliary space: $\Theta(n)$
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * This just uses `DynamicTable` underneath so that it can shrink and grow according to the current number of elements.
    * Only works with elements of `TriviallyCopyableType`.
