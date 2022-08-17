# Linked List
Notes about this implementation of Linked List (`LinkedList`):
* Supported operations and their computational complexity: With $n$ being the number of elements,
    * **SEARCH**: `LinkedList::search(element)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(n)$
    * **INSERT**: `LinkedList::push_back(element)`, `LinkedList::push_front(element)`, `LinkedList::insert_after(iterator, element)`, `LinkedList::insert_before(iterator, element)` 
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
    * **DELETE**: `LinkedList::pop_back()`, `LinkedList::pop_front()`, `LinkedList::remove(iterator)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(1)$
* Other technical:
    * This is technically a circular linked list with the sentinel closing the circle.
    * Range-based for loop is supported.
    * The Merge sort algorithm implemented in `Merge sort.h` can be used to sort the list.
    * Only works with elements of `TriviallyCopyableType`.

Things I want to improve:
* (*Done - 15/08/2022 1:13 AM*) Maybe using a sentinel to properly implement `LinkedList::end()`?
* Seriously, I don't even know if all of those templates would work correctly.
* (*Done - 16/08/2022 11:25 PM*) Implements Merge sort for Linked list.

Things I've learnt anyways (or I've already known but it's good to reiterate):
* `typename` should precede subtypes of templated class. By default, the compiler treats `A<T>::B` as a member variable (do I remember correctly??) if `T` is a dependent typename.
* Nested types can not be used in partial specializations. For example, before arriving at this implementation, I did this and it didn't work.
```C++
template <...>
class LinkedList {
    ...
    class NonConstBiIter {
        ...
    };
};
...
//Doesn't work!!!
template <typename Elem_T>
class std::iterator_traits<typename LinkedList<Elem_T>::NonConstBiIter> {
    ...
};
```
Well, I can see the reason why though --- if this were to be allowed, suppose the compiler comes across something like this:
```C++
std::iterator_traits<int*> ...
```
By default, there's already a partial specialization for `std::iterator_traits<int*>` - If  `LinkedList<Elem_T>::NonConstBiIter` were a `typedef` for `int*`, which one should the compiler choose??

For the same reason, this doesn't work either:
```C++
//Doesn't work either!!!
template <typename LinkedList_T>
class std::iterator_traits<typename LinkedList_T::NonConstBiIter> {
    ...
};
```
Moreover, in this particular situation, even if there are no clashing specializations, to check whether a partial specialization for `int*` exists, the compiler would have to check all available types and their corresponding `NonConstBiIter` subtypes to see if there are any `typedef`s for `int*` -- which is so impractical.
