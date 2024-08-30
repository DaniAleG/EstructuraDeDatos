#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "NodoSimple.h"
#include "..\Ordenador.h"
#include <string>

template <typename T>
class ListaSimple {
private:
    NodoSimple<T>* primero;

public:
    ListaSimple();
    ~ListaSimple();
    void insertar(T, T, T);
    void buscar(T);
    void eliminar(T);
    void mostrar();
    bool cedulaRepetida(T);
    void guardarEnArchivo();
    void cargarDesdeArchivo();
    bool validarCedula(long int);
    T ingresarCedula(const std::string &);
    T ingresarOpcion(const std::string &, int, int);
    bool esNumeroCedulaValido(const T &);
    bool listaVacia();
    T ingresarNumeros(const std::string &);
    T ingresarLetras(const std::string &, bool opcional = false);
    T convertirMayusculas(T);
    
    NodoSimple<T>* getPrimero();
    
    void ordenarCaracteresEnAtributo(const std::string& atributo);
    void guardarCaracteresOrdenadosEnArchivo(const std::string& atributo);
    void mostrarCaracteresOrdenados();
    template <typename Compare>
    void ordenarConRadix(Compare comp);
    void ordenarCaracteresRadix(const std::string& atributo);
    void resetLista();
};

#include "ListaSimple.cpp"
#endif // LISTASIMPLE_H
