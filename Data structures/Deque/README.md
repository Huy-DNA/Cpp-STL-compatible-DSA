# Deque
> I kept running into SIGTRAP when the destructor is executed. I managed to narrow down the problem to when a `Deque` is pushed on and popped back to empty - the internal `_buffer` doesn't seem valid after that. I was confused because it worked just fine with `Queue`. Actually I did make some 'innocent-looking' modifications to `Queue` and then copied it over to `Deque`... guess what? `Queue` ran into the same problem as `Deque`. However, I was too stubborn and convinced myself that the aformentioned modification couldn't have broken the program. Consequently, although I did find the potential source of bugs, I avoided looking into it thoughtfully and wasting a lot of time getting frustrated and now ranting about it :).
> Moral of the story:
> * Don't assume anything that you just did is innocent but rather test it carefully before you move on.
> * If you've identified the source of the problem, look into it! - even though you're sooo convinced that there couldn't be anything wrong with it.

Notes about this implementation of Deque (`Deque`) - I previously mistaken it with Dequeue LOL:
* Supported operations and their computational complexity:
    * **INSERT**: `Deque::push_front(element)`, `Deque::push_back(element)`
        * Worst-case auxiliary space: $\Theta(n)$ (when doubling capacity)
        * Amortized running time: $\Theta(1)$
    * **DELETE**: `Deque::pop_front()`, `Deque::pop_back()`
        * Worst-case auxiliary space: $\Theta(n)$ (when shrinking capacity)
        * Amortized running time: $\Theta(1)$ 
* Other technical:
    * Each time the internal buffer has to grow or shrink, the elements have to be copied, which triggers the type's copy constructor. This could be undesirable.
    * Only works with elements of `TriviallyCopyableType`.

Things I want to improve:
* The object's internal state is mutated a lot by its private methods. I don't think this is good practice.