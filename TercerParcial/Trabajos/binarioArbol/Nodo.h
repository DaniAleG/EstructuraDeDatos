#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    std::string valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(const std::string& val);
};

#endif // NODO_H


