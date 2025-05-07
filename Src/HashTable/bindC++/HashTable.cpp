#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <functional>
#include <stdexcept>
#include <optional>
#include <string>

namespace py = pybind11;

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

    // Renamed from "delete" to "remove" to avoid conflict with Python reserved words
    std::optional<Value> remove(const Key& key) {
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

// Instantiate the template for a hash table with string keys and string values.
using HashTableString = HashTable<int, int>;

PYBIND11_MODULE(HashTableCpp, m) {
    m.doc() = "A simple hash table module implemented in C++";

    py::class_<HashTableString>(m, "HashTableCpp")
        .def(py::init<size_t>(), py::arg("size"))
        .def("insert", &HashTableString::insert, py::arg("key"), py::arg("value"),
             "Insert a key-value pair into the hash table")
        .def("search", &HashTableString::search, py::arg("key"),
             "Search for a key in the hash table. Returns the value or None if not found")
        .def("remove", &HashTableString::remove, py::arg("key"),
             "Remove a key from the hash table. Returns the removed value or None if key not found")
        .def("update", &HashTableString::update, py::arg("key"), py::arg("value"),
             "Update the value associated with the given key");
}
