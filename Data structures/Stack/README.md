# Stack
Notes about this implementation of Stack:
* Supported operations and their computational complexity:
    * **INSERT**: **Stack**::push(*element*)
        * Worst-case auxiliary space: $\Theta(n)$
        * Amortized running time: $\Theta(1)$
    * **DELETE**: **Stack**::pop()
        * Worst-case auxiliary space: $\Theta(n)$
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * This just uses DynamicTable underneath.
    * Only works with elements of TriviallyCopyableType.
