#ifndef __NON_NEGATIVE_INTEGRAL_TYPE_INFERATOR_HELL__
#define __NON_NEGATIVE_INTEGRAL_TYPE_INFERATOR_HELL__

#include <climits>
#include <type_traits>
#include <cstdint>

/*Infer the smallest unsigned type such that `n` is within that type's range
  Returns a TypeWrapper object that wraps around the inferred type.*/
template <std::size_t n>
constexpr auto uint_infer() {
    if constexpr (n <= UINT8_MAX)
        return uint8_t{};
    if constexpr (UINT8_MAX < n && n <= UINT16_MAX)
        return uint16_t{};
    if constexpr (UINT16_MAX < n && n <= UINT32_MAX)
        return uint32_t{};
    if constexpr (UINT32_MAX < n && n <= UINT64_MAX)
        return uint64_t{};
}

template <std::size_t n>
using UIntInfer = std::remove_reference_t<decltype(infer<n>())>;

#endif
 