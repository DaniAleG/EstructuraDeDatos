#ifndef BUSCADOR_H
#define BUSCADOR_H

#include "../OrdenamientoPorRadix/ListaSimple_Seleccion/NodoSimple.h"
#include "../OrdenamientoPorRadix/ListaDoble_Seleccion/NodoDoble.h"
#include "../OrdenamientoPorRadix/ListaCircular_Seleccion/NodoCircular.h"
#include <string>

template <typename Nodo>
class Buscador {
public:
    static void buscarTablasHash(Nodo* cabeza, const std::string& valor, const std::string& atributo);
};

#include "Buscador.cpp"
#endif // BUSCADOR_H