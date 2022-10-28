#ifndef __AVL_TREE_HELL__
#define __AVL_TREE_HELL__

#include <type_traits>
#include <stdexcept>
#include <functional>
#include <iostream>

template <typename Elem_T, typename Comp_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class ConstAVLBiIter;

template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class AVLTree {
    typedef std::size_t size_t;
    typedef ConstAVLBiIter<Elem_T, Comp_T> ConstAVLBiIter;
    friend ConstAVLBiIter;

    struct Node {
        Elem_T data;
        Node* left;
        Node* right;
        Node* p;
        size_t height;          // maximum level + 1
    };
public:
    ConstAVLBiIter search(const Elem_T& e) {
        Node* cur = _root;
        while (cur != _NIL && cur->data != e) {
            if (_less(cur->data, e))
                cur = cur->right;
            else cur = cur->left;
        }
        return _create_ConstAVLBiIter(cur);
    }

    ConstAVLBiIter minimum() const {
        return minimum_at_subtree(_root);
    }

    ConstAVLBiIter maximum() const {
        return maximum_at_subtree(_root);
    }

    ConstAVLBiIter minimum_at_subtree(ConstAVLBiIter iter) {
        Node* nptr = _extract_Node(iter);
        if (nptr == _NIL)
            return _create_ConstAVLBiIter(_NIL);
        while (nptr->left != _NIL)
            nptr = nptr->left;
        return _create_ConstAVLBiIter(nptr);
    }

    ConstAVLBiIter maximum_at_subtree(ConstAVLBiIter iter) {
        Node* nptr = _extract_Node(iter);
        if (nptr == _NIL)
            return _create_ConstAVLBiIter(_NIL);
        while (nptr->right != _NIL)
            nptr = nptr->right;
        return _create_ConstAVLBiIter(nptr);
    }

    ConstAVLBiIter predecessor(ConstAVLBiIter iter) {
        Node* nptr = _extract_Node(iter);
        if (nptr == _NIL)
            return _create_ConstAVLBiItier(_NIL);
        else if (nptr->left != _NIL)
            return maximum_at_subtree(nptr->left);
        else while (nptr->p != _NIL && nptr->p->right != nptr)
            nptr = nptr->p;
        return _create_ConstAVLBiIter(nptr->p);
    }

    const Node* successor(const Node* iter) {
        Node* nptr = _extract_Node(iter);
        if (nptr == _NIL)
            return _create_ConstAVLBiIter(_NIL);
        else if (nptr->right != _NIL)
            return minimum_at_subtree(nptr->right);
        else while (nptr->p != _NIL && nptr->p->left != nptr)
            nptr = nptr->p;
        return _create_ConstAVLBiIter(nptr->p);
    }

    void insert(const Elem_T& e) {
        Node* new_node = new Node{e, _NIL, _NIL, _NIL, 1};
        
        if (_root == _NIL) {
            _root = new_node;
            return;
        }

        Node* cur = _root;
        Node* prev = _NIL;
        while (cur != _NIL) {
            prev = cur;
            if (_less(cur->data, e))
                cur = cur->right;
            else cur = cur->left;
        }
        if (_less(prev->data, e))
            prev->right = new_node;
        else prev->left = new_node;
        new_node->p = prev;

        _insert_fixup(new_node);
    }

    void remove(const Elem_T& e) {
        remove(search(e));
    }

    Elem_T remove(ConstAVLBiIter iter) {
        Node* u = _extract_Node(iter);
        if (u == _NIL)
            throw std::runtime_error{"AVLTree::remove() called on null pointer."};
        
        Node* to_be_fixed = u->p;
        Node* fixed_child;
        if (u->left == _NIL) {
            _transplant(u, u->right);
            fixed_child = u->right;
        }
        else if (u->right == _NIL) {
            _transplant(u, u->left);
            fixed_child = u->left;
        }
        else {
            Node* v = _extract_Node(minimum_at_subtree(_create_ConstAVLBiIter(u->right)));
            if (v->p != u) {
                to_be_fixed = v->p;
                fixed_child = v->right;
                _transplant(v, v->right);
                v->right = u->right;
                u->right->p = v;
            } else {
                to_be_fixed = v;
                fixed_child = v->right;
            }
            _transplant(u, v);
            v->left = u->left;
            u->left->p = v; 
            v->height = u->height;
        }
        Elem_T res = u->data;
        delete u;
        _remove_fixup(to_be_fixed, fixed_child);
        return res;
    }
    
    void print() const {
        _print_recur("", _root, false);
    }

    ~AVLTree() {
        _deallocate_node(_root);
    }
private:
    void _print_recur(const std::string& prefix, const Node* node, bool isLeft) const {
        /*From: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c*/
        if (node != _NIL) {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->data << '\n';

            // enter the next tree level - left and right branch
            _print_recur(prefix + (isLeft ? "│   " : "    "), node->left, true);
            _print_recur(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

    void _insert_fixup(Node* u) {
        bool taller = true;
        while (taller && u != _root) {
            Node* v = u->p;
            
            if (v->left == u) {
                Node* m = v->right;             //u's sibling
                v->height = u->height + 1;
                switch (u->height - m->height) {
                    case 0:
                        taller = false;
                        break;
                    case 1:
                        if (v->p->right == v) {
                            _right_rotate(v);
                            v = v->p;
                        }
                        u = v;
                        v = v->p;
                        break;
                    case 2:
                        _right_rotate(v);
                        taller = false;
                        break;
                }
            } else {
                Node* m = v->left;              //u's sibling
                v->height = u->height + 1;
                switch (u->height - m->height) {
                    case 0:
                        taller = false;
                        break;
                    case 1:
                        if (v->p->left == v) {
                            _left_rotate(v);
                            v = v->p;
                        }
                        u = v;
                        v = v->p;
                        break;
                    case 2:
                        _left_rotate(v);
                        taller = false;
                        break;
                }
            }
        }
    }

    void _remove_fixup(Node* v, Node* u) {
        //v is the root of the smallest subtree that may be imbalanced due to previous deletion
        //u is the child of p that is balanced but there's a node in its branch that was deleted
        bool shorter = true;
        while (shorter && u != _root) {
            if (u == v->left) {
                Node* m = v->right;             //u's sibling
                v->height = 1 + std::max(m->height, u->height);
                switch (m->height - u->height) {
                    case 0:
                        u = v;
                        v = v->p;
                        break;
                    case 1:
                        shorter = false;
                        break;
                    case 2:
                        if (m->right->height < m->left->height) {
                            _right_rotate(m);
                            _left_rotate(v);
                            shorter = false;
                        }
                        else {
                            _left_rotate(v);
                            u = v->p;
                            v = u->p;
                        }
                        break;
                }
            } else {
                Node* m = v->left;                  //u's sibling
                v->height = 1 + std::max(m->height, u->height);
                switch (m->height - u->height) {
                    case 0:
                        u = v;
                        v = v->p;
                        break;
                    case 1:
                        shorter = false;
                        break;
                    case 2:
                        if (m->left->height < m->right->height) {
                            _left_rotate(m);
                            _right_rotate(v);
                            shorter = false;
                        }
                        else {
                            _right_rotate(v);
                            u = v->p;
                            v = u->p;
                        }
                        break;
                }
            }
        }
    }

    //Note: transplant does not update node's height
    void _transplant(Node* u, Node* v) {
        v->p = u->p;
        
        if (u->p == _NIL)
            _root = v;
        else if (u->p->left == u)
            u->p->left = v;
        else u->p->right = v;
    }

    void _left_rotate(Node* u) {
        if (u->right == _NIL) return;
        Node* v = u->right;

        v->p = u->p;

        if (u->p == _NIL)
            _root = v;
        else if (u->p->left == u)
            u->p->left = v;
        else u->p->right = v;

        u->right = v->left;

        if (v->left != _NIL)
            v->left->p = u;
        
        v->left = u;
        u->p = v;

        u->height = 1 + std::max(u->left->height, u->right->height);
        v->height = 1 + std::max(v->left->height, v->right->height);
    }

    void _right_rotate(Node* u) {
        if (u->left == _NIL) return;
        Node* v = u->left;

        v->p = u->p;

        if (u->p == _NIL)
            _root = v;
        else if (u->p->left == u)
            u->p->left = v;
        else u->p->right = v;

        u->left = v->right;

        if (v->right != _NIL)
            v->right->p = u;
        
        v->right = u;
        u->p = v; 
        
        u->height = 1 + std::max(u->left->height, u->right->height);
        v->height = 1 + std::max(v->left->height, v->right->height);
    }

    void _deallocate_node(Node* u) {
        if (u == _NIL) return;
        _deallocate_node(u->left);
        _deallocate_node(u->right);
        delete u;
    }

    ConstAVLBiIter _create_ConstAVLBiIter(const Node* node) {
        return {node, *this};
    }

    Node* _extract_Node(ConstAVLBiIter iter) {
        return const_cast<Node*>(iter._node);       //Bad: const_cast but...
    }

    Node* _root = _NIL;
    Comp_T _less{};
    static Node _sentinel;
    static constexpr Node* _NIL = &_sentinel; 
};

template <typename Elem_T, typename Comp_T, typename _SFINAE>
typename AVLTree<Elem_T, Comp_T, _SFINAE>::Node AVLTree<Elem_T, Comp_T, _SFINAE>::_sentinel{0, nullptr, nullptr, nullptr, 0}; 

template <typename Elem_T, typename Comp_T,
          typename>
class ConstAVLBiIter {
    friend class AVLTree<Elem_T, Comp_T>;
    typedef typename AVLTree<Elem_T, Comp_T>::Node Node;
    static constexpr Node* _NIL = AVLTree<Elem_T, Comp_T>::_NIL;
public:
    const Elem_T& operator*() const {
        if (_node == _NIL)
            throw std::runtime_error{"Dereferencing nullptr."};
        return _node->data;
    }

    const Elem_T* operator->() const {
        if (_node == _NIL)
            throw std::runtime_error{"Dereferencing nullptr."};
        return &(_node->data);
    }

    ConstAVLBiIter operator++() {
        _node = _owner.successor(*this)._node;
        return *this;
    }

    ConstAVLBiIter operator--() {
        _node = _owner.predecessor(*this)._node;
        return *this;
    }

    bool operator==(const ConstAVLBiIter& other) const {
        return _node == other._node;
    }
private:
    ConstAVLBiIter(const Node* node, const AVLTree<Elem_T, Comp_T>& owner): _node{node}, _owner{owner} {}
    const Node* _node;
    const AVLTree<Elem_T, Comp_T>& _owner;
};

template <typename Elem_T, typename Comp_T>
struct std::iterator_traits<ConstAVLBiIter<Elem_T, Comp_T>> {
    typedef const std::remove_cv_t<Elem_T> value_type;                //cppreference does not specify what this does so...
    typedef const Elem_T* pointer;                                    //cppreference does not specify what this does so...
    typedef const Elem_T& reference;                                  //cppreference does not specify what this does so...
    typedef std::bidirectional_iterator_tag iterator_category;        //I know what this does!!!
};

#endif