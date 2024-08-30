
#include "ListaDoble.h"

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    while (cabeza) {
        eliminarAlInicio();
    }
}

void ListaDoble::insertarAlFinal(int x, int y) {
    Nodo* nuevoNodo = new Nodo(x, y);
    if (!cola) {
        cabeza = cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}

void ListaDoble::eliminarAlInicio() {
    if (cabeza) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        if (cabeza) {
            cabeza->anterior = nullptr;
        } else {
            cola = nullptr;
        }
        delete temp;
    }
}

Nodo* ListaDoble::obtenerCabeza() {
    return cabeza;
}

Nodo* ListaDoble::obtenerCola() {
    return cola;
}
