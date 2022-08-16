# Dynamic Table
Notes about this implementation of Dynamic Table (`DynamicTable`):
* Supported operations and their computational complexity:
    * **INSERT**: `DynamicTable::push_back(element)`
        * Worst-case auxiliary space: $\Theta(n)$ (when doubling capacity)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `DynamicTable::pop_back()`
        * Worst-case auxiliary space: $\Theta(n)$ (when shrinking capacity)
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * Each time the internal buffer has to grow or shrink, the elements have to be copied, which triggers the type's copy constructor. This could be undesirable.
    * It doesn't emulate vector well in many cases like when the element is popped, when the redundant array slots are first allocated,...
    * Only works with elements of `TriviallyCopyableType`.

Things I want to improve:
* Support (or more thoroughly support) `DynamicTable::begin`, `DynamicTable::end`, `DynamicTable::cbegin`, `DynamicTable::cend`, `DynamicTable::rbegin` and `DynamicTable::rend` so that `DynamicTable` could be used in sorting and selection algorithms I have implemented as well as used in element-wise for loop.
## Proof for armotized running time of **INSERT** and **DELETE** operations
