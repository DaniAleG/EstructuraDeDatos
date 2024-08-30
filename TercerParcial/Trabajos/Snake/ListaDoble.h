#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.h"

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble();
    ~ListaDoble();
    void insertarAlFinal(int x, int y);
    void eliminarAlInicio();
    Nodo* obtenerCabeza();
    Nodo* obtenerCola();
};

#endif
