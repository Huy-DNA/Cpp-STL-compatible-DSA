#ifndef __SHELL_SORT_HELL__
#define __SHELL_SORT_HELL__

#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto segment_sort(Iter begin, Iter end, const size_t increment, const size_t index, const Comp& less = std::less<const Elem_T&>{}) 
                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                 typename std::random_access_iterator_tag>::value, 
                                    void> {
    for (Iter i_ptr = begin + index + increment; i_ptr < end; i_ptr += increment) {
        Elem_T i_ele = *i_ptr;
        Iter j_ptr = i_ptr - increment;
        for (; j_ptr >= begin; j_ptr -= increment)
            if (less(i_ele, *j_ptr))
                *(j_ptr + increment) = *j_ptr;
            else break;
        *(j_ptr + increment) = i_ele;
    }
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto shell_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                 typename std::random_access_iterator_tag>::value, 
                                    void> {
    static const int increments[] = {364, 121, 40, 13, 4, 1};
    const size_t len = end - begin;
    
    for (int increment: increments) {
        if (increment >= len) continue;
        for (int index = 0; index < increment; ++index)
            segment_sort(begin, end, increment, index, less);
    }
}
#endif