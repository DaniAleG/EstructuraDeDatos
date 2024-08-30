#ifndef BUSCADOR_H
#define BUSCADOR_H

#include "../ProyectoGrupal/ListaSimple/NodoSimple.h"
#include "../ProyectoGrupal/ListaDoble/NodoDoble.h"
#include "../ProyectoGrupal/ListaCircular/NodoCircular.h"
#include <string>

template <typename Nodo>
class Buscador {
public:
    static void buscarSecuencial(Nodo* cabeza, const std::string& valor, const std::string& atributo);
    static void buscarBinario(Nodo* cabeza, const std::string& valor, const std::string& atributo);
    static void buscarTablasHash(Nodo* cabeza, const std::string& valor, const std::string& atributo);
};

#include "Buscador.cpp"
#endif // BUSCADOR_H