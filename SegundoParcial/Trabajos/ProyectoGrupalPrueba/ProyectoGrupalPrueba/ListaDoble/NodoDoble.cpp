#include "NodoDoble.h"

template <typename T>
NodoDoble<T>::NodoDoble(T numCedula, T primerNombre, T apellido) {
    this->numCedula = numCedula;
    this->primerNombre = primerNombre;
    this->apellido = apellido;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

template <typename T>
void NodoDoble<T>::setNumCedula(T numCedula) {
    this->numCedula = numCedula;
}

template <typename T>
void NodoDoble<T>::setPrimerNombre(T primerNombre) {
    this->primerNombre = primerNombre;
}

template <typename T>
void NodoDoble<T>::setApellido(T apellido) {
    this->apellido = apellido;
}

template <typename T>
void NodoDoble<T>::setSiguiente(NodoDoble* siguiente) {
    this->siguiente = siguiente;
}

template <typename T>
void NodoDoble<T>::setAnterior(NodoDoble* anterior) {
    this->anterior = anterior;
}

template <typename T>
T NodoDoble<T>::getNumCedula() {
    return numCedula;
}

template <typename T>
T NodoDoble<T>::getPrimerNombre() {
    return primerNombre;
}

template <typename T>
T NodoDoble<T>::getApellido() {
    return apellido;
}

template <typename T>
NodoDoble<T>* NodoDoble<T>::getSiguiente() {
    return siguiente;
}

template <typename T>
NodoDoble<T>* NodoDoble<T>::getAnterior() {
    return anterior;
}
