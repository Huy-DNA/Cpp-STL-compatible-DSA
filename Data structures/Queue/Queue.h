#ifndef __QUEUE_HELL__
#define __QUEUE_HELL__

#include <type_traits>
#include <exception>

template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class Queue {
    typedef std::size_t size_t;
public:
    Queue() = default;
    Queue(const Queue&) = delete;
    ~Queue() {
        delete[] _buffer;
    }

    void enqueue(const Elem_T& e) {
        if (_full()) {
            Elem_T* sec_buffer = new Elem_T[_capacity * 2];
            _copy_to_sec_buffer(sec_buffer);
            delete[] _buffer;

            _buffer = sec_buffer;
            _head = 0;
            _capacity *= 2;
        }
        _buffer[_get_next_to_tail()] = e;
        ++_size;
    }

    Elem_T dequeue() {
        if (empty()) throw std::runtime_error{"Queue::dequeue() called on empty queue."};
        
        Elem_T res = _buffer[_head];
        _head = _inc_wrap(_head, 1);

        if (_capacity >= 1 && _size - 1 <= _capacity / 4) {
            Elem_T* sec_buffer = new Elem_T[_capacity / 2];
            _copy_to_sec_buffer(sec_buffer);
            delete[] _buffer;

            _buffer = sec_buffer;
            _head = 0;
            _capacity /= 2;
        }
        --_size;

        return res;
    }

    bool empty() const {
        return _size == 0;
    }

    Elem_T& head() {
        if (empty()) throw std::runtime_error{"Queue::head() called on empty queue."};
        return _buffer[_head];
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }
private:
    void _copy_to_sec_buffer(Elem_T* sec_buffer) const {
        const size_t _tail = _get_tail();
        for (size_t i = _head, sec_i = 0; ; ++sec_i, i = _inc_wrap(i, 1)) {
            sec_buffer[sec_i] = _buffer[i];
            if (i == _tail) return;
        }
    }

    bool _full() const {
        return _size == _capacity;
    }

    inline size_t _inc_wrap(size_t n, size_t k) const {
        return (n + k) % _capacity;
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