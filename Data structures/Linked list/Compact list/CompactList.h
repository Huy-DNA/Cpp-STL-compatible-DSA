#ifndef __COMPACT_LIST_HELL__
#define __COMPACT_LIST_HELL__

#include <type_traits>
#include <stdexcept>
#include <iterator>

/*Class representing bidirectional non-const iterator to CompactList's element.*/
template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class CompactListNonConstBiIter;


/*Pointer-less Linked List implemented using a dynamic array -- array indices act as pointers. 
  It's also Compact -- meaning all elements always occupy the leftmost slots of the array.
  Elem_T must be of TriviallyCopyableType.*/
template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class CompactList {
    friend class CompactListNonConstBiIter<Elem_T>;
    typedef std::size_t size_t;
    struct Node {
        Elem_T data;
        long long next;        //Note the difference
        long long prev;        //Note the difference
    };
    constexpr static long long _NIL = -1;       //index representing the sentinel
    constexpr static long long _INVALID = -2;   //index representing invalid elements (non-existent)
public:
    ~CompactList() {
        delete[] _buffer;
    }

    /*Returns the first element of the list that equals `e`.*/
    CompactListNonConstBiIter<Elem_T> search(const Elem_T& e) {
        long long cur = _head;
        while (cur != _NIL && _buffer[cur].data != e)
            cur = _buffer[cur].next;
        if (cur == _NIL) cur = _INVALID;
        return {cur, _buffer, _sentinel};
    }

    /*Inserts `e` after `iter`.*/
    void insert_after(CompactListNonConstBiIter<Elem_T> iter, const Elem_T& e) {
        if (iter.id == -1) throw std::runtime_error{"CompactList::insert_after() called on invalid position."};
        _insert_after(iter.id, e);
    }

    /*Inserts `e` before `iter`*/
    void insert_before(CompactListNonConstBiIter<Elem_T> iter, const Elem_T& e) {
        if (iter.id == -1) throw std::runtime_error{"CompactList::insert_after() called on invalid position."};
        _insert_before(iter.id, e);
    }

    /*Inserts `e` at the end of the list.*/
    void push_back(const Elem_T& e) {
        _insert_after(_tail, e);
    }

    /*Inserts `e` at the start of the list.*/
    void push_front(const Elem_T& e) {
        _insert_before(_head, e);
    }

    /*Removes and returns the last element of the list.*/
    Elem_T pop_back() {
        if (empty()) throw std::runtime_error{"CompactList::pop_back() called on empty list."};
        return _remove(_tail);
    }

    /*Removes and returns the first element of the list.*/
    Elem_T pop_front() {
        if (empty()) throw std::runtime_error{"CompactList::pop_front() called on empty list."};
        return _remove(_head);
    }

    /*Removes the element pointed to by `iter` from the list.*/
    void remove(CompactListNonConstBiIter<Elem_T> iter) {
        if (iter.id == _NIL or iter.id == _INVALID) throw std::runtime_error{"CompactList::remove() called on invalid position."};
        _remove(iter.id);
    }

    /*Returns whether the list is empty.*/
    bool empty() const {
        return _size == 0;   
    }

    /*Returns the number of elements in the list.*/
    size_t size() const {
        return _size;
    }

    /*Returns the current capacity of the underlying buffer.*/
    size_t capacity() const {
        return _capacity;
    }

    /*Returns an iterator to the first element.*/
    CompactListNonConstBiIter<Elem_T> begin() {
        return {_head, _buffer, _sentinel};
    }

    /*Returns an iterator to the sentinel, which is past-one from the last element.*/
    CompactListNonConstBiIter<Elem_T> end() {
        return {_NIL, _buffer, _sentinel};
    }
private:
    /*Removes element at position `pos` in the underlying array.
      `pos` is guaranteed to be valid and not equal _NIL.*/
    Elem_T _remove(long long pos) {
        Elem_T res = _buffer[pos].data;

        --_size;
        _index_buffer_sentinel_aware(_buffer[pos].next).prev = _buffer[pos].prev;
        _index_buffer_sentinel_aware(_buffer[pos].prev).next = _buffer[pos].next;
        
        if (pos != _size) {
            _buffer[pos] = _buffer[_size];
            
            long long size_prev = _buffer[_size].prev;
            _index_buffer_sentinel_aware(size_prev).next = pos;
            
            long long size_next = _buffer[_size].next;
            _index_buffer_sentinel_aware(size_next).prev = pos;
        }
        if (_can_halve()) _halve_buffer();

        return res;
    }

    /*Inserts `e` that is `next` of the element at position `pos` in the underlying array.*/
    void _insert_after(long long pos, const Elem_T& e) {
        if (_full()) _double_buffer();
        Node& e_pos = _index_buffer_sentinel_aware(pos);
        _buffer[_size] = {e, e_pos.next, pos};
        _index_buffer_sentinel_aware(e_pos.next).prev = _size;
        e_pos.next = _size;
        ++_size;
    }

    /*Inserts `e` that is `prev` of the element at position `pos` in the underlying array. */
    void _insert_before(long long pos, const Elem_T& e) {
        if (_full()) _double_buffer();
        Node& e_pos = _index_buffer_sentinel_aware(pos);
        _buffer[_size] = {e, pos, e_pos.prev};
        _index_buffer_sentinel_aware(e_pos.prev).next = _size;
        e_pos.prev = _size;
        ++_size;
    }
    
    /*Works like _buffer[id], but if id == -1, returns a reference to the sentinel.*/
    Node& _index_buffer_sentinel_aware(long long id) {
        if (id == -1) return _sentinel;
        return _buffer[id];
    }

    void _double_buffer() {
        Node* sec_buffer = new Node[_capacity * 2];
        _copy(_buffer, _size, sec_buffer);
        delete[] _buffer;
        _buffer = sec_buffer;
        _capacity *= 2;
    }

    void _halve_buffer() {
        Node* sec_buffer = new Node[_capacity / 2];
        _copy(_buffer, _size, sec_buffer);
        delete[] _buffer;
        _buffer = sec_buffer;
        _capacity /= 2;
    }

    static void _copy(Node* from_buffer, size_t from_size, Node* to_buffer) {
        memcpy(to_buffer, from_buffer, from_size * sizeof(Node));
    }

    bool _full() const {
        return _size == _capacity;
    }

    bool _can_halve() const {
        return _capacity > 1 && _size <= _capacity / 4;
    }

    size_t _size = 0;
    size_t _capacity = 1;
    Node* _buffer = new Node[_capacity];

    Node _sentinel = {{}, -1, -1};      //_sentinel.next == _head, _sentinel.prev == _tail
    long long& _head = _sentinel.next;
    long long& _tail = _sentinel.prev;
};

