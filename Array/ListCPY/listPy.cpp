#include <pybind11/pybind11.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace py = pybind11;

template <typename T>
class StaticArrayList {
private:
    T* data;
    int max_size;
    int size;

public:
    StaticArrayList(int max_size) : max_size(max_size), size(0) {
        data = new T[max_size];
    }

    ~StaticArrayList() {
        delete[] data;
    }

    bool Empty() const {
        return size == 0;
    }

    void PushFront(const T& element) {
        if (size >= max_size) throw std::overflow_error("List is full");
        for (int i = size; i > 0; --i) {
            data[i] = data[i - 1];
        }
        data[0] = element;
        size++;
    }

    void PushBack(const T& element) {
        if (size >= max_size) throw std::overflow_error("List is full");
        data[size++] = element;
    }

    void PopFront() {
        if (Empty()) throw std::underflow_error("List is empty");
        for (int i = 0; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void PopBack() {
        if (Empty()) throw std::underflow_error("List is empty");
        size--;
    }

    bool Find(const T& element) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == element) return true;
        }
        return false;
    }

    void Erase(const T& element) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (data[i] == element) {
                index = i;
                break;
            }
        }
        if (index == -1) throw std::runtime_error("Element not found");

        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void AddBefore(const T& target, const T& element) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (data[i] == target) {
                index = i;
                break;
            }
        }
        if (index == -1) throw std::runtime_error("Target not found");

        if (size >= max_size) throw std::overflow_error("List is full");

        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        size++;
    }

    void AddAfter(const T& target, const T& element) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (data[i] == target) {
                index = i;
                break;
            }
        }
        if (index == -1) throw std::runtime_error("Target not found");

        if (size >= max_size) throw std::overflow_error("List is full");

        for (int i = size; i > index + 1; --i) {
            data[i] = data[i - 1];
        }
        data[index + 1] = element;
        size++;
    }

    std::string PrintList() const {
        std::string output = "{ ";
        for (int i = 0; i < size; ++i) {
            output += std::to_string(data[i]);
            if (i < size - 1) output += ", ";
        }
        output += " }";
        return output;
    }
};

PYBIND11_MODULE(listPy, m) {
    m.doc() = "Python bindings for StaticArrayList";  // Descripción del módulo

    py::class_<StaticArrayList<int>>(m, "StaticArrayList")
        .def(py::init<int>(), py::arg("capacity"),
            "Inicializa una StaticArrayList con una capacidad específica")
        .def("empty", &StaticArrayList<int>::Empty,
            "Devuelve True si la lista está vacía, False en caso contrario")
        .def("pushFront", &StaticArrayList<int>::PushFront, py::arg("value"),
            "Agrega un elemento al inicio de la lista")
        .def("pushBack", &StaticArrayList<int>::PushBack, py::arg("value"),
            "Agrega un elemento al final de la lista")
        .def("popFront", &StaticArrayList<int>::PopFront,
            "Elimina el primer elemento de la lista")
        .def("popBack", &StaticArrayList<int>::PopBack,
            "Elimina el último elemento de la lista")
        .def("find", &StaticArrayList<int>::Find, py::arg("value"),
            "Busca un elemento y devuelve su índice o -1 si no se encuentra")
        .def("erase", &StaticArrayList<int>::Erase, py::arg("index"),
            "Elimina un elemento en el índice especificado")
        .def("addBefore", &StaticArrayList<int>::AddBefore, py::arg("index"), py::arg("value"),
            "Agrega un elemento antes del índice especificado")
        .def("addAfter", &StaticArrayList<int>::AddAfter, py::arg("index"), py::arg("value"),
            "Agrega un elemento después del índice especificado")
        .def("print_list", &StaticArrayList<int>::PrintList,
            "Imprime todos los elementos de la lista en la consola");
}
