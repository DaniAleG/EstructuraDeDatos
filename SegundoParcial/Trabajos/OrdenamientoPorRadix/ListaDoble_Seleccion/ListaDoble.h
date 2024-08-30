#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoDoble.h"
#include "..\Ordenador.h"
#include <string>

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* primero;
    NodoDoble<T>* ultimo;

public:
    ListaDoble();
    ~ListaDoble();
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
    NodoDoble<T>* getPrimero();



    void ordenarCaracteresEnAtributo(const std::string& atributo);
    void guardarCaracteresOrdenadosEnArchivo(const std::string& atributo);
    void mostrarCaracteresOrdenados();
    void resetLista();
    template <typename Compare>
    void ordenarConRadix(Compare comp);
    void ordenarCaracteresRadix(const std::string& atributo);


};

#include "ListaDoble.cpp"
#endif // LISTADOBLE_H
