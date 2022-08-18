#ifndef __DYNAMIC_TABLE_HELL__
#define __DYNAMIC_TABLE_HELL__

#include <stdexcept>
#include <type_traits>

/*This DynamicTable grows by double when its size exceeds its capacity
  and shrinks by half when its size is no greater than a quarter of its capacity.
  Uses are restricted to elements of TriviallyCopyableType.*/
template <typename Elem_T, 
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value, void>>
class DynamicTable {
    typedef std::size_t size_t;
public:
    DynamicTable() = default;
    ~DynamicTable() {
        delete[] _buffer;
    }
    DynamicTable(const DynamicTable&) = delete;
    DynamicTable& operator=(const DynamicTable&) = delete;
    
    /*Copies and inserts the passed element into the table.*/
    void push_back(const Elem_T& e) {
        if (_size == _capacity) {
            Elem_T* _sec_buffer = new Elem_T[_capacity * 2];
            _copy(_buffer, _size, _sec_buffer);
            delete[] _buffer;
            _buffer = _sec_buffer;
            _capacity *= 2;
        }
        _buffer[_size++] = e;
    }
    
    /*Removes the last element from the table and returns it.*/
    Elem_T pop_back() {
        if (empty()) throw std::runtime_error{"DynamicTable::pop_back called on empty table."};
        
        const Elem_T popped_value = back();
        if (_capacity > 1 && _size - 1 <= _capacity / 4) {
            Elem_T* _sec_buffer = new Elem_T[_capacity / 2];
            _copy(_buffer, _size - 1, _sec_buffer);
            delete[] _buffer;
            _buffer = _sec_buffer;
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
        return _buffer[_size - 1];
    }

    /*Returns the first element.*/
    inline Elem_T& front() {
        if (empty()) throw std::runtime_error{"DynamicTable::front called on empty table."};
        return _buffer[0];
    }

    /*Returns the current number of elements in the table.*/
    inline const size_t& size() const {
        return _size;
    }

    /*Returns the maximum number of elements the table can hold before it needs to reallocate its internal buffer.*/
    inline const size_t& capacity() const {
        return _capacity;
    }

    /*Returns the id_th element of the table. No bound checking is performed.*/
    Elem_T& operator[](size_t id) {
        return _buffer[id];
    }

    const Elem_T& operator[](size_t id) const {
        return _buffer[id];
    }

    /*Returns the id_th element of the table with bound checking.*/
    Elem_T& at(size_t id) {
        if (id < 0 or id >= _size) throw std::runtime_error{"Dynamic::at called with an out-of-bound index."};
        return _buffer[id];
    }
    
    const Elem_T& at(size_t id) const {
        if (id < 0 or id >= _size) throw std::runtime_error{"Dynamic::at called with an out-of-bound index."};
        return _buffer[id];
    }

    Elem_T* begin() {
        return _buffer + 0;
    }

    Elem_T* end() {
        return _buffer + _size;
    }
private:
    /*Copies content of `from_buffer` to `to_buffer`. Should only be called on arrays of TriviallyCopyableType.*/
    static void _copy(Elem_T* from_buffer, size_t from_size, Elem_T* to_buffer) {
        memcpy(to_buffer, from_buffer, sizeof(Elem_T) * from_size);
    }   

    size_t _capacity = 1;                       //The maximum number of elements the buffer can hold before having to be reallocated.
    size_t _size = 0;                           //The current number of elements in the buffer.
    Elem_T* _buffer = new Elem_T[_capacity];
};

#endif