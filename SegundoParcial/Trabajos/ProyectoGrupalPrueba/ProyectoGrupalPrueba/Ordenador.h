#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <string>
#include <vector>

template <typename Nodo>
class Ordenador {
public:
    /* Métodos de ordenamiento por intercambio */
    template <typename Compare>
    static void ordenarPorSeleccion(Nodo*& cabeza, Compare comp);

    template <typename Compare>
    static void ordenarPorSeleccionCircular(Nodo*& cabeza, Compare comp);

    static void ordenarCaracteresEnAtributo(Nodo*& cabeza, const std::string& atributo);
    static void ordenarCaracteresEnAtributoCircular(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteres(std::string str);
    static void guardarCaracteresEnArchivo(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresEnArchivoCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    /* Métodos de ordenamiento por burbuja*/
    template <typename Compare>
    static void burbuja(Nodo*& cabeza, Compare comp);

    template <typename Compare>
    static void burbujaCircular(Nodo*& cabeza, Compare comp);

    static void ordenarCaracteresEnAtributoBurbuja(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresBurbuja(std::string str);
    static void ordenarCaracteresBurbujaCircular(Nodo*& cabeza, const std::string& atributo);
    static void guardarCaracteresBurbuja(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresBurbujaCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    /* Métodos de ordenamiento Quicksort */
    template <typename Compare>
    static void quickSort(Nodo*& cabeza, Compare comp);

    template <typename Compare>
    static void quickSortCircular(Nodo*& cabeza, Compare comp);

    template <typename Compare>
    static Nodo* particionar(Nodo* inicio, Nodo* fin, Compare comp);

    template <typename Compare>
    static void quickSortRec(Nodo* inicio, Nodo* fin, Compare comp);

    template <typename Compare>
    static void quickSortRecCircular(Nodo* inicio, Nodo* fin, Nodo* cabeza, Compare comp);
    
    static void ordenarCaracteresEnAtributoQuickSort(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresQuickSort(std::string str);
    static void ordenarCaracteresQuickSortCircular(Nodo*& cabeza, const std::string& atributo);
    static void ordenarCaracteresEnAtributoQuickSortCircular(Nodo*& cabeza, const std::string& atributo);
    static void guardarCaracteresQuickSort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresQuickSortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);

    /* Métodos de ordenamiento Shell Sort */
    template <typename Compare>
    static void shellSort(Nodo*& cabeza, Compare comp);

    template <typename Compare>
    static void shellSortCircular(Nodo*& cabeza, Compare comp);

    static void ordenarCaracteresEnAtributoShellSort(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresShellSort(std::string str);
    static void ordenarCaracteresShellSortCircular(Nodo*& cabeza, const std::string& atributo);
    static void guardarCaracteresShellsort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresShellsortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    /* Métodos de ordenamiento por Distribucion*/
    template <typename GetKey>
    static void distribucion(Nodo*& cabeza, GetKey getKey);

    template <typename GetKey>
    static void distribucionCircular(Nodo*& cabeza, GetKey getKey);
    
    static void ordenarCaracteresEnAtributoDistribucion(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresDistribucion(std::string str);
    static void ordenarCaracteresEnAtributoDistribucionCircular(Nodo*& cabeza, const std::string& atributo);
    static void guardarCaracteresDistribucion(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresDistribucionCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    /* Métodos de ordenamiento Radix */
    template <typename GetKey>
    static void radixSort(Nodo*& cabeza, GetKey getKey);

    template <typename GetKey>
    static void radixSortCircular(Nodo*& cabeza, GetKey getKey);
    
    static void ordenarCaracteresEnAtributoRadix(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresRadixSort(std::string str);
    static void ordenarCaracteresEnAtributoRadixCircular(Nodo*& cabeza, const std::string& atributo);
    static void guardarCaracteresRadixSort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresRadixSortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
private:
    static void intercambiarDatos(Nodo* a, Nodo* b);
};

#include "Ordenador.cpp"
#endif // ORDENADOR_H
