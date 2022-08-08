#ifndef __DYNAMIC_TABLE_HELL__
#define __DYNAMIC_TABLE_HELL__

#include <exception>

/*This DynamicTable grows by double when its size exceeds its capacity
  and shrinks by half when its size is no greater than a quarter of its capacity.*/
template <typename Elem_T>
class DynamicTable {
    typedef std::size_t size_t;
public:
    DynamicTable() = default;
    DynamicTable(const DynamicTable&) = delete;
    DynamicTable& operator=(const DynamicTable&) = delete;
    
    void push_back(const Elem_T& e) {
        if (_size == _capacity) {
            Elem_T* sec_buffer = new Elem_T[_capacity * 2];
            copy(buffer, _size, sec_buffer);
            delete[] buffer;
            buffer = sec_buffer;
            _capacity *= 2;
        }
        buffer[_size++] = e;
    }
    
    Elem_T pop_back() {
        if (empty()) throw std::runtime_error{"DynamicTable::pop_back called on empty table."};
        
        const Elem_T popped_value = back();
        if (_capacity > 1 && _size - 1 <= _capacity / 4) {
            Elem_T* sec_buffer = new Elem_T[_capacity / 2];
            copy(buffer, _size - 1, sec_buffer);
            delete[] buffer;
            buffer = sec_buffer;
            _capacity /= 2;
        }
        --_size;

        return popped_value;
    }

    inline bool empty() const {
        return _size == 0;
    }

    inline Elem_T& back() {
        if (empty()) throw std::runtime_error{"DynamicTable::back called on empty table."};
        return buffer[_size- 1];
    }

    inline Elem_T& front() {
        if (empty()) throw std::runtime_error{"DynamicTable::front called on empty table."};
        return buffer[0];
    }

    inline size_t size() const {
        return _size;
    }

    inline size_t capacity() const {
        return _capacity;
    }
private:
    inline static void copy(Elem_T* from_buffer, size_t from__capacity, Elem_T* to_buffer) {
        for (size_t i = 0; i < from__capacity; ++i)
            to_buffer[i] = from_buffer[i];
    }
    size_t _capacity = 1;
    size_t _size= 0;
    Elem_T* buffer = new Elem_T[_capacity];
};

#endif