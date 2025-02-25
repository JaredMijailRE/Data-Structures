#include <vector>
#include <functional>
#include <stdexcept>
#include <optional>

template<typename Key, typename Value>
class HashTable {
private:
    size_t size;
    std::vector<std::vector<std::pair<Key, Value>>> table;

    size_t hash_function(const Key& key) const {
        return std::hash<Key>{}(key) % size;
    }

public:
    HashTable(size_t size) : size(size), table(size) {
        if (size == 0) {
            throw std::invalid_argument("Size must be greater than 0");
        }
    }

    void insert(const Key& key, const Value& value) {
        size_t index = hash_function(key);
        auto& bucket = table[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
    }

    std::optional<Value> search(const Key& key) const {
        size_t index = hash_function(key);
        const auto& bucket = table[index];
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return std::nullopt;
    }

    std::optional<Value> delete(const Key& key) {
        size_t index = hash_function(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                Value removed_value = it->second;
                bucket.erase(it);
                return removed_value;
            }
        }
        return std::nullopt;
    }

    void update(const Key& key, const Value& value) {
        size_t index = hash_function(key);
        auto& bucket = table[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        throw std::out_of_range("Key not found");
    }
};