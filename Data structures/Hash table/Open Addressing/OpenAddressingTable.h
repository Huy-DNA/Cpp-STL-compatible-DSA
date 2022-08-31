#include <stdexcept>
#include <functional>
#include <type_traits>

template <typename Key_T, typename Value_T, typename Hasher_T = std::hash<Key_T>, std::size_t TABLE_SIZE = 101,
          typename = std::enable_if_t<std::is_trivially_copyable<Key_T>::value, void>,
          typename = std::enable_if_t<std::is_trivially_copyable<Value_T>::value, void>>
class OpenAddressingTable {
    typedef std::size_t size_t;
    struct KeyValuePair {
        Key_T key;
        Value_T value;
        bool empty = true;
    };
public:
    OpenAddressingTable(std::string method = "linear"): _probe_method{method} {
        if (!_valid_probe_method()) throw std::runtime_error{"Invalid probing method."};
    }

    Value_T& operator[](const Key_T& key) { 
        if (_probe_method == "linear") {
            for (size_t round = 0; round < TABLE_SIZE; ++round) {
                const size_t id = _linear_probing(key, !round);
                if (_null_at(id)) throw std::runtime_error{"Indexing on non-existent key."};
                if (_key_at(id) == key)
                    return _value_at(id);
            }
        } else throw std::runtime_error{"Unimplemented probe method"};      //To be implemented

        throw std::runtime_error{"Indexing on non-existent key."};
    }

    void insert(const Key_T& key, const Value_T& value) {
        if (_probe_method == "linear") {
            for (size_t round = 0; round < TABLE_SIZE; ++round) {
                const size_t id = _linear_probing(key, !round);
                if (_null_at(id)) {
                    _key_at(id) = key;
                    _value_at(id) = value;
                    _table[id].empty = false;
                    return;
                } else if (_key_at(id) == key)
                    throw std::runtime_error{"OpenAddressingTable::insert() called on already inserted key."};
            }
        } else throw std::runtime_error{"Unimplemented probe method"};      //To be implemented
        
        throw std::runtime_error{"OpenAddressingTable::insert() called on full table."};
    }

private:
    size_t _linear_probing(const Key_T& key, bool reset = false) const {
        static const Key_T* cache_key = nullptr;
        static size_t cache_hash;

        if (&key != cache_key || reset) {
            cache_key = &key;
            cache_hash = hash(key);
        } else {
            cache_hash = (cache_hash + 1) % TABLE_SIZE;
        }

        return cache_hash;
    }
    size_t hash(const Key_T& key) const {
        return hasher(key) % TABLE_SIZE;
    }

    bool _valid_probe_method() const {
        if (_probe_method != "linear" && _probe_method != "quadratic")
            return false;
        return true;
    }

    bool _null_at(size_t id) const {
        return _table[id].empty;
    }

    Key_T& _key_at(size_t id) {
        return _table[id].key;
    }

    Value_T& _value_at(size_t id) {
        return _table[id].value;
    }

    KeyValuePair _table[TABLE_SIZE];
    const Hasher_T hasher{};
    const std::string _probe_method;    //either `linear` or `quadratic`
};