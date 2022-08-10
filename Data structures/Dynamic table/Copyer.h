#ifndef __ARRAY_RESOURCE_TRIVIAL_COPYER__
#define __ARRAY_RESOURCE_TRIVIAL_COPYER__

#include <type_traits>

/*The elements to be copied must be of TriviallyCopyableType.
  Standard Copyer just simply copies elements in their original order.*/
template <typename Elem_T,
          typename = std::enable_if_t<std::is_trivially_copyable<Elem_T>::value,
                                      void>>
struct StandardResourceTrivialCopyer {
    void operator()(Elem_T* from_buffer, std::size_t from_size, Elem_T* to_buffer) const {
        memcpy(to_buffer, from_buffer, sizeof(Elem_T) * from_size);
    }
};

#endif