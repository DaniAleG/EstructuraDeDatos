#include "NodoSimple.h"

template <typename T>
NodoSimple<T>::NodoSimple(T numCedula, T primerNombre, T apellido) {
    this->numCedula = numCedula;
    this->primerNombre = primerNombre;
    this->apellido = apellido;
    this->siguiente = nullptr;
}

template <typename T>
void NodoSimple<T>::setNumCedula(T numCedula) {
    this->numCedula = numCedula;
}

template <typename T>
void NodoSimple<T>::setPrimerNombre(T primerNombre) {
    this->primerNombre = primerNombre;
}

template <typename T>
void NodoSimple<T>::setApellido(T apellido) {
    this->apellido = apellido;
}

template <typename T>
void NodoSimple<T>::setSiguiente(NodoSimple* siguiente) {
    this->siguiente = siguiente;
}

template <typename T>
T NodoSimple<T>::getNumCedula() const {
    return numCedula;
}

template <typename T>
T NodoSimple<T>::getPrimerNombre() const {
    return primerNombre;
}

template <typename T>
T NodoSimple<T>::getApellido() const {
    return apellido;
}

template <typename T>
NodoSimple<T>* NodoSimple<T>::getSiguiente() const {
    return siguiente;
}
