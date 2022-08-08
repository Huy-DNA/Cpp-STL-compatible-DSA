#ifndef __STACK_HELL__
#define __STACK_HELL__

#include "../Dynamic table/DynamicTable.h"

template <typename Elem_T>
class Stack {
    typedef std::size_t size_t;
public:
    
private:
    size_t top = 0;
    DynamicTable<Elem_T> dy_buffer;
};

#endif