#ifndef __STACK_HELL__
#define __STACK_HELL__

#include "../Dynamic table/DynamicTable.h"

template <typename Elem_T>
class Stack {
    typedef std::size_t size_t;
public:
    //constructor

    void push(Elem_T e) {
        dy_buffer.push_back(e);
    }
    Elem_T pop() {
        return dy_buffer.pop_back();
    }

    bool empty() const {
        return dy_buffer.empty();
    }

    Elem_T& top() {
        return dy_buffer.back();
    }
private:
    DynamicTable<Elem_T> dy_buffer;
    const size_t& top = dy_buffer.size();
};

#endif