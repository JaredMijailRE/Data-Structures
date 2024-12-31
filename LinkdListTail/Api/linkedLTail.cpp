#include <iostream>
#include <string>
#include <pybind11/pybind11.h>


namespace py = pybind11;

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

    void pushFrontBase(T key) { // agregar nodo al comienzo
        Node<T>* nodo = new Node<T>(key);
        nodo->next = head;
        head = nodo;
        if (tail == nullptr) { // Si la lista estaba vacía
            tail = head;
        }
    }

    void popFrontBase() { // quitar nodo comienzo
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        Node<T>* temp = head;
        head = head->next;
        if (head == nullptr) { // Si la lista queda vacía
            tail = nullptr;
        }
        delete temp;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while (!booleanEmpty()) {
            popFront();
        }
    }

    void pushFront(T key) { // agregar nodo al comienzo (con actualización de tail)
        pushFrontBase(key);
    }

    T keyFront() {  // retornar data comienzo
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el elemento.");
        return head->data;
    }

    void popFront() { // quitar nodo comienzo
        popFrontBase();
    }

    void pushBack(T key) { // agregar nodo final
        Node<T>* nodo = new Node<T>(key);
        if (tail == nullptr) { // Lista vacía
            head = tail = nodo;
        } else {
            tail->next = nodo;
            tail = nodo;
        }
    }

    T keyTopBack() { // retornar data final
        if (tail == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el elemento.");
        return tail->data;
    }

    void popBack() { // quitar nodo final
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        if (head->next == nullptr) { // Un único elemento
            delete head;
            head = tail = nullptr;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    bool booleanFind(T key) { // esta elemento?
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void erase(T key) { // eliminar x elemento
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        if (head->data == key) {
            popFront();
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != key) {
            temp = temp->next;
        }
        if (temp->next == nullptr)
            throw runtime_error("Elemento no encontrado.");
        Node<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        if (toDelete == tail) { // Si se elimina el último nodo
            tail = temp;
        }
        delete toDelete;
    }

    bool booleanEmpty() { // lista vacía?
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


PYBIND11_MODULE(linkedLTail, m) {
    m.doc() = "Python bindings for LinkedList with Tail"; 

    py::class_<LinkedList<int>>(m, "linkedLTail")
        .def(py::init<>()) // Constructor por defecto
        .def("pushFront", &LinkedList<int>::pushFront, py::arg("key"), "Agrega un nodo al inicio de la lista")
        .def("pushBack", &LinkedList<int>::pushBack, py::arg("key"), "Agrega un nodo al final de la lista")
        .def("popFront", &LinkedList<int>::popFront, "Elimina el nodo al inicio de la lista")
        .def("popBack", &LinkedList<int>::popBack, "Elimina el nodo al final de la lista")
        .def("keyFront", &LinkedList<int>::keyFront, "Devuelve el valor del nodo al inicio de la lista")
        .def("keyTopBack", &LinkedList<int>::keyTopBack, "Devuelve el valor del nodo al final de la lista")
        .def("find", &LinkedList<int>::booleanFind, py::arg("key"), "Devuelve si un elemento está en la lista")
        .def("erase", &LinkedList<int>::erase, py::arg("key"), "Elimina un nodo con un valor específico")
        .def("empty", &LinkedList<int>::booleanEmpty, "Devuelve si la lista está vacía")
        .def("print_list", &LinkedList<int>::PrintList, "Imprime la lista");
}