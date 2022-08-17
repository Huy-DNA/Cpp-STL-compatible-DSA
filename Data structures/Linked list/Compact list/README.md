# Compact List
Notes about this implementation of Compact List (`CompactList`):
* Supported operations and their computational complexity: With $n$ being the number of elements,
    * **SEARCH**: 
        * `CompactList::search(element)`
            * Worst-case auxiliary space: $\Theta(1)$
            * Worst-case running time: $\Theta(n)$
        * `CompactList::sorted_search(element)` - <span style="color:#FF0000"> Requires the list to be sorted </span>
            * Worst-case auxiliary space: $\Theta(1)$
            * Worst-case running time: $\Theta(n)$
            * Expected running time: $\Theta(\sqrt{n})$ (improved!) - <span style="color:#FF0000"> But all elements need to be distinct. </span>
    * **INSERT**: `CompactList::push_back(element)`, `CompactList::push_front(element)`, `CompactList::insert_after(iterator, element)`, `CompactList::insert_before(iterator, element)` 
        * Worst-case auxiliary space: $\Theta(n)$ (when the underlying array is doubled)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `CompactList::pop_back()`, `CompactList::pop_front()`, `CompactList::remove(iterator)`
        * Worst-case auxiliary space: $\Theta(n)$ (when the underlying array is halved)
        * Amortized running time: $\Theta(1)$
* Other technical:
    * The underlying array for holding the elements is dynamic so there's no concrete upper bound for the number of elements `CompactList` can hold.
    * Range-based for loop is supported.
    * The Merge sort algorithm implemented in `Merge sort.h` can be used to sort the list.
    * Only works with elements of `TriviallyCopyableType`.

Notes:
* In Compact List, array indices act like `next` and `prev` pointers in regular Linked Lists. We don't need any pointers here so this can be implemented in languages that do not have pointers.
* Additionally, every meaningful array elements (that is, array elements that representing some list elements) reside leftmost of the array.
* `CompactList` uses more memory than `LinkedList` and still cause memory fragmentation just as normal array.

Things I want to improve:
* More efficient search on Compact List after Merge sort for Linked List is implemented.
