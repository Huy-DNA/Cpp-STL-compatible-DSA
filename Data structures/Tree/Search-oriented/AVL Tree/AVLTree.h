#ifndef __AVL_TREE_HELL__
#define __AVL_TREE_HELL__

#include <type_traits>
#include <stdexcept>
#include <functional>

template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class ConstAVLBiIter;

template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class AVLTree {
    typedef std::size_t size_t;

    struct Node {
        Elem_T data;
        Node* left;
        Node* right;
        Node* p;
        size_t height;
    };
public:
    ~AVLTree() {

    }

    ConstAVLBiIter search(const Elem_T& e) {

    }

    void insert(const Elem_T& e) {

    }

    Elem_T remove(ConstAVLBiIter iter) {

    }

    ConstAVLBiIter minimum_at_subtree(ConstAVLBiIter iter) {

    }

    ConstAVLBiIter maximum_at_subtree(ConstAVLBiIter iter) {

    }

    ConstAVLBiIter minimum() {

    }

    ConstAVLBiIter maximum() {

    }

    ConstAVLBiIter predecessor(ConstAVLBiIter iter) {

    }

    ConstAVLBiIter successor(ConstAVLBiIter iter) {

    }

    void print() const {

    }
private:
    void _insert_fixup(Node* u) {

    }

    void _remove_fixup(Node* u) {

    }

    void _transplant(Node* u, Node* v) {

    }

    void _left_rotate(Node* u) {

    }

    void _right_rotate(Node* v) {

    }

    Node* _extract_Node(ConstAVLBiIter iter) {

    }

    ConstAVLBiIter _create_ConstAVLBiIter(ConstAVLBiIter iter) {

    }

    void _deallocate_node(Node* u) {

    }

    static const Comp_T _less{};
    Node* _root = _NIL;
    static inline Node _sentinel;
    constexpr static Node* _NIL = &_sentinel;
};

template <typename Elem_T, typename Comp_T, typename _SFINAE>
AVLTree<Elem_T, Comp_T, _SFINAE>::Node AVLTree<Elem_T, Comp_T, _SFINAE>::_sentinel{{}, &_sentinel, &_sentinel, &_sentinel, -1};


template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class ConstAVLBiIter {

};

template <typename Elem_T, typename Comp_T>
struct std::iterator_traits<ConstAVLBiIter<Elem_T, Comp_T>> {

};

#endif