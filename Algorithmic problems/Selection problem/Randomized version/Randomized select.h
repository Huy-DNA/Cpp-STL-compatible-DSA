#ifndef __RANDOMIZED_SELECTION_HELL__
#define __RANDOMIZED_SELECTION_HELL__

#include <functional>
#include <type_traits>
#include <iterator>
#include <random>
#include <utility>

template <typename Iter, typename Elem_T = std::remove_reference_t<decltype(*Iter())>, typename Comp = std::function<bool(const Elem_T&, const Elem_T&)>>
auto select(Iter begin, Iter end, unsigned long long k, Comp less = std::less<const Elem_T&>())
                -> std::enable_if_t<std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                                                 typename std::random_access_iterator_tag>::value,
                                    Elem_T> {
    using std::swap;
    static std::mt19937 mt;

    while (true) {
        const long long len = end - begin;
        const long long pivot_id = std::uniform_int_distribution<long long>{0, len - 1}(mt);
        const Elem_T pivot_e = *(begin + pivot_id);

        long long less_right_id = 0;
        long long greater_left_id = len - 1;
        for (Iter i_ptr = begin; i_ptr <= begin + greater_left_id; ++i_ptr) {
            if (less(*i_ptr, pivot_e)) {
                swap(*i_ptr, *(begin + less_right_id));
                ++less_right_id;
            } else if (less(pivot_e, *i_ptr)) {
                swap(*i_ptr, *(begin + greater_left_id));
                --greater_left_id;
                --i_ptr;
            }
        }

        if (less_right_id > k - 1)
            end = begin + less_right_id;
        else if (greater_left_id < k - 1) {
            begin += greater_left_id + 1;
            k -= greater_left_id + 1;
        }
        else return pivot_e;
    }
}

#endif