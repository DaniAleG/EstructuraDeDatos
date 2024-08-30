#ifndef ELIMINARCARACTER_H
#define ELIMINARCARACTER_H

#include <string>
#include <algorithm> 
#include <iostream>  

template<typename Nodo>
class EliminarCaracter {
public:
    std::string eliminarCaracterCadenaLambda(const std::string& str, char c);
    void eliminarCaracterListaRecursiva(Nodo *actual, char caracter, const std::string &atributo);
    void eliminarCaracterListaCircular(Nodo *cabeza, char caracter, const std::string &atributo);
};

#include "EliminarCaracter.cpp"

#endif // ELIMINARCARACTER_H
