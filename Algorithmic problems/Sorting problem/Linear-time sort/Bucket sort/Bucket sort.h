#ifndef __BUCKET_SORT_HELL__
#define __BUCKET_SORT_HELL__

#include "Linked list.h"
#include <type_traits>
#include <iterator>
#include <vector>

/*This function only works with elements of floating point type.
  It assumes that all elements are within the range [0, 1).*/
template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>>
auto bucket_sort(Iter begin, Iter end)
                    -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                     typename std::random_access_iterator_tag>::value
                                                     && std::is_floating_point<Elem_T>::value,
                                        void> {
    const unsigned long long len = end - begin;
    std::vector<LinkedList<Elem_T>> bucket_list(len);
    
    //Put elements into their buckets
    for (Iter i_ptr = begin; i_ptr < end; ++i_ptr) {
        const unsigned long long i_bucket = *i_ptr * len;
        bucket_list[i_bucket].push_back(*i_ptr);
    }

    //Insertion sort the elements in each bucket
    for (auto& bucket: bucket_list)
        bucket.insertion_sort();
    
    //Combine the list
    LinkedList<Elem_T> res;
    for (auto& bucket: bucket_list)
        res.concat(bucket);
    
    auto res_values = res.get_list_content();    //This could be optimized though
    
    for (long long i = 0; i < len; ++i)
        *(begin + i) = res_values[i];
}

#endif