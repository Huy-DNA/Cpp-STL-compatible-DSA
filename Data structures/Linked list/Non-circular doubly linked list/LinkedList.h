#ifndef __NONCIRCULAR_DOUBLY_LINKED_LIST_HELL__
#define __NONCIRCULAR_DOUBLY_LINKED_LIST_HELL__

#include <type_traits>
#include <stdexcept>
#include <iterator>

/*Iterator class representing pointers to list elements.*/

template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class NonConstBiIter;

/*Elem_T must be of TriviallyCopyableType.*/
template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class LinkedList {
    friend class NonConstBiIter<Elem_T>;
    typedef std::size_t size_t;
    struct Node {
        Elem_T data;
        Node* next;
        Node* prev;
    };

   public:
    ~LinkedList() {
        while (_head != _NIL) {
            Node* cur = _head->next;
            delete _head;
            _head = cur;
        }
    }

    /*Returns a pointer to the first element whose value equals e.*/
    NonConstBiIter<Elem_T> search(const Elem_T& e) {
        Node* cur = _head;
        while (cur != _NIL && cur->data != e)
            cur = cur->next;
        return {cur};
    }
    
    /*Pushes an element at the end of the list.*/
    void push_back(const Elem_T& e) {
        ++_size;
        if (_head == _NIL)
            _head = _tail = new Node {e, _NIL, _NIL};
        else {
            _tail->next = new Node {e, _NIL, _tail};
            _tail = _tail->next;
        }
    }

    /*Pushes an element at the start of the list.*/
    void push_front(const Elem_T& e) {
        ++_size;
        if (_head == _NIL)
            _head = _tail = new Node {e, _NIL, _NIL};
        else {
            Node* tmp = new Node {e, _head, _NIL};
            _head->prev = tmp;
            _head = tmp;
        }
    }

    /*Removes and returns the element at the start of the list.*/
    Elem_T pop_front() {
        if (_size == 0) throw std::runtime_error{"LinkedList::pop_front() called on empty list."};
        --_size;

        Elem_T res = _head->data;
        Node* tmp = _head;

        _head = _head->next;
        if (_head == _NIL) _tail = _NIL;
        else _head->prev = _NIL;

        delete tmp;
        return res;
    }

    /*Removes and returns the element at the end of the list.*/
    Elem_T pop_back() {
        if (_size == 0) throw std::runtime_error{"LinkedList::pop_back() called on empty list."};
        --_size;
        
        Elem_T res = _tail->data;
        Node* tmp = _tail;

        _tail = _tail->prev;
        if (_tail == _NIL) _head = _NIL;
        else _tail->next = _NIL;

        delete tmp;
        return res;
    }

    /*Returns a pointer to the first element.*/
    NonConstBiIter<Elem_T> begin() {
        return {_head};
    }

    /*Returns nullptr.
    Not to the element past one from the last element.*/
    NonConstBiIter<Elem_T> end() {
        return {_NIL};
    }

    /*Returns a reference to the last element.*/
    Elem_T& back() {
        if (_size == 0) throw std::runtime_error{"LinkedList::back() called on empty list."};
        return _tail->data;
    }

    /*Returns a reference to the first element.*/
    Elem_T& front() {
        if (_size == 0) throw std::runtime_error{"LinkedList::front() called on empty list."};
        return _head->data;
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }
private:
    //Technically, this is a circular linked list -- sentinel is the element that closes the circle.
    Node _sentinel = {{}, &_sentinel, &_sentinel};     //sentinel->next == _head()
                                                    //sentinel->prev == _prev()
    
    Node*& _tail = _sentinel.prev;
    Node*& _head = _sentinel.next;

    Node* _NIL = &_sentinel;                            
    size_t _size = 0;
};

template <typename Elem_T,
          typename>
class NonConstBiIter {
public:
    NonConstBiIter(typename LinkedList<Elem_T>::Node* n): node{n} {}
    bool operator==(NonConstBiIter other) const {
        return other.node == node;
    }
    bool operator!=(NonConstBiIter other) const {
        return other.node != node;
    }
    NonConstBiIter& operator++() {
        node = node->next;
        return *this;
    }
    NonConstBiIter& operator--() {
        node = node->prev;
        return *this;
    }
    Elem_T& operator*() {
        return node->data;
    }
    Elem_T* operator->() {
        return &(node->data);
    }
private:
    /*Beware: node can be nullptr*/
    typename LinkedList<Elem_T>::Node* node;
};

/*Defines LinkedList::NonConstBiIter as bidirectional iterator.*/
template <typename Elem_T>
struct std::iterator_traits<NonConstBiIter<Elem_T>> {
    typedef std::remove_cv_t<Elem_T> value_type;                //cppreference does not specify what this does so...
    typedef Elem_T* pointer;                                    //cppreference does not specify what this does so...
    typedef Elem_T& reference;                                  //cppreference does not specify what this does so...
    typedef std::bidirectional_iterator_tag iterator_category;  //I know what this does!!!
};
#endif