#ifndef __RADIX_SORT_HELL__
#define __RADIX_SORT_HELL__

#include <type_traits>
#include <functional>
#include <iterator>
#include "Stable sort.h"

/*This function require that all elements or the fields 'key' of them be positive and of intergral type.
 The third parameter specifies the upper bound of the elements or their 'key' values, so that they lie within [0, k].*/
template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>>
auto radix_sort(Iter begin, Iter end, unsigned long long k)
                    -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                     typename std::random_access_iterator_tag>::value
                                        && std::is_integral<Elem_T>::value,
                                        void> {
    int log2_floor(unsigned long long n);
    int get_kth_rbit_group(unsigned long long n, int k, int r);
    
    if (end - begin <= 1) return;
    const int bit_group_size = log2_floor(end - begin);         //Treat a digit as a group of 'bit_group_size' bits
    const int max_digit = (1 << bit_group_size) - 1;            //Maximum value a digit can have
    
    for (int i = 1; k > 0; k >>= bit_group_size, ++i)
        stable_sort(begin, end, max_digit, [=](unsigned long long n){return get_kth_rbit_group(n, i, bit_group_size);});
    
}

template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>>
auto radix_sort(Iter begin, Iter end, unsigned long long k)
                    -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                     typename std::random_access_iterator_tag>::value
                                        && std::is_integral<decltype(Elem_T().key)>::value,
                                        void> {
    int log2_floor(unsigned long long n);
    int get_kth_rbit_group(unsigned long long n, int k, int r);
    
    if (end - begin <= 1) return;
    const int bit_group_size = log2_floor(end - begin);         //Treat a digit as a group of 'bit_group_size' bits
    const int max_digit = (1 << bit_group_size) - 1;            //Maximum value a digit can have
    
    for (int i = 1; k > 0; k >>= bit_group_size, ++i)
        stable_sort(begin, end, max_digit, [=](unsigned long long n){return get_kth_rbit_group(n, i, bit_group_size);});
    
}

inline int log2_floor(unsigned long long n) {
    for (int i = 1;; ++i)
        if ((1 << i) > n)
            return i - 1;
    return -1;
}

inline int get_kth_rbit_group(unsigned long long n, int k, int r) {
    unsigned long long bitmask = (1 << r) - 1;
    return (n >> ((k - 1) * r)) & bitmask;
}

#endif
