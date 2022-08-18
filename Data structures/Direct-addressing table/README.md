# Direct Addressing Table
Notes about this implementation of Direct-addressing Table (`DirectAddressingTable`):
* Supported operations and their computational complexity: With $k$ being the maximum key.
    * *Initialization*: $\Theta(k)$ time, $\Theta(k)$ space
    * **SEARCH**: `DirectAddressingTable::operator[](key)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
    * **INSERT**: `DirectAddressingTable::insert(key, value)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
    * **DELETE**: `DirectAddressingTable::remove(key)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
* Other technical:
    * Keys must be non-negative integers and upper bounded by a specified number.
    * Only works with values of `TriviallyCopyableType`.

Notes:
* Direct Addressing Table should only be used when the key set is reasonably small. Although it has asymtotically optimal worst-case running time for all of the *dictionary* operations, if the set of possible keys is huge (or can be infinite), it's impractical to use this data structure. Another downside is that there are often many empty slots in the table, which is a big waste of memory.
