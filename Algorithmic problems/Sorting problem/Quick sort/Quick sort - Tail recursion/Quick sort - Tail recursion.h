#ifndef __QUICK_SORT_TAIL_RECURSION_HELL__
#define __QUICK_SORT_TAIL_RECURSION_HELL__

#include <random>
#include <utility>
#include <iterator>
#include <type_traits>
#include <functional>

template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto quick_sort(Iter begin, Iter end, const Comp& less = std::less<const Elem_T&>{})
                            -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                             typename std::random_access_iterator_tag>::value,
                                                void> {
    using std::swap;

    static std::mt19937_64 mt{0};

    while (begin < end - 1) {
        const long long len = end - begin;
        
        const long long pivot_id = std::uniform_int_distribution<long long>{0, len - 1}(mt);
        const Elem_T pivot_e = *(begin + pivot_id);

        long long less_right = 0;
        long long greater_left = len - 1;
        for (Iter i_ptr = begin; i_ptr <= begin + greater_left; ++i_ptr) {
            if (less(*i_ptr, pivot_e)) {
                swap(*i_ptr, *(begin + less_right));
                ++less_right;
            } else if (less(pivot_e, *i_ptr)) {
                swap(*i_ptr, *(begin + greater_left));
                --greater_left;
                --i_ptr;
            }
        }
        
        //Tail recursion: only one recursive call is needed!
        /*----------------------------------*/
        //Recursively sort the "shorter" part between l and g
        //Let the loop handle the longer part
        //Because the shorter part is less than half the original length,
        //There would be at most lg n stack frames on the call stack
        if (less_right < len - greater_left) {
            quick_sort(begin, begin + less_right, less);
            begin += greater_left + 1;
        } else {
            quick_sort(begin + greater_left + 1, end, less);
            end = begin + less_right;
        }
        /*----------------------------------*/
    }
}

#endif