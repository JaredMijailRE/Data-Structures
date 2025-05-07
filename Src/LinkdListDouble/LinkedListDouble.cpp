#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* before;

    Node(T value) : data(value), next(nullptr), before(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
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

    void printList(ostream& os = cout) { // Imprimir lista
        Node<T>* temp = head;
        os << "Elementos en la lista enlazada: [";
        while (temp != nullptr) {
            os << temp->data;
            if (temp->next != nullptr)
                os << " ";
            temp = temp->next;
        }
        os << "]" << endl;
    }
};

int main() {
    LinkedList<int> list;
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        int command, value;
        ss >> command;

        try {
            switch (command) {
                case 1: // Imprimir lista
                    list.printList();
                    break;
                case 2: // Agregar al final
                    ss >> value;
                    list.pushBack(value);
                    break;
                case 3: // Quitar último
                    list.popBack();
                    break;
                case 4: // Agregar al inicio
                    ss >> value;
                    list.pushFront(value);
                    break;
                case 5: // Quitar primero
                    list.popFront();
                    break;
                default:
                    cout << "Error: Comando inválido." << endl;
            }
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
