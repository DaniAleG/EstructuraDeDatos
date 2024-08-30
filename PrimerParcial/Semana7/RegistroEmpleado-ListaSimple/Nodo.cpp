#include <iostream>
#include "Nodo.h"
using namespace std;

Nodo::Nodo() {
    this->dato = "";
    this->siguiente = nullptr;
}
void Nodo::setDato(const string& dato) {
    this->dato = dato;
}

string Nodo::getDato() {
    return this->dato;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}

Nodo* Nodo::getSiguiente() {
    return this->siguiente;
}
