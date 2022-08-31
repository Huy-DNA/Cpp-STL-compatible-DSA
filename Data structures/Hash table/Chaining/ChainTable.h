#ifndef __CHAIN_TABLE_HELL__
#define __CHAIN_TABLE_HELL__

#include "../../Linked list/Non-circular doubly linked list/LinkedList.h"
#include <type_traits>
#include <stdexcept>
#include <functional>

template <typename Key_T, typename Value_T, typename Hasher_T = std::hash<Key_T>, std::size_t TABLE_SIZE = 31,
          typename = std::enable_if_t<std::is_trivially_copyable<Value_T>::value, void>>
class ChainTable {
    typedef std::size_t size_t;
    struct KeyValuePair {
        Key_T key;
        Value_T value;
        bool operator==(const KeyValuePair& other) const {
            return key == other.key;
        }
        bool operator==(const Key_T& key_other) const {
            return key == key_other;
        }
    };
public:
    Value_T& operator[](const Key_T& key) {
        const size_t id = hash(key);
        LinkedList<KeyValuePair>& list = _table[id];        // The slot that `key` hashes to

        auto key_pos = list.search(key);
        if (!key_pos) throw std::runtime_error{"Indexing on non-existent key."};

        return key_pos->value;
    }

    void insert(const Key_T& key, const Value_T& value) {
        const size_t id = hash(key);
        LinkedList<KeyValuePair>& list = _table[id];        // The slot that `key` hashes to
        
        auto key_pos = list.search(key);
        if (key_pos) throw std::runtime_error{"ChainTable::insert() called on already existed key."};
        
        list.push_back({key, value});
    }

    Value_T remove(const Key_T& key) {
        const size_t id = hash(key);
        LinkedList<KeyValuePair>& list = _table[id];        // The slot that `key` hashes to

        auto key_pos = list.search(key);
        if (!key_pos) throw std::runtime_error{"ChainTable::remove() called on non-existent key."};

        return list.remove(key_pos).value;
    }
private:
    std::size_t hash(const Key_T& key) const {
        return _key_hasher(key) % TABLE_SIZE;
    }

    LinkedList<KeyValuePair> _table[TABLE_SIZE];
    const Hasher_T _key_hasher{};
};

#endif