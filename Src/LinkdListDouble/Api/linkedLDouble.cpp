#include <iostream>
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* before;

    Node(T value) : data(value), next(nullptr), before(nullptr) {}
};

template <typename T>
class LinkedL {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedL() : head(nullptr), tail(nullptr) {}

    ~LinkedL() {
        // Destructor para liberar memoria
        while (!booleanEmpty()) {
            popFront();
        }
    }

    void pushFront(T key) { // Agregar nodo al comienzo
        Node<T>* nodo = new Node<T>(key);
        nodo->next = head;
        if (head != nullptr) {
            head->before = nodo;
        }
        head = nodo;
        if (tail == nullptr) {
            tail = nodo; // Si es el primer nodo, actualizar el tail
        }
    }

    T keyFront() { // Retornar dato al comienzo
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el elemento.");
        return head->data;
    }

    void popFront() { // Quitar nodo al comienzo
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->before = nullptr;
        } else {
            tail = nullptr; // Lista quedó vacía
        }
        delete temp;
    }

    void pushBack(T key) { // Agregar nodo al final
        Node<T>* nodo = new Node<T>(key);
        if (tail != nullptr) {
            tail->next = nodo;
            nodo->before = tail;
        } else {
            head = nodo; // Si la lista está vacía, actualizar el head
        }
        tail = nodo;
    }

    T keyTopBack() { // Retornar dato al final
        if (tail == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el elemento.");
        return tail->data;
    }

    void popBack() { // Quitar nodo al final
        if (tail == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        Node<T>* temp = tail;
        tail = tail->before;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr; // Lista quedó vacía
        }
        delete temp;
    }

    bool booleanFind(T key) { // Verificar si el elemento existe
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void erase(T key) { // Eliminar nodo con valor específico
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        if (head->data == key) {
            popFront();
            return;
        }
        Node<T>* temp = head;
        while (temp != nullptr && temp->data != key) {
            temp = temp->next;
        }
        if (temp == nullptr)
            throw runtime_error("El elemento no existe.");
        if (temp->next != nullptr) {
            temp->next->before = temp->before;
        }
        if (temp->before != nullptr) {
            temp->before->next = temp->next;
        }
        if (temp == tail) {
            tail = temp->before;
        }
        delete temp;
    }

    bool booleanEmpty() { // Verificar si la lista está vacía
        return head == nullptr;
    }

    std::string PrintList() const {
        std::string output = "{ ";
        Node<T>* temp = head;
        while (temp != nullptr) {
            output += std::to_string(temp->data);
            temp = temp->next;
            if (temp != nullptr) output += ", ";
        }
        output += " }";
        return output;
    }
};

PYBIND11_MODULE(linkedLDouble, m) {
    m.doc() = "Python bindings for LinkedList double"; 

    py::class_<LinkedL<int>>(m, "LinkedList")
        .def(py::init<>()) // Constructor por defecto
        .def("pushFront", &LinkedL<int>::pushFront, py::arg("key"), "Agrega un nodo al inicio de la lista")
        .def("pushBack", &LinkedL<int>::pushBack, py::arg("key"), "Agrega un nodo al final de la lista")
        .def("popFront", &LinkedL<int>::popFront, "Elimina el nodo al inicio de la lista")
        .def("popBack", &LinkedL<int>::popBack, "Elimina el nodo al final de la lista")
        .def("keyFront", &LinkedL<int>::keyFront, "Devuelve el valor del nodo al inicio de la lista")
        .def("keyTopBack", &LinkedL<int>::keyTopBack, "Devuelve el valor del nodo al final de la lista")
        .def("find", &LinkedL<int>::booleanFind, py::arg("key"), "Devuelve si un elemento está en la lista")
        .def("erase", &LinkedL<int>::erase, py::arg("key"), "Elimina un nodo con un valor específico")
        .def("empty", &LinkedL<int>::booleanEmpty, "Devuelve si la lista está vacía")
        .def("print_list", &LinkedL<int>::PrintList, "Imprime la lista");
}
