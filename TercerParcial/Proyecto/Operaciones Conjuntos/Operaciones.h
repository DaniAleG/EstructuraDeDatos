#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "ListaSimple.h"
#include "Dibujar.h"
#include <string>

class Operaciones {
public:
    void gotoxyMain(int x, int y);
    void printMenuMain(const char* menu[], int size, int currentSelection);
    
    void operarConjuntosMenu(int opcion);

    template <typename T>
    void ingresarConjunto(ListaSimple<T>& conjunto);
    template <typename T>
    void mostrarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B);
    template <typename T>
    void mostrarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B);
    template <typename T>
    void mostrarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B);
    template <typename T>
    void mostrarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B);
    template <typename T>
    void mostrarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B);
};

#include "Operaciones.cpp"

#endif // OPERACIONES_H