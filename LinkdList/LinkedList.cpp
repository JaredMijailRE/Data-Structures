#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

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

    void printList(ostream& os = cout) const {
        Node* temp = head;
        os << "Elementos en la lista enlazada: [";
        while (temp != nullptr) {
            os << temp->data;
            if (temp->next != nullptr)
                os << " ";
            temp = temp->next;
        }
        os << "]" << endl;
    }

    void inserSort(int key){
        if (head == nullptr){
            pushFront(key);
        }else{
            Node* temp = head;
            if(key <= temp->data){
                pushFront(key);
                return;}
            while (temp->next != nullptr) {
                if (temp->data < key && key <= temp->next->data) {
                    addAfter(temp, key);
                    return;}
                temp = temp->next;
            } pushBack(key);
        }
    }
};

int main() {
    LinkedList list;
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
                    if (ss >> value) {
                        list.pushBack(value);
                    } else {
                        cout << "Error: Falta el valor para añadir al final." << endl;
                    }
                    break;
                case 3: // Remove last
                    list.popBack();
                    break;
                case 4: // Add to beginning
                    if (ss >> value) {
                        list.pushFront(value);
                    } else {
                        cout << "Error: Falta el valor para añadir al principio." << endl;
                    }
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
