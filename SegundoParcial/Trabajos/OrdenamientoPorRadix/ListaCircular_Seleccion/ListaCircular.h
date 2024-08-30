#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "NodoCircular.h"
#include "..\Ordenador.h"
#include <string>

template <typename T>
class ListaCircular {
private:
    NodoCircular<T>* primero;
    NodoCircular<T>* ultimo;

public:
    ListaCircular();
    ~ListaCircular();
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
    T ingresarLetras(const std::string &);
    T convertirMayusculas(T);
    NodoCircular<T>* getPrimero();


    void ordenarCaracteresEnAtributo(const std::string& atributo);
    void guardarCaracteresOrdenadosEnArchivo(const std::string& atributo);
    void mostrarCaracteresOrdenados();
    void ordenarCaracteresShellSort(const std::string& atributo);
    template <typename Compare>
    void ordenarConRadix(Compare comp);
    void ordenarCaracteresRadix(const std::string& atributo);
    void resetLista();
};

#include "ListaCircular.cpp"
#endif // LISTACIRCULAR_H
