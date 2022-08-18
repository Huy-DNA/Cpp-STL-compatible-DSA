#ifndef __MEMORY_POOL_HELL__
#define __MEMORY_POOL_HELL__

#include <cstddef>
#include <type_traits>
#include <stdexcept>

/*Elem_T must be of TriviallyCopyableType.*/
template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
class MemoryPool {
    typedef std::size_t size_t;
    static constexpr size_t BUFFER_SIZE = 1000;     //Maximum number of elements that the memory pool can allocate
public:
    MemoryPool() {      //initializes memory pool
        _free = 0;
        for (size_t i = 0; i < BUFFER_SIZE - 1; ++i)
            _next[i] = i + 1;
        _next[BUFFER_SIZE - 1] = -1;
    }
    
    Elem_T* allocate(const Elem_T& e = {}) {
        if (empty()) throw std::runtime_error{"MemoryPool::allocate() called on empty pool."};
        --_size;
        Elem_T* ptr = _val + _free;
        *ptr = e;
        _free = _next[_free];
        return ptr;
    }

    void deallocate(Elem_T* e_ptr) {
        const size_t id = e_ptr - _val;
        ++_size;
        _next[id] = _free;
        _free = id;
    }

    bool empty() const {
        return _free == -1;
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return BUFFER_SIZE;
    }
private:
    size_t _free;
    size_t _next[BUFFER_SIZE];
    Elem_T _val[BUFFER_SIZE];
    size_t _size = BUFFER_SIZE;
};
#endif