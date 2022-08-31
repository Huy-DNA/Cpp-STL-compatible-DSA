#ifndef __QUICK_SORT_HELL__
#define __QUICK_SORT_HELL__

#include <functional>
#include <type_traits>
#include <iterator>
#include <random>
#include <utility>

template <typename Iter, typename Elem_T = typename std::iterator_traits<Iter>::value_type, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto quick_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                    -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category, 
                                                     typename std::random_access_iterator_tag>::value,
                                        void> {
    using std::swap;                     //This is intentional, see Koenig lookup

    static std::mt19937_64 mt{0};        //For randomly picking a pivot

    if (begin < end - 1) {
        const long long len = end - begin;
        
        const long long pivot_id = std::uniform_int_distribution<long long>{0, len - 1}(mt);    //Randomly pick a pivot
        const Elem_T pivot_e = *(begin + pivot_id);     //The pivotal element

        long long less_right_id = 0;                    //The offset from 'begin' where an element would be swapped to if it's smaller than the pivotal element
        long long greater_left_id = len - 1;            //The offset from 'begin' where an element would be swapped to if it's greater than the pivotal element

        for (Iter i_ptr = begin; i_ptr <= begin + greater_left_id; ++i_ptr) {
            /* Partions the array into 3 parts l|e|g:
                l contains any elements that are less than the pivotal element
                e contains any elements that equal the pivotal elements
                g contains any elements that are greater than the pivotal element
            */
            if (less(*i_ptr, pivot_e)) {
                swap(*i_ptr, *(begin + less_right_id));
                ++less_right_id;
            }
            else if (less(pivot_e, *i_ptr)) {
                swap(*i_ptr, *(begin + greater_left_id));
                --greater_left_id;
                --i_ptr;
            }
        }

        quick_sort(begin, begin + less_right_id, less);         //Recursively sort the l part
        quick_sort(begin + greater_left_id + 1, end, less);     //Recursively sort the r part
    }
}

#endif