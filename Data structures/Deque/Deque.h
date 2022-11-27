#ifndef __DEQUEUE_HELL__
#define __DEQUEUE_HELL__

#include <type_traits>
#include <stdexcept>

template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class Deque {
    typedef std::size_t size_t;
public:
    Deque() = default;
    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;
    ~Deque() {
        delete[] _buffer;
    }

    void push_back(const Elem_T& e) {
        if (_full()) _push_reallocate_on_full();
        _buffer[_get_next_to_tail()] = e;
        ++_size;
    }

    void push_front(const Elem_T& e) {
        if (_full()) _push_reallocate_on_full();
        _buffer[_get_before_head()] = e;
        _head = _dec_wrap(_head, 1);
        ++_size;
    }

    Elem_T pop_back() {
        if (empty()) throw std::runtime_error{"Deque::pop_back() called on empty dequeue."};

        const Elem_T res = _buffer[_get_tail()];
        --_size;

        if (_capacity > 1 && _size <= _capacity / 4)
            _pop_reallocate_on_quarter();
        
        return res;
    }


    Elem_T pop_front() {
        if (empty()) throw std::runtime_error{"Deque::pop_front() called on empty dequeue."};
        
        const Elem_T res = _buffer[_head];
        _head = _inc_wrap(_head, 1);
        --_size;

        if (_capacity > 1 && _size <= _capacity / 4)
            _pop_reallocate_on_quarter();

        return res;
    }
    
    bool empty() const {
        return _size == 0;
    }

    Elem_T& front() {
        if (empty()) throw std::runtime_error{"Deque::front() called on empty dequeue."};
        return _buffer[_head];
    }

    Elem_T& back() {
        if (empty()) throw std::runtime_error{"Deque::back() called on empty dequeue."};
        return _buffer[_get_tail()];
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }
private:
    void _push_reallocate_on_full() {
        Elem_T* sec_buffer = new Elem_T[_capacity * 2];
        _copy_to_sec_buffer(sec_buffer);
        delete[] _buffer;
        _buffer = sec_buffer;
        _head = 0;
        _capacity *= 2;
    }

    void _pop_reallocate_on_quarter() {
        Elem_T* sec_buffer = new Elem_T[_capacity / 2];
        _copy_to_sec_buffer(sec_buffer);
        delete[] _buffer;
        _buffer = sec_buffer;
        _head = 0;
        _capacity /= 2;
    }

    void _copy_to_sec_buffer(Elem_T* sec_buffer) const {
        for (size_t i = 0; i < _size; ++i) {
            sec_buffer[i] = _buffer[_inc_wrap(_head, i)];
        }
    }

    bool _full() const {
        return _size == _capacity;
    }

    inline size_t _inc_wrap(size_t n, size_t k) const {
        return (n + k) % _capacity;
    }

    inline size_t _dec_wrap(size_t n, size_t k) const {
        return (n - k + _capacity) % _capacity;
    }

    inline size_t _get_before_head() const {
        return _dec_wrap(_head, 1);
    }

    inline size_t _get_tail() const {     //careful when _size == 0
        return _inc_wrap(_head, _size - 1);
    }

    inline size_t _get_next_to_tail() const {
        return _inc_wrap(_head, _size);
    }

    size_t _head = 0;
    size_t _size = 0;
    size_t _capacity = 1;
    Elem_T* _buffer = new Elem_T[_capacity];
};
#endif