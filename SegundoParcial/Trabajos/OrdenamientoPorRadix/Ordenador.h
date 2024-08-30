#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <string>

template <typename Nodo>
class Ordenador {
public:
    
    static void guardarCaracteresEnArchivo(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    static void guardarCaracteresEnArchivoCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo);
    template <typename GetKey>
    static void radixSort(Nodo*& cabeza, GetKey getKey);
    static void countingSort(Nodo*& cabeza, int exp);
    static void ordenarCaracteresEnAtributoRadix(Nodo*& cabeza, const std::string& atributo);
    static std::string ordenarCaracteresRadixSort(std::string str);
    static void ordenarCaracteresEnAtributoRadixCircular(Nodo*& cabeza, const std::string& atributo);
    template <typename GetKey>
    static void radixSortCircular(Nodo*& cabeza, GetKey getKey);
private:
    static void intercambiarDatos(Nodo* a, Nodo* b);
};

#include "Ordenador.cpp"
#endif // ORDENADOR_H
