#include <iostream>
#include <string>
#include <sstream>

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

    void printList(ostream& os = cout) { // imprimir
        Node<T>* temp = head;
        os << "Elementos en la lista enlazada: [";
        while (temp != nullptr) {
            os << temp->data;
            if (temp->next != nullptr)
                os << ", ";
            temp = temp->next;
        }
        os << "]" << endl;
    }

    void addAfter(Node<T>* node, int key) {
        if (node == nullptr)
            throw runtime_error("Referencia inválida de nodo.");
        Node<T>* newNodo = new Node<T>(key);
        newNodo->next = node->next;
        node->next = newNodo;
    }


    void inserSort(int key){
        if (head == nullptr){
            pushFront(key);
        if (tail->data < key) pushBack(key);
        }else{
            Node<T>* temp = head;
            if(key <= temp->data){
                pushFront(key);
                return;}
            while (true) {
                if (temp->data < key && key <= temp->next->data) {
                    addAfter(temp, key);
                    return;}
                temp = temp->next;}
        }
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
                case 1: // Print list
                    list.printList();
                    break;
                case 2: // Add to end
                    ss >> value;
                    list.pushBack(value);
                    break;
                case 3: // Remove last
                    list.popBack();
                    break;
                case 4: // Add to beginning
                    ss >> value;
                    list.pushFront(value);
                    break;
                case 5: // Remove first
                    list.popFront();
                    break;
                case 6:
                    if (ss >> value) {
                        list.inserSort(value);
                    } else {
                        cout << "Error: Falta el valor para añadir al final." << endl;
                    }
            }
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
