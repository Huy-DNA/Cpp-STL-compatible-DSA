#ifndef __MERGE_SORT_HELL__
#define __MERGE_SORT_HELL__

#include <vector>
#include <iterator>
#include <type_traits>
#include <functional>

//Merge sort with random access iterators
/*---------------------------------------*/
template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto merge(Iter begin, Iter mid, Iter end, const Comp& less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category, 
                                                           typename std::random_access_iterator_tag>::value,
                                              void> {
    long long l_id = 0;
    long long r_id = 0;
    std::vector<Elem_T> buffer;
    
    while (begin + l_id < mid || mid + r_id < end) {
        const Iter l_ptr = begin + l_id;
        const Iter r_ptr = mid + r_id;
        if (l_ptr >= mid) {
            buffer.push_back(*r_ptr);
            ++r_id;
        }
        else if (r_ptr >= end) {
            buffer.push_back(*l_ptr);
            ++l_id;
        }
        else if (less(*r_ptr, *l_ptr)) {
            buffer.push_back(*r_ptr);
            ++r_id;
        }
        else {
            buffer.push_back(*l_ptr);
            ++l_id;
        }
    }
    
    Iter i_ptr = begin;
    for (Elem_T& e: buffer) {
        *i_ptr = e;
        ++i_ptr;
    }
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto split(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category, 
                                                           typename std::random_access_iterator_tag>::value,
                                              void> {
    if (begin < end - 1) {
        const long long half_dist = (end - begin) / 2;
        const Iter mid = begin + half_dist;
        split(begin, mid, less);
        split(mid, end, less);
        merge(begin, mid, end, less);
    }
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto merge_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category, 
                                                           typename std::random_access_iterator_tag>::value,
                                              void> {
    split(begin, end, less);
}

//Merge sort with forward and bidirectional iterators
/*--------------------------------------------*/
template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto merge(Iter begin, Iter mid, Iter end, Comp less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::bidirectional_iterator_tag>::value
                                                || std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::forward_iterator_tag>::value,
                                                void> {
    Iter l_iter = begin;
    Iter r_iter = mid;
    std::vector<Elem_T> buffer;

    while (l_iter != mid || r_iter != end) {
        if (l_iter == mid) {
            buffer.push_back(*r_iter);
            ++r_iter;
        } 
        else if (r_iter == end) {
            buffer.push_back(*l_iter);
            ++l_iter;
        } 
        else if (less(*r_iter, *l_iter)) {
            buffer.push_back(*r_iter);
            ++r_iter;
        }
        else {
            buffer.push_back(*l_iter);
            ++l_iter;
        }
    }

    Iter cur_iter = begin;
    for (Elem_T& v: buffer) {
        *cur_iter = v;
        ++cur_iter;
    }
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto split(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{}) 
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::bidirectional_iterator_tag>::value
                                                || std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::forward_iterator_tag>::value,
                                                void> {
    Iter tmp = begin;           //This is dumb
    if (++tmp == end) return;

    Iter fast = begin, slow = begin;
    while (fast != end && ++fast != end) {
        ++slow;
        ++fast;
    }
    split(begin, slow, less);
    split(slow, end, less);
    merge(begin, slow, end, less);
}

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto merge_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::bidirectional_iterator_tag>::value
                                                || std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::forward_iterator_tag>::value,
                                                void> {
    split(begin, end, less);
}
#endif