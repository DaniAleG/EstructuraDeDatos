#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.cpp"
#include <string>

class Arbol {
public:
    Arbol();
    ~Arbol();

    Nodo* construirArbol(const std::string* tokens, int numeroTokens);
    double evaluarArbol(Nodo* raiz);
    int calcularAltura(Nodo* raiz);
    void dibujarArbol(Nodo* raiz, int x, int y, int nivel, int desplazamiento);
    void configurarGraficos();
    void dibujarArbolRPN(const std::string& expresion);

private:
    void destruirArbol(Nodo* nodo);
};

#endif // ARBOL_H
