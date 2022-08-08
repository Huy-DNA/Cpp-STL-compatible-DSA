# Dynamic Table
Notes about this implementation of Dynamic Table (DynamicTable):
* Supported operations and their computational complexity:
    * **INSERT**: **DynamicTable**::push_back(*element*)
        * Worst-case auxiliary space: $\Theta(n)$ (when doubling capacity)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: **DynamicTable**::pop_back()
        * Worst-case auxiliary space: $\Theta(n)$ (when shrinking capacity)
        * Amortized running time: $\Theta(1)$

## Proof for armotized running time of **INSERT** and **DELETE** operations
To be added.........................