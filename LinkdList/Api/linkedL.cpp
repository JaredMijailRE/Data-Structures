#include <iostream>
#include <string>
#include <pybind11/pybind11.h>


namespace py = pybind11;

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        // Liberar memoria
        while (!booleanEmpty()) {
            popFront();
        }
    }

    void pushFront(int key) {
        Node* nodo = new Node(key);
        nodo->next = head;
        head = nodo;
    }

    int keyFront() const {
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el elemento del frente.");
        return head->data;
    }

    void popFront() {
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento del frente.");
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void pushBack(int key) {
        Node* nodo = new Node(key);
        if (head == nullptr) {
            head = nodo;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = nodo;
        }
    }

    int keyTopBack() const {
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede obtener el último elemento.");
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void popBack() {
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el último elemento.");
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    bool booleanFind(int key) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == key)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void erase(int key) {
        if (head == nullptr)
            throw runtime_error("Lista vacía. No se puede eliminar el elemento.");
        if (head->data == key) {
            popFront();
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != key) {
            temp = temp->next;
        }
        if (temp->next == nullptr)
            throw runtime_error("Elemento no encontrado en la lista.");
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    bool booleanEmpty() const {
        return head == nullptr;
    }

    void addBefore(Node* node, int key) {
        if (head == nullptr || node == head) {
            pushFront(key);
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next != node) {
            temp = temp->next;
        }
        if (temp->next == nullptr)
            throw runtime_error("Nodo no encontrado en la lista.");
        Node* newNodo = new Node(key);
        newNodo->next = node;
        temp->next = newNodo;
    }

    void addAfter(Node* node, int key) {
        if (node == nullptr)
            throw runtime_error("Referencia inválida de nodo.");
        Node* newNodo = new Node(key);
        newNodo->next = node->next;
        node->next = newNodo;
    }

    std::string PrintList() const {
        std::string output = "{ ";
        Node* temp = head;
        while (temp != nullptr) {
            output += std::to_string(temp->data);
            temp = temp->next;
            if (temp != nullptr) output += ", ";
        }
        output += " }";
        return output;
    }
};


PYBIND11_MODULE(linkedL, m) {
    m.doc() = "Python bindings for LinkedList"; 

    py::class_<LinkedList>(m, "linkedL")
        .def(py::init<>()) // Constructor por defecto
        .def("pushFront", &LinkedList::pushFront, py::arg("key"), "Agrega un nodo al inicio de la lista")
        .def("pushBack", &LinkedList::pushBack, py::arg("key"), "Agrega un nodo al final de la lista")
        .def("popFront", &LinkedList::popFront, "Elimina el nodo al inicio de la lista")
        .def("popBack", &LinkedList::popBack, "Elimina el nodo al final de la lista")
        .def("keyFront", &LinkedList::keyFront, "Devuelve el valor del nodo al inicio de la lista")
        .def("keyTopBack", &LinkedList::keyTopBack, "Devuelve el valor del nodo al final de la lista")
        .def("find", &LinkedList::booleanFind, py::arg("key"), "Devuelve si un elemento está en la lista")
        .def("erase", &LinkedList::erase, py::arg("key"), "Elimina un nodo con un valor específico")
        .def("empty", &LinkedList::booleanEmpty, "Devuelve si la lista está vacía")
        .def("print_list", &LinkedList::PrintList, "Imprime la lista");
}