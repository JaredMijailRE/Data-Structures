#include <iostream>
#include <stdexcept>

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

    void PrintList() const {
        std::cout << "{ ";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << " }" << std::endl;
    }
};

int main() {
    int listSize = 10; 
    StaticArrayList<int> list(listSize);

    list.PushFront(10);
    list.PushBack(20);
    list.PushBack(30);
    list.PushFront(5);
    list.PrintList();  

    return 0;
}
