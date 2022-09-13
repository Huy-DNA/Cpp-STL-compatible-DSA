# Red Black Tree
* Supported operations and their computational complexity: With $n$ being the number of elements,
    * **SEARCH**: `RedBlackTree::search(element)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **INSERT**: `RedBlackTree::insert(element)` 
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **DELETE**: `RedBlackTree::remove(iterator)`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **MINIMUM**: `RedBlackTree::minimum()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **MAXIMUM**: `RedBlackTree::maximum()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **SUCCESSOR**: `RedBlackTree::succesor()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
    * **PREDECESSOR**: `RedBlackTree::predecessor()`
        * Worst-case auxiliary space: $\Theta(1)$
        * Worst-case running time: $\Theta(\lg n)$
* Other technical:
    * Only works with elements of `TriviallyCopyableType`.

Things I want to improve:
* Is static data member's out-of-class definition of a class template inline?
* Using `const_cast` is bad and my current design makes it unable to provide const version of all methods of the class!
* Currently, most class methods accept an argument of a user-defined Iterator type. This type is just acting as a safe wrapper around an internal `Node` pointer so that outside users can not modify the internal data, otherwise, Red Black Tree's assumptions would be violated. However, this leads to the mentioned-above problem and some cumbersome situation, like this one in `RedBlackTree::remove()`:
```C++
Node* m = _extract_Node(minimum_at_subtree(_create_ConstRBBiIter(node->right)));
```

Things I've learnt anyways:
* Out-of-template-class definitions of static data members like this do not work:
```C++
template <typename Elem_T, typename Comp_T>
typename RedBlackTree<Elem_T, Comp_T>::Node RedBlackTree<Elem_T, Comp_T>::_sentinel = {{}, _NIL, _NIL, _NIL, BLACK};
```
or this:
```C++
template <typename Elem_T, typename Comp_T>
typename RedBlackTree<Elem_T, Comp_T, void>::Node RedBlackTree<Elem_T, Comp_T, void>::_sentinel = {{}, _NIL, _NIL, _NIL, BLACK};
```
but this works:
```C++
template <typename Elem_T, typename Comp_T, typename _SFINAE>
typename RedBlackTree<Elem_T, Comp_T, _SFINAE>::Node RedBlackTree<Elem_T, Comp_T, _SFINAE>::_sentinel = {{}, _NIL, _NIL, _NIL, BLACK};
```
The only reason I can come up is because these kinds of definition need explicity in the class of which the static data member is being defined. Seems reasonable but not totally convincing.

## Details about Red Black Tree
