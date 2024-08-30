#ifndef DIBUJAR_H
#define DIBUJAR_H

#include "ListaSimple.h"
#include <graphics.h>
#include <string>

class Dibujar {
public:
    template <typename T>
    void dibujarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B);

    template <typename T>
    void dibujarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B);

    template <typename T>
    void dibujarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B);

    template <typename T>
    void dibujarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B);

    template <typename T>
    void dibujarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B);

private:
    template <typename T>
    void mostrarDatos(const ListaSimple<T>& lista, int x, int y);

    void mostrarDatos(const ListaSimple<std::string>& conjunto, int x, int y);
};

#include "Dibujar.cpp"

#endif // DIBUJAR_H