#ifndef __COUNTING_SORT_HELL__
#define __COUNTING_SORT_HELL__

#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>

/*This function (2 overloads) requires the elements are of integral type or object types having an integral-typed field named 'key'.
  All elements between begin and end are assumed to lie within [0, k] or have their 'key' values lie within [0, k].
  Otherwise, the behavior is undefined.*/
template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>>
auto counting_sort(Iter begin, Iter end, unsigned long long k)
                        -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                         typename std::random_access_iterator_tag>::value 
                                            && std::is_integral<Elem_T>::value,
                                            void> {
    std::vector<unsigned long long> buffer(k + 1);          
    for (Iter i_ptr = begin; i_ptr < end; ++i_ptr)
        ++buffer[*i_ptr];                           //buffer[i] now stores the total occurences of i between begin and end
    for (long long i = 1; i < k + 1; ++i)
        buffer[i] += buffer[i - 1];                 //buffer[i] now stores the total occurences of numbers no greater than i
    
    std::vector<Elem_T> res(end - begin);           //intermediatary buffer storing the final sorted array
    for (Iter i_ptr = end - 1; i_ptr >= begin; --i_ptr) {
        res[buffer[*i_ptr] - 1] = *i_ptr;
        --buffer[*i_ptr];
    }

    for (long long i = 0; i < end - begin; ++i)
        *(begin + i) = res[i]; 
}

template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>>
auto counting_sort(Iter begin, Iter end, unsigned long long k)
                        -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                         typename std::random_access_iterator_tag>::value 
                                            && std::is_integral<decltype(Elem_T().key)>::value,
                                            void> {
    std::vector<unsigned long long> buffer(k + 1);          
    for (Iter i_ptr = begin; i_ptr < end; ++i_ptr)
        ++buffer[i_ptr->key];                           //buffer[i] now stores the total occurences of i between begin and end
    for (long long i = 1; i < k + 1; ++i)
        buffer[i] += buffer[i - 1];                     //buffer[i] now stores the total occurences of numbers no greater than i
    
    std::vector<Elem_T> res(end - begin);               //intermediatary buffer storing the final sorted array
    for (Iter i_ptr = end - 1; i_ptr >= begin; --i_ptr) {
        res[buffer[i_ptr->key] - 1] = *i_ptr;
        --buffer[i_ptr->key];
    }

    for (long long i = 0; i < end - begin; ++i)
        *(begin + i) = res[i]; 
}


#endif