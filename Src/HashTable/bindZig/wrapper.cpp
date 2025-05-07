#include <pybind11/pybind11.h>
#include <stdexcept>
#include "MyHashTable.h"  // Use your manually created header

namespace py = pybind11;

class PyHashTable {
public:
    // Constructor: creates a new hash table with the given size.
    PyHashTable(size_t size) {
        table = create_u32_hash_table_default(size);
        if (table == nullptr) {
            throw std::runtime_error("Failed to create hash table");
        }
    }

    // Destructor: cleans up the hash table.
    ~PyHashTable() {
        destroy_u32_hash_table(table);
    }

    // Insert a key-value pair.
    void insert(uint32_t key, uint32_t value) {
        if (insert_u32(table, key, value) != 0) {
            throw std::runtime_error("Insert failed");
        }
    }

    // Search for a key; returns the value if found.
    uint32_t search(uint32_t key) {
        uint32_t result;
        if (search_u32(table, key, &result) != 0) {
            throw std::runtime_error("Key not found");
        }
        return result;
    }

    // Remove a key; returns the removed value if found.
    uint32_t remove(uint32_t key) {
        uint32_t result;
        if (remove_u32(table, key, &result) != 0) {
            throw std::runtime_error("Key not found");
        }
        return result;
    }

    // Update the value for a key.
    void update(uint32_t key, uint32_t value) {
        if (update_u32(table, key, value) != 0) {
            throw std::runtime_error("Update failed");
        }
    }

private:
    // Underlying pointer to the hash table.
    HashTable_u32_u32* table;
};

PYBIND11_MODULE(HashTableZig, m) {
    m.doc() = "A simple hash table module implemented in Zig";
    py::class_<PyHashTable>(m, "HashTableZig")
        .def(py::init<size_t>())
        .def("insert", &PyHashTable::insert)
        .def("search", &PyHashTable::search)
        .def("remove", &PyHashTable::remove)
        .def("update", &PyHashTable::update);
}
