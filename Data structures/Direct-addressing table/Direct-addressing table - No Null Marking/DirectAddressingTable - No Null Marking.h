#ifndef __DIRECT_ADDRESSING_TABLE_NO_NULL_MARKING_HELL__
#define __DIRECT_ADDRESSING_TABLE_NO_NULL_MARKING_HELL__

#include "../../../CppUtilities/Unsigned Integral Inferator/UIntInfer.h"
#include "../../Dynamic table/DynamicTable.h"
#include <cstddef>
#include <type_traits>
#include <stdexcept>

/*DirectAddressingTable<Value_T, K_MAX> can be thought of as mapping from a key in range [0, K_MAX] to a value of Value_T.
  Value_T must be of TriviallyCopyableType,
  K_MAX must be nonnegative,
  Id_T is the type assumed for table indices,
  Additionally, this implementation only requires constant initialization time at the cost of more memory usage.*/
template <typename Value_T, std::size_t K_MAX, typename Id_T = UIntInfer<K_MAX>,
          typename = std::enable_if_t<std::is_trivially_copyable<Value_T>::value, void>>
class DirectAddressingTable {
public:
    Value_T& operator[](Id_T key) {
        if (null_at(key)) throw std::runtime_error{"Indexing empty slot."};
        return _table[key];
    }
    
    const Value_T& operator[](Id_T key) const {
        if (null_at(key)) throw std::runtime_error{"Indexing empty slot."};
        return _table[key];
    }

    void insert(Id_T key, const Value_T& value) {
        if (!null_at(key)) throw std::runtime_error{"DirectAddressingTable::insert() called on already inserted slot."};
        _table[key] = value;

        _pos_in_stack[key] = _id_stack.size();
        _id_stack.push_back(key);
    }

    Value_T remove(Id_T key) {
        if (null_at(key)) throw std::runtime_error{"DirectAddressingTable::remove() called on empty slot."};
        
        const Id_T key_pos_in_stack = _pos_in_stack[key];
        const Id_T last_id = _id_stack.pop_back();

        //Make last index fill in the spot of deleted key
        _id_stack[key_pos_in_stack] = last_id;
        _pos_in_stack[last_id] = key_pos_in_stack;

        return _table[key];
    }

    bool null_at(Id_T key) const {
        const Id_T key_pos_in_stack = _pos_in_stack[key];

        if (key_pos_in_stack >= _id_stack.size()) return true;
        if (_id_stack[key_pos_in_stack] != key) return true;

        return false;
    }
private:
    Value_T _table[K_MAX + 1];
    DynamicTable<Id_T> _id_stack;
    Id_T _pos_in_stack[K_MAX + 1];
};
#endif