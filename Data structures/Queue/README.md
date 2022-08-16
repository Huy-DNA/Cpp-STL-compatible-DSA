# Queue 
Notes about this implementation of Queue (`Queue`):
* Supported operations and their computational complexity:
    * **INSERT**: `Queue::enqueue(element)`
        * Worst-case auxiliary space: $\Theta(n)$ (when doubling capacity)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `Queue::dequeue()`
        * Worst-case auxiliary space: $\Theta(n)$ (when shrinking capacity)
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * Each time the internal buffer has to grow or shrink, the elements have to be copied, which triggers the type's copy constructor. This could be undesirable.
    * Only works with elements of `TriviallyCopyableType`.

Notes:
* This implementation keeps track of a `_head` index and an implicit tail index (inferred from `_size`) - essentially it's a circular buffer, where the contiguous sequence of elements get wrapped around in the underlying buffer. This gives us flexibility in how we manipulate the two ends of the sequence. As we'll see, this allows us to implement **Deque**, a *sequential container* (in C++ terminology) of which you can append elements to both two ends. 