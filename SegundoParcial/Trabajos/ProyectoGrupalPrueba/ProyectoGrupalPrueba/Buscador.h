#ifndef BUSCADOR_H
#define BUSCADOR_H

#include "../ProyectoGrupalPrueba(2)/ListaSimple/NodoSimple.h"
#include "../ProyectoGrupalPrueba(2)/ListaDoble/NodoDoble.h"
#include "../ProyectoGrupalPrueba(2)/ListaCircular/NodoCircular.h"
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