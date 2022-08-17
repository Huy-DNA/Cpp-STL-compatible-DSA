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
            * Expected running time: $O(\sqrt{n})$ (improved!) - <span style="color:#FF0000"> But all elements need to be distinct. </span>
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

## Proof for $\Theta(\sqrt{n})$ expected running time of `CompactList::sorted_search`
Suppose we have a `CompactList` with $n$ elements.

Three things to keep in mind:
* The list is compact, which means all of those elements all reside in the first $n$ slots of the underlying array.
* All elements must be distinct.
* The elements are sorted in increasing order.

### Understanding `CompactList::sorted_search`
Look at the code for `CompactList::sorted_search`:
```C++
CompactListNonConstBiIter<Elem_T> sorted_search(const Elem_T& e, const std::function<bool(const Elem_T&, const Elem_T&)>& less = std::less<const Elem_T&>{}) {
        static std::mt19937_64 mt;
        std::uniform_int_distribution<size_t> gen {0, _size - 1};
        long long cur = _head;
        while (cur != _NIL && less(_buffer[cur].data, e)) {
            long long random_pos = gen(mt);
            if (_buffer[random_pos].data == e) return _create_iterator(random_pos);
            if (less(_buffer[random_pos].data, e) && less(_buffer[cur].data, _buffer[random_pos].data))
                cur = random_pos;
            cur = _buffer[cur].next;
        }
        if (cur == _NIL || less(e, _buffer[cur].data)) cur = _INVALID;
        return _create_iterator(cur);
    }
```
Hard to understand, right??? -- all these language's quirks and implementation details. Let's use pseudocode instead.

Think of the `CompactList` instance as an obj `l` having 4 interested fields: `size`, `val`, `next` and `head`.
* The number of elements in the list is stored in `l.size`. 
* We can access the Linked list's elements by indexing `l.val` like `l.val[i]`. Notice that `i` always lies in the range $[0,$ `l.size` $ - 1]$.
* `l.next[i]` is the index of the next element in the list, which means `l.val[l.next[i]]` is the element next to `l.val[i]`.
* `l.head` is the index of the first element in the list.
* The last element in the list will point to a sentinel value `NIL`.

Also think of `sorted_search` as a function `SORTED-SEARCH` that takes in a Compact List `l` and an element `e` to be searched.

The pseudocode would be:
```ada
SORTED-SEARCH(l, e):
    cur = l.head
    WHILE cur != NIL && l.val[cur] < e:
        random-pos = RANDOM(0, l.size - 1)
        random-e   = l.val[random-pos]
        IF random-e == e:
            RETURN random-pos
        IF random-e < e && l.val[cur] < random-e:
            cur = random-pos
        cur        = l.next[cur]
    IF cur == NIL || e < l.val[cur]:
        RETURN NIL
    RETURN cur
```

So basically, instead of just scanning sequentially all the list elements for the desired one, we take SHORTCUTS~~~
* First randomly pick a random element in the list (we can do this because we know all elements lies in $[0,$ `l.size` $-1]$).
* Then, determine whether it's safe to "jump" to this element. It should be safe if the element lies somewhere between the current elements and the desired element (if any) in the list. Because we know that the list is sorted, we can infer this information by comparing the picked element with the desired and current one. It it's safe, jump to it! If it's not safe, just ignore it.
* Finally, we just advance to the next element, either from the just-jumped-to element or the current element (if we didn't do the jump).

OK. Now we got the intuition -- we're ready to slay!
### Proof
You may wonder, if we just randomly pick an element, determine whether it's safe to jump to it, then do the jump if it's really is -- all without manually advancing to the next element, how far can we expect to get? That is with this function,
```ada
ONLY-JUMP(l, e, steps):
    cur = l.head
    FOR step IN 0..steps:
        random-pos = RANDOM(0, l.size - 1)
        random-e   = l.val[random-pos]
        IF random-e == e:
            RETURN random-pos
        IF random-e < e && l.val[cur] < random-e:
            cur    = random-pos
        -- cur        = l.next[cur]
    RETURN cur
```
what do I expect it to return?

We can formulate this as a mathematical problem:
> Given a sequence of number $1, 2, \cdots, n$. You wish to get as close as possible to a real number $m$. You know there exists a number $0 \le k \le n$ such that $k \le m < k + 1$. In getting there, you must conform to some rule:
> * Initially you're at number $0$.
> * Each step, pick a random number $i$ in $[1, n]$. If $i > m$, stay where you are. Otherwise, you can choose to jump to $i$ (Of course, you should only jump if $i$ is closer to $m$ than where you're currently at!).

> You want to know with $s$ steps, how far you can *expect* to get?

Side note: The case where $m > k$ is equivalent to the case where the $k^{th}$ element in the linked list is the last element to be less than $e$, and $m = k$ means the $k^{th}$ element is the desired one. 

Denote $i_t$ as the number you draw at at step $t$, $y_t = i_t$, when $i_t \le k$, otherwise $y_t = 0$.

Essentially, the problem asks you to determine $E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}]$. However, approximating $E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}]$ is sufficient for the purpose of this whole proof.

