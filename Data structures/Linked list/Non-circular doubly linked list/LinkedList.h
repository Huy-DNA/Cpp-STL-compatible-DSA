#ifndef __NONCIRCULAR_DOUBLY_LINKED_LIST__
#define __NONCIRCULAR_DOUBLY_LINKED_LIST__

#include <type_traits>
#include <exception>
#include <iterator>

/*Iterator class representing pointers to list elements.*/

template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class NonConstBiIter;

/*Elem_T must be of TriviallyCopyableType.
  LinkedList::end() won't work as expected, that is, it doesn't point to off-by-one-from-the-end element. Therefore, --LinkedList::end() != <last-element>. In fact, it causes Segmentation fault. */
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
        while (_head != nullptr) {
            Node* cur = _head->next;
            delete _head;
            _head = cur;
        }
    }

    /*Returns a pointer to the first element whose value equals e.*/
    NonConstBiIter<Elem_T> search(const Elem_T& e) {
        Node* cur = _head;
        while (cur != nullptr && cur->data != e)
            cur = cur->next;
        return {cur};
    }
    
    /*Pushes an element at the end of the list.*/
    void push_back(const Elem_T& e) {
        ++_size;
        if (_head == nullptr)
            _head = _tail = new Node {e, nullptr, nullptr};
        else {
            _tail->next = new Node {e, nullptr, _tail};
            _tail = _tail->next;
        }
    }

    /*Pushes an element at the start of the list.*/
    void push_front(const Elem_T& e) {
        ++_size;
        if (_head == nullptr)
            _head = _tail = new Node {e, nullptr, nullptr};
        else {
            Node* tmp = new Node {e, _head, nullptr};
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
        if (_head == nullptr) _tail = nullptr;
        else _head->prev = nullptr;

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
        if (_tail == nullptr) _head = nullptr;
        else _tail->next = nullptr;

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
        return {nullptr};
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
    Node* _head = nullptr;
    Node* _tail = nullptr;
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
    typedef std::remove_cv_t<Elem_T> value_type;
    typedef Elem_T* pointer;
    typedef Elem_T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};
#endif