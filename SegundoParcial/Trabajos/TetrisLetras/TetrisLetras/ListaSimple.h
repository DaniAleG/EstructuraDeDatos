#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "Nodo.cpp"

template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

public:
    ListaSimple();
    ~ListaSimple();
    void agregar(const T& valor);
    void eliminar(const T& valor);
    void imprimir() const;
    bool contiene(const T& valor) const;
    Nodo<T>* getPrimero() const;
    T ingresarLetras(const char* msj);
};



#endif