Notice that $\displaystyle \max_{1 \le t \le s}\{0, y_t\}$ always lies within $[0, k]$.

With $s$ steps, for each $i$ in $[1..k]$,  
$P(\displaystyle\max_{1 \le t \le s}\{0, y_t\} = i) = \frac{1}{n^s}\begin{pmatrix}(n-k+i)^s - (n -k + i - 1)^s\end{pmatrix}$

Therefore,  
$E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}] = \displaystyle \frac{1}{n^s}\sum_{i=1}^k i\begin{pmatrix}(n-k+i)^s - (n-k+i-1)^s\end{pmatrix} = \frac{1}{n^s}\begin{pmatrix}kn^s-(n-1)^s - (n-2)^s - \cdots - (n-k)^s\end{pmatrix} = k - \begin{pmatrix}\displaystyle(1-\frac{1}{n})^s+(1-\frac{2}{n})^s+\cdots+(1-\frac{k}{n})^s\end{pmatrix}\ge k - \displaystyle f(\frac{1}{n})-f(\frac{2}{n})-\cdots-f(\frac{k}{n})$.

Here, $f(x)=(1-x)^s$.

Because $f$ is a decreasing function in $[0, 1]$,  
$\displaystyle \frac{1}{n} \sum_{i=1}^{k} f(\frac{i}{n}) \le \int_0^{\frac{k}{n}}f(x)dx=\frac{1-(1-\frac{k}{n})^{s+1}}{s+1}$.

Hence, $E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}] \ge k - n\cdot\frac{1-(1-\frac{k}{n})^{s+1}}{s+1}$.

We can see the greater the value of $s$, the greater the lower bound of $E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}]$

Consequently, for $s \ge \sqrt{n} - 1$, $E[\displaystyle \max_{1 \le t \le s}\{0, y_t\}] \ge k -\sqrt{n}\begin{pmatrix}1-(1-\frac{k}{n})^{\sqrt{n}}\end{pmatrix} \ge k - \sqrt{n}$.

What this means is that if we repeat the above process of pick, check and jump about $\sqrt{n}$ times, we can expect to be at least at position $k-\sqrt{n}$. We can only appreciate this result if we look at this procedure:
```ada
JUMP-FIRST(l, e):
    cur = l.head
    -- we jump first
    FOR step IN 0..sqrt(l.size): -- iterate sqrt(n) times
        random-pos = RANDOM(0, l.size - 1)
        random-e   = l.val[random-pos]
        IF random-e == e:
            RETURN random-pos
        IF random-e < e && l.val[cur] < random-e:
            cur    = random-pos
    
    -- we then advance
    WHILE cur != NIL && l.val[cur] != e:
        cur  = l.next[cur]
    
    -- finally check and return
    IF cur == NIL || e < l.val[cur]:
        RETURN NIL
    RETURN cur
```

In `JUMP-FIRST`, we first repeat the whole process $\sqrt{n}$ times, then manually advancing until we either find the desired element or hit `NIL` or an element that is greater than `e`. Because after the whole jumping process, we expect to be at least at the $(k-\sqrt{n})^{th}$ element, we can hope that we only need to advance about $\sqrt{n}$ times to get to the $k^{th}$ element (which is either the desired element or the last element that is less than `e`).

Hence, the expected running time of `JUMP-FIRST` is $O(\sqrt{n})$.

Finally, convince yourself that `SORTED-SEARCH` is just a more optimized version of `JUMP-FIRST`, in which we jump and advance at the same time.

We can conclude the proof here.
