#include <iostream>
#include "Nodo.h"
using namespace std;

Nodo :: Nodo(){
    this->dato = dato;
    this->siguiente = NULL;
    this->anterior = NULL;
}
void Nodo :: setDato(string dato){
    this->dato = dato;
}
string Nodo ::getDato(){
    return this->dato;
}
void Nodo :: setSiguiente(Nodo* siguiente){
    this->siguiente = siguiente;
}
Nodo* Nodo ::getSiguiente(){
    return this->siguiente;
}
void Nodo :: setAnterior(Nodo* anterior){
    this->anterior = anterior;
}
Nodo* Nodo ::getAnterior(){
    return this->anterior;
}