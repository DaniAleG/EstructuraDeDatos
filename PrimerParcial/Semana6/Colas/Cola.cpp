#include "Cola.h"
#include <stdexcept>

template <typename T>
Cola<T>::Cola() : frente(nullptr), fondo(nullptr) {}

template <typename T>
Cola<T>::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

template <typename T>
void Cola<T>::encolar(T valor) {
    Nodo* nuevoNodo = new Nodo(valor);
    if (estaVacia()) {
        frente = fondo = nuevoNodo;
    } else {
        fondo->siguiente = nuevoNodo;
        fondo = nuevoNodo;
    }
}

template <typename T>
void Cola<T>::desencolar() {
    if (estaVacia()) {
        throw std::underflow_error("La cola está vacía");
    }
    Nodo* temp = frente;
    frente = frente->siguiente;
    delete temp;
    if (!frente) {
        fondo = nullptr;
    }
}

template <typename T>
T Cola<T>::obtenerFrente() const {
    if (estaVacia()) {
        throw std::underflow_error("La cola está vacía");
    }
    return frente->dato;
}

template <typename T>
bool Cola<T>::estaVacia() const {
    return frente == nullptr;
}
