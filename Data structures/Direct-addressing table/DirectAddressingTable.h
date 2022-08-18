#ifndef __DIRECT_ADDRESSING_TABLE__
#define __DIRECT_ADDRESSING_TABLE__

#include <type_traits>
#include <stdexcept>
#include <bitset>

/*DirectAddressingTable<Value_T, K_MAX> can be thought of as mapping from a key in range [0, K_MAX] to a value of Value_T.
  Value_T must be of TriviallyCopyableType,
  K_MAX must be nonnegative.*/
template <typename Value_T, size_t K_MAX,
          typename = std::enable_if_t<std::is_trivially_copyable<Value_T>::value, void>,
          typename = std::enable_if_t<K_MAX >= 0, void>>
class DirectAddressingTable {
    typedef std::size_t size_t;
public:
    Value_T& operator[](size_t key) {
        if (!_nonnull[key]) throw std::runtime_error{"Indexing empty slot."};
        return _table[key];
    }

    const Value_T& operator[](size_t key) const {
        if (!_nonnull[key]) throw std::runtime_error{"Indexing empty slot."};
        return _table[key];
    }

    void insert(size_t key, const Value_T& value) {
        if (_nonnull[key]) throw std::runtime_error{"DirectAddressingTable::insert() called on already inserted slot."};
        _nonnull[key] = true;
        _table[key] = value;
    }

    Value_T remove(size_t key) {
        if (!_nonnull[key]) throw std::runtime_error{"DirectAddressingTable::remove() called on empty slot."};
        _nonnull[key] = false;
        return _table[key];
    }
private:
    Value_T _table[K_MAX + 1];
    std::bitset<K_MAX + 1> _nonnull;
};
#endif