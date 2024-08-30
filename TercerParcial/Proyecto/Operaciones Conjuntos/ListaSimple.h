#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>

// Definición del struct Nodo
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;

    Nodo(const T& dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
};

// Definición del struct ListaSimple
template <typename T>
class ListaSimple {
    

public:
Nodo<T>* cabeza;
    ListaSimple() : cabeza(nullptr) {}
    ~ListaSimple();
    void insertar(const T& dato);
    void mostrar() const;
    Nodo<T>* buscar(const T& dato) const;
    bool contains(const T& elemento) const;
    ListaSimple<T> unionList(const ListaSimple<T>& otra) const;
    ListaSimple<T> interseccion(const ListaSimple<T>& otra) const;
    ListaSimple<T> diferencia(const ListaSimple<T>& otra, bool isDifferenceAB) const;
    ListaSimple<T> diferenciaSimetrica(const ListaSimple<T>& otra) const;
    ListaSimple<T> complemento(const ListaSimple<T>& otra, bool complementoAB) const;
};

#include "ListaSimple.cpp"

#endif // LISTASIMPLE_H