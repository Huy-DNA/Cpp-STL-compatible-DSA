#ifndef __SELECTION_SORT_HELL__
#define __SELECTION_SORT_HELL__

#include <functional>
#include <type_traits>
#include <iterator>
#include <utility>

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto selection_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{}) 
                    -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                     typename std::random_access_iterator_tag>::value,
                                        void> {
    using std::swap;

    for (Iter i_ptr = begin; i_ptr < end - 1; ++i_ptr) {
        Iter min_ptr = i_ptr;
        for (Iter j_ptr = i_ptr + 1; j_ptr != end; ++j_ptr)
            if (*j_ptr < *min_ptr)
                min_ptr = j_ptr;
        swap(*i_ptr, *min_ptr);
    }
}

#endif