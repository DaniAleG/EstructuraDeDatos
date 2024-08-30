#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoDoble.h"
#include "..\Ordenador.h"
#include <string>
#include "..\Interfaz.h"


template <typename T>
class ListaDoble :public Interfaz<NodoDoble<T>>{
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
    /* Métodos de ordenamiento por intercambio */
    template <typename Compare>
    void ordenar(Compare comp);

    void ordenarCaracteresEnAtributo(const std::string& atributo);
    void guardarCaracteresOrdenadosEnArchivo(const std::string& atributo);
    /* Métodos de ordenamiento por burbuja*/
    template <typename Compare>
    void ordenarConBurbuja(Compare comp);
    
    void ordenarCaracteresBurbuja(const std::string& atributo);
    void guardarCaracteresOrdenadosBurbuja(const std::string& atributo);
    /* Métodos de ordenamiento Quicksort */
    template <typename Compare>
    void ordenarConQuickSort(Compare comp);

    void ordenarCaracteresQuickSort(const std::string& atributo);
    void guardarCaracteresOrdenadosQuickSort(const std::string& atributo);
    /* Métodos de ordenamiento Shell Sort */
    template <typename Compare>
    void ordenarConShellSort(Compare comp);

    void ordenarCaracteresShellSort(const std::string& atributo);
    void guardarCaracteresOrdenadosShellsort(const std::string& atributo);
    /* Métodos de ordenamiento Radix */
    template <typename Compare>
    void ordenarConRadix(Compare comp);
    void ordenarCaracteresRadix(const std::string& atributo);
    void guardarCaracteresOrdenadosRadixSort(const std::string& atributo);


    void mostrarCaracteresOrdenados();
    
    void resetLista();

    void eliminarCaracter(NodoDoble<T>* lista, string caracter)override;

    T ingresarCaracter(const std::string&);
};

#include "ListaDoble.cpp"
#endif // LISTADOBLE_H
