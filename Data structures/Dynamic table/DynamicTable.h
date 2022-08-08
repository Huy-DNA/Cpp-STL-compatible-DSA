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
    ~DynamicTable() {
        delete[] buffer;
    }
    DynamicTable(const DynamicTable&) = delete;
    DynamicTable& operator=(const DynamicTable&) = delete;
    
    /*Copies and inserts the passed element into the table.*/
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
    
    /*Removes the last element from the table.*/
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

    /*Returns whether the table is empty.*/
    inline bool empty() const {
        return _size == 0;
    }

    /*Returns the last element.*/
    inline Elem_T& back() {
        if (empty()) throw std::runtime_error{"DynamicTable::back called on empty table."};
        return buffer[_size - 1];
    }

    /*Returns the first element.*/
    inline Elem_T& front() {
        if (empty()) throw std::runtime_error{"DynamicTable::front called on empty table."};
        return buffer[0];
    }

    /*Returns the current number of elements in the table.*/
    inline size_t size() const {
        return _size;
    }

    /*Returns the maximum number of elements the table can hold before it needs to reallocate its internal buffer.*/
    inline size_t capacity() const {
        return _capacity;
    }
private:
    inline static void copy(Elem_T* from_buffer, size_t from_capacity, Elem_T* to_buffer) {
        for (size_t i = 0; i < from_capacity; ++i)
            to_buffer[i] = from_buffer[i];
    }
    size_t _capacity = 1;                       //The maximum number of elements the buffer can hold before having to be reallocated.
    size_t _size = 0;                           //The current number of elements in the buffer.
    Elem_T* buffer = new Elem_T[_capacity];
};

#endif