#ifndef __INSERTION_SORT_HELL__
#define __INSERTION_SORT_HELL__

#include <iterator>
#include <type_traits>
#include <functional>

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto insertion_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T &>{}) 
                                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category, 
                                                                typename std::random_access_iterator_tag>::value, 
                                                                void> {
    for (Iter i_ptr = begin + 1; i_ptr < end; ++i_ptr) {
        auto i_ele = *i_ptr;
        Iter j_ptr = i_ptr - 1;
        for (; j_ptr >= begin; --j_ptr)
            if (less(i_ele, *j_ptr))
                *(j_ptr + 1) = *j_ptr;
            else break;
        *(j_ptr + 1) = i_ele;
    }   
}

#endif