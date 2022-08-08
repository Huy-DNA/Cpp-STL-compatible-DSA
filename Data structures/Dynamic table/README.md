# Dynamic Table
Notes about this implementation of Dynamic Table (DynamicTable):
* Supported operations and their computational complexity:
    * **INSERT**: **DynamicTable**::push_back(*element*)
        * Worst-case auxiliary space: $\Theta(n)$ (when doubling capacity)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: **DynamicTable**::pop_back()
        * Worst-case auxiliary space: $\Theta(n)$ (when shrinking capacity)
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * Each time the internal buffer has to grow or shrink, the elements have to be copied, which triggers the type's copy constructor. This could be undesirable.
    * It doesn't emulate vector well in many cases like when the element is popped, when the redundant array slots are first allocated,...
## Proof for armotized running time of **INSERT** and **DELETE** operations