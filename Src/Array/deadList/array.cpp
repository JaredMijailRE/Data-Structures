#include <iostream>
using namespace std;

struct ARRAY { // Array estatico de 3 espacios
    unsigned short a;
    unsigned short b;
    unsigned short c;
};

ARRAY addLast(ARRAY array, unsigned short value) {
    if (array.a == 0) {
        array.a = value;
    } else if (array.b == 0) {
        array.b = value;
    } else if (array.c == 0) {
        array.c = value;
    } else {
        array.a = array.b;
        array.b = array.c;
        array.c = value;
    }
    return array;
}

ARRAY removeLast(ARRAY array) {
    if (array.c != 0) {
        array.c = 0;
    } else if (array.b != 0) {
        array.b = 0;
    } else if (array.a != 0) {
        array.a = 0;
    }
    return array;
}

ARRAY addFirst(ARRAY array, unsigned short value) {
    if (array.c != 0) {
        array.c = array.b;
        array.b = array.a;
        array.a = value;
    } else if (array.b != 0) {
        array.c = array.b;
        array.b = array.a;
        array.a = value;
    } else if (array.a != 0) {
        array.b = array.a;
        array.a = value;
    } else {
        array.a = value;
    }
    return array;
}

char getElement(unsigned short num) {
    return (num == 0) ? ' ' : char(num);
}

void prints(ARRAY array) {
    char t1 = getElement(array.a);
    char t2 = getElement(array.b);
    char t3 = getElement(array.c);
    cout << t1 << ' ' << t2 << ' ' << t3 << endl;
}

int main() {
    ARRAY array = {0, 0, 0};

    cout << "inicial: ";
    prints(array);

    array = addLast(array, 'A');
    array = addLast(array, 'B');
    array = addLast(array, 'C');
    cout << "agregar A, B, C al final: ";
    prints(array);

    array = addFirst(array, 'X');
    cout << "agregar X al inicio: ";
    prints(array);

    array = removeLast(array);
    cout << "remover el ultimo elemento: ";
    prints(array);

    return 0;
}
