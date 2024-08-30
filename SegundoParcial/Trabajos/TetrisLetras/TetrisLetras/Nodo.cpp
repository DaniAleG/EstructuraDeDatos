#include "Nodo.h"

template <typename T>
Nodo<T>::Nodo(const T& valor) : valor(valor), siguiente(nullptr) {}

template <typename T>
T Nodo<T>::getValor() const {
    return valor;
}

template <typename T>
void Nodo<T>::setValor(const T& valor) {
    this->valor = valor;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() const {
    return siguiente;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* siguiente) {
    this->siguiente = siguiente;
}