template <typename Elem_T,
          typename>
class CompactListNonConstBiIter {
    friend class CompactList<Elem_T>;
    typedef typename CompactList<Elem_T>::Node Node;
    constexpr static long long _NIL = -1;
    constexpr static long long _INVALID = -2;
public:
    bool operator==(CompactListNonConstBiIter other) const {
        return (other.id == id) && (other._list_buffer == _list_buffer) && (&other._list_sentinel == &_list_sentinel); 
    }

    bool operator!=(CompactListNonConstBiIter other) const {
        return !(other == *this);
    }

    Elem_T& operator*() {
        switch (id) {
            case _INVALID: throw std::runtime_error{"Invalid iterator."};
            case _NIL: throw std::runtime_error{"Dereferencing sentinel."};
            default: return _list_buffer[id].data;
        }
    }

    Elem_T* operator->() {
        switch (id) {
            case _INVALID: throw std::runtime_error{"Invalid iterator."};
            case _NIL: throw std::runtime_error{"Dereferencing sentinel."};
            default: return &_list_buffer[id].data;
        }
    }

    CompactListNonConstBiIter& operator++() {
        switch (id) {
            case _INVALID: throw std::runtime_error{"Invalid iterator."};
            case _NIL: id = _list_sentinel.next; break;
            default: id = _list_buffer[id].next;
        }
        return *this;
    }

    CompactListNonConstBiIter& operator--() {
        switch (id) {
            case _INVALID: throw std::runtime_error{"Invalid iterator."};
            case _NIL: id = _list_sentinel.prev; break;
            default: id = _list_buffer[id].prev;
        }
        return *this;
    }
private:
    CompactListNonConstBiIter(long long i, Node* buffer, Node& sentinel): id{i}, _list_buffer{buffer}, _list_sentinel{sentinel} {}
    long long id;
    Node* _list_buffer;
    Node& _list_sentinel;
};

template <typename Elem_T>
struct std::iterator_traits<CompactListNonConstBiIter<Elem_T>> {
    typedef std::remove_cv_t<Elem_T> value_type;                //cppreference does not specify what this does so...
    typedef Elem_T* pointer;                                    //cppreference does not specify what this does so...
    typedef Elem_T& reference;                                  //cppreference does not specify what this does so...
    typedef std::bidirectional_iterator_tag iterator_category;  //I know what this does!!!
};
#endif