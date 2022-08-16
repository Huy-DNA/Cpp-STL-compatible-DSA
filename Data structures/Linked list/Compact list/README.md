# Compact List
Notes about this implementation of Compact List (`CompactList`):
* Supported operations and their computational complexity: With $n$ being the number of elements,
    * **SEARCH**: `CompactList::search(element)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(n)$
    * **INSERT**: `CompactList::push_back(element)`, `CompactList::push_front(element)`, `CompactList::insert_after(iterator, element)`, `CompactList::insert_before(iterator, element)` 
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
    * **DELETE**: `CompactList::pop_back()`, `CompactList::pop_front()`, `CompactList::remove(iterator)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
* Other technical:
    * Range-based for loop is supported.
    * Only works with elements of `TriviallyCopyableType`.

Notes:
* In Compact List, array indices act like `next` and `prev` pointers in regular Linked Lists. We don't need any pointers here so this can be implemented in languages that do not have pointers.
* Additionally, every meaningful array elements (that is, array elements that representing some list elements) reside leftmost of the array.
* If the Compact List's elements are sorted, there's a search algorithm on the list that yields asymtotically better expected running time than $\Theta(n)$.

Things I want to improve:
* More efficient search on Compact List after Merge sort for Linked List is implemented.
