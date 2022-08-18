# Direct Addressing Table - No Null Marking
Notes about this implementation of Direct-addressing Table (`DirectAddressingTable`):
* Supported operations and their computational complexity: With $k$ being the maximum key.
    * *Initialization*: $\Theta(1)$ time (improved!), $\Theta(k)$ space
    * **SEARCH**: `DirectAddressingTable::operator[](key)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
    * **INSERT**: `DirectAddressingTable::insert(key, value)`
        * Worst-case auxiliary space: $\Theta(n)$ (when `DirectAddressingTable::_id_stack` is doubled)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `DirectAddressingTable::remove(key)`
        * Worst-case auxiliary space: $\Theta(n)$ (when `DirectAddressingTable::_id_stack` is halved)
        * Amortized running time: $\Theta(1)$
* Other technical:
    * Keys must be non-negative integers and upper bounded by a specified number.
    * Only works with values of `TriviallyCopyableType`.
    * Requires no non-trivial initialization.

Notes:
* If you're working with a large set of keys, initial initialization every slot to NULL might be undesirable, as it's time-consuming, so this implementation might be more desirable. However, insertion and deletion operations are slightly slower and may also use auxiliary memory.
* There's a trade off between time and space. Two more arrays, one dynamic, one static must be created. With an already large set of keys, this may be unwanted, too!! I've tried to address this by using the least unsigned integer type to store the index.

Things I've learnt from this:
* When I coded `DynamicTable`, I thought I would only need to code the non-const `DynamicTable::operator[](size_t)`. It's because I thought under no circumstances would someone want a constant dynamic array -- it sounds dumb right. However, I soon realized I needed it because I need to call that method from a constant method inside another class (`DirectAddressingTable::null_at(size_t key)`). In conclusion, it's good practice to just write both non-const and const version - it might not seem apparent at first but is essential in some cases like when you need to call it from a const method.
