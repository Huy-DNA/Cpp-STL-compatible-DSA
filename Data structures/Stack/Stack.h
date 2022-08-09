#ifndef __STACK_HELL__
#define __STACK_HELL__

#include "../Dynamic table/DynamicTable.h"

template <typename Elem_T>
class Stack {
    typedef std::size_t size_t;
public:
    /*Pushes the passed element to the stack.*/
    void push(const Elem_T& e) {
        _dy_buffer.push_back(e);
    }

    /*Removes the last element and returns it.*/
    Elem_T pop() {
        return _dy_buffer.pop_back();
    }

    /*Checks if the stack is empty.*/
    bool empty() const {
        return _dy_buffer.empty();
    }

    /*Returns the element at the top.*/
    Elem_T& top() {
        return _dy_buffer.back();
    }

    /*Returns the current number of elements on the stack.*/
    size_t size() {
        return _dy_buffer.size();
    }

private:
    DynamicTable<Elem_T> _dy_buffer;
};

#endif