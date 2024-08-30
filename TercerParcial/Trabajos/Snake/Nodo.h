#ifndef NODO_H
#define NODO_H

struct Nodo {
    int x, y;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int _x, int _y) : x(_x), y(_y), siguiente(nullptr), anterior(nullptr) {}
};

#endif
