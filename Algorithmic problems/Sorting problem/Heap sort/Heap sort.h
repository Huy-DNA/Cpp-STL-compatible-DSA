#ifndef __HEAP_SORT_HELL__
#define __HEAP_SORT_HELL__

#include <type_traits>
#include <functional>
#include <utility>
#include <iterator>

#define left(x) (((x) << 1) | 1)
#define right(x) (((x) << 1) + 2)
#define parent(x) (((x) - 1) >> 1)
#define elem_at(begin, id) (*((begin) + (id)))

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto max_heapify(long long cur, Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                                 typename std::random_access_iterator_tag>::value,
                                                    void> {
    using std::swap;    //This is intentional, see Koenig lookup on cppreference

    const long long len = end - begin;
    while (cur < len) {
        long long greatest_id = cur;
        
        const long long left_id = left(cur);
        if (left_id < len) {
            if (less(elem_at(begin, greatest_id), elem_at(begin, left_id)))
                greatest_id = left_id;

            //The check for right child is nested inside the if block for a little optimization
            //because if left_id > len, there's no way right_id < len.
            const long long right_id = right(cur);
            if (right_id < len && less(elem_at(begin, greatest_id), elem_at(begin, right_id)))
                greatest_id = right_id;
        }

        if (greatest_id == cur) return;
        else {
            swap(elem_at(begin, greatest_id), elem_at(begin, cur));
            cur = greatest_id;
        }
    }
}


template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto build_max_heap(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                                 typename std::random_access_iterator_tag>::value,
                                                    void> {
    for (long long i = end - begin - 1; i >= 0; --i)
        max_heapify(i, begin, end, less);
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto move_max_to_back(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                                 typename std::random_access_iterator_tag>::value,
                                                    void> {
    using std::swap;

    swap(elem_at(begin, 0), *(end - 1));
    max_heapify(0, begin, end - 1, less);
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto heap_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                                 typename std::random_access_iterator_tag>::value,
                                                    void> {
    build_max_heap(begin, end, less);
    while (begin < end - 1) {
        move_max_to_back(begin, end, less);
        --end;
    }
}

#endif