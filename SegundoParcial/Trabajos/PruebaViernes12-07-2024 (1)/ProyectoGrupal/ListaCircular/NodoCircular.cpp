#include "NodoCircular.h"

template <typename T>
NodoCircular<T>::NodoCircular(T numCedula, T primerNombre, T apellido) {
    this->numCedula = numCedula;
    this->primerNombre = primerNombre;
    this->apellido = apellido;
    this->siguiente = nullptr;
}

template <typename T>
void NodoCircular<T>::setNumCedula(T numCedula) {
    this->numCedula = numCedula;
}

template <typename T>
void NodoCircular<T>::setPrimerNombre(T primerNombre) {
    this->primerNombre = primerNombre;
}

template <typename T>
void NodoCircular<T>::setApellido(T apellido) {
    this->apellido = apellido;
}

template <typename T>
void NodoCircular<T>::setSiguiente(NodoCircular* siguiente) {
    this->siguiente = siguiente;
}

template <typename T>
T NodoCircular<T>::getNumCedula() {
    return numCedula;
}

template <typename T>
T NodoCircular<T>::getPrimerNombre() {
    return primerNombre;
}

template <typename T>
T NodoCircular<T>::getApellido() {
    return apellido;
}

template <typename T>
NodoCircular<T>* NodoCircular<T>::getSiguiente() {
    return siguiente;
}
