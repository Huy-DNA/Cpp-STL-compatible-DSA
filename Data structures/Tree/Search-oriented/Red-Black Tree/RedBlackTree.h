#ifndef __RED_BLACK_TREE_HELL__
#define __RED_BLACK_TREE_HELL__

#include <iostream>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <string>
#include <windows.h>            // For colored output

template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class ConstRBBiIter;

/*Requires Elem_T to be a trivially copyable type.*/
template <typename Elem_T, typename Comp_T = std::less<const Elem_T&>,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class RedBlackTree {
    friend class ConstRBBiIter<Elem_T, Comp_T>;
    typedef std::size_t size_t;
    typedef ConstRBBiIter<Elem_T, Comp_T> ConstRBBiIter;

    enum Color {
        RED, BLACK, RESET
    };

    struct Node {
        Elem_T data;
        Node* left;
        Node* right;
        Node* p;
        Color color;
    };
public:
    ~RedBlackTree() {
        _deallocate_node(_root);
    }

    ConstRBBiIter search(const Elem_T& e) {
        Node* cur = _root;

        while (cur != _NIL && cur->data != e)
            if (_less(cur->data, e)) cur = cur->right;
            else cur = cur->left;

        return _create_ConstRBBiIter(cur);               
    }  

    void insert(const Elem_T& e) {
        if (_root == _NIL) {
            _root = new Node{e, _NIL, _NIL, _NIL, BLACK};
            return;
        }

        Node* prev;
        Node* cur = _root;

        while (cur != _NIL) {
            prev = cur;
            if (_less(cur->data, e))
                cur = cur->right;
            else cur = cur->left;
        }
        
        Node* new_node = new Node{e, _NIL, _NIL, prev, RED};
        if (_less(prev->data, e))
            prev->right = new_node;
        else prev->left = new_node;

        _insert_fixup(new_node);
    }

    Elem_T remove(const Elem_T& e) {
        return remove(search(e));
    }

    Elem_T remove(ConstRBBiIter iter) {
        Node* node = _extract_Node(iter);

        if (node == _NIL)
            throw std::runtime_error{"Redblacktree::remove() called on null pointer."};
        
        Node* to_be_fixed;                  // Node that needs fixing after deletion 
        Color original_color = node->color; // Color of to be moved-or-removed node

        if (node->left == _NIL) {
            to_be_fixed = node->right;
            _transplant(node, node->right);
        } else if (node->right == _NIL) {
            to_be_fixed = node->left;
            _transplant(node, node->left);
        } else {
            Node* m = _extract_Node(minimum_at_subtree(_create_ConstRBBiIter(node->right)));
            original_color = m->color;
            to_be_fixed = m->right;

            if (node->right != m) {
                _transplant(m, m->right);
                m->right = node->right;
                m->right->p = m;
            }
            _transplant(node, m);
            m->left = node->left;
            m->left->p = m;
            m->color = node->color;
        }
        if (original_color == BLACK)
            _remove_fixup(to_be_fixed);
        
        Elem_T res = node->data;
        delete node;
        return res;
    }

    ConstRBBiIter minimum_at_subtree(ConstRBBiIter iter) {
        const Node* cur = _extract_Node(iter);
        if (cur == _NIL) return _create_ConstRBBiIter(_NIL);

        while (cur->left != _NIL)
            cur = cur->left;
        return _create_ConstRBBiIter(cur);
    }

    ConstRBBiIter maximum_at_subtree(ConstRBBiIter iter) {
        const Node* cur = _extract_Node(iter);
        if (cur == _NIL) return _create_ConstRBBiIter(_NIL);

        while (cur->right != _NIL)
            cur = cur->right;
        return _create_ConstRBBiIter(cur);
    }

    ConstRBBiIter maximum() {
        return maximum_at_subtree(_root);
    }

    ConstRBBiIter minimum() {
        return minimum_at_subtree(_root);
    }
    
    ConstRBBiIter successor(ConstRBBiIter iter) {
        const Node* node = _extract_Node(iter);
        if (node == _NIL)
            return _create_ConstRBBiIter(_NIL);
        if (node->right != _NIL)
            return minimum_at_subtree(node->right);
        while (node != _NIL && node->p->left != node)
            node = node->p;
        if (node == _NIL)
            return _create_ConstRBBiIter(_NIL);
        return _create_ConstRBBiIter(node->p);
    }

    ConstRBBiIter predecessor(ConstRBBiIter iter) {
        const Node* node = _extract_Node(iter);
        if (node == _NIL)
            return _create_ConstRBBiIter(_NIL);
        if (node->left != _NIL)
            return maximum_at_subtree(node->right);
        while (node != _NIL && node->p->right != node)
            node = node->p;
        if (node == _NIL)
            return _create_ConstRBBiIter(_NIL);
        return _create_ConstRBBiIter(node->p);
    }

    void print() const {
        _print_recur("", _root, false);
    }
private:
    void _print_recur(const std::string& prefix, const Node* node, bool isLeft) const {
        /*From: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c*/
        if (node != _NIL) {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            _set_text_color(node->color);
            std::cout << node->data << '\n';
            _set_text_color(RESET);

            // enter the next tree level - left and right branch
            _print_recur(prefix + (isLeft ? "│   " : "    "), node->left, true);
            _print_recur(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

    static void _set_text_color(Color color) {
        static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        int code;
        switch (color) {
            case BLACK: code = 0; break;
            case RED: code = 4; break;
            default: code = 7; break;
        }
        SetConsoleTextAttribute(h, code);
    }

    void _deallocate_node(Node* n) {
        if (n == _NIL) return;
        _deallocate_node(n->left);
        _deallocate_node(n->right);
        delete n;
    }

    void _insert_fixup(Node* n) {
        while (n->p->color == RED) {
            Node* m = n->p;         // n's parent
                                    // m is RED
                                    // m->p is BLACK
            if (m->p->left == m) {
                Node* u = m->p->right;
                if (u->color == RED) {
                    m->color = u->color = BLACK;
                    m->p->color = RED;
                    n = m->p;
                } else {
                    if (m->right == n) {
                        _left_rotate(m);
                        n = m;
                        m = n->p;
                    }
                    m->color = BLACK;
                    m->p->color = RED;
                    _right_rotate(m->p);
                    return;
                }
            } else {
                Node* u = m->p->left;
                if (u->color == RED) {
                    m->color = u->color = BLACK;
                    m->p->color = RED;
                    n = m->p;
                } else {
                    if (m->left == n) {
                        _right_rotate(m);
                        n = m;
                        m = n->p;
                    }
                    m->color = BLACK;
                    m->p->color = RED;
                    _left_rotate(m->p);
                    return;
                }
            }
        }
        _root->color = BLACK;
    }

    void _remove_fixup(Node* n) {
        while (n->color == BLACK && n != _root) {
            Node* m = n->p;         // n's parent
            if (m->left == n) {
                Node* u = m->right;
                if (u->color == RED) {
                    m->color = RED;
                    u->color = BLACK;
                    _left_rotate(m);
                    u = m->right;
                }
                if (u->left->color == BLACK && u->right->color == BLACK) {
                    u->color = RED;
                    n = m;
                } else {
                    if (u->right->color == BLACK) {
                        u->left->color = BLACK;
                        u->color = RED;
                        _right_rotate(u);
                        u = u->p;
                    }
                    u->right->color = BLACK;
                    u->color = m->color;
                    m->color = BLACK;
                    _left_rotate(m);
                    n = _root;
                }
            } else {
                Node* u = m->left;
                if (u->color == RED) {
                    m->color = RED;
                    u->color = BLACK;
                    _right_rotate(m);
                    u = m->left;
                }
                if (u->left->color == BLACK && u->right->color == BLACK) {
                    u->color = RED;
                    n = m;
                } else {
                    if (u->left->color == BLACK) {
                        u->right->color = BLACK;
                        u->color = RED;
                        _left_rotate(u);
                        u = u->p;
                    }
                    u->left->color = BLACK;
                    u->color = m->color;
                    m->color = BLACK;
                    _right_rotate(m);
                    n = _root;
                }
            }
        }
        n->color = BLACK;   
    }

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
        v->left = u;
        u->right->p = u;
        u->p = v;
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
        v->right = u;
        u->left->p = u;
        u->p = v;
    }

    ConstRBBiIter _create_ConstRBBiIter(const Node* node) {
        return {node, *this};
    }

    Node* _extract_Node(ConstRBBiIter iter) {
        return const_cast<Node*>(iter._node);       //Bad: const_cast but...
    }
    Node* _root = _NIL;
    const Comp_T _less{};
    static Node _sentinel;
    static constexpr Node* _NIL = &_sentinel;
};

template <typename Elem_T, typename Comp_T, typename _SFINAE>
typename RedBlackTree<Elem_T, Comp_T, _SFINAE>::Node RedBlackTree<Elem_T, Comp_T, _SFINAE>::_sentinel = {{}, _NIL, _NIL, _NIL, BLACK};

template <typename Elem_T, typename Comp_T,
          typename>
class ConstRBBiIter {
    friend class RedBlackTree<Elem_T, Comp_T>;
    typedef typename RedBlackTree<Elem_T, Comp_T>::Node Node;
    static constexpr Node* _NIL = RedBlackTree<Elem_T, Comp_T>::_NIL;
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

    ConstRBBiIter operator++() {
        _node = _owner.successor(*this)._node;
        return *this;
    }

    ConstRBBiIter operator--() {
        _node = _owner.predecessor(*this)._node;
        return *this;
    }

    bool operator==(const ConstRBBiIter& other) const {
        return _node == other._node;
    }
private:
    ConstRBBiIter(const Node* node, const RedBlackTree<Elem_T, Comp_T>& owner): _node{node}, _owner{owner} {}
    const Node* _node;
    const RedBlackTree<Elem_T, Comp_T>& _owner;
};

template <typename Elem_T, typename Comp_T>
struct std::iterator_traits<ConstRBBiIter<Elem_T, Comp_T>> {
    typedef const std::remove_cv_t<Elem_T> value_type;                //cppreference does not specify what this does so...
    typedef const Elem_T* pointer;                                    //cppreference does not specify what this does so...
    typedef const Elem_T& reference;                                  //cppreference does not specify what this does so...
    typedef std::bidirectional_iterator_tag iterator_category;        //I know what this does!!!
};

#endif