#pragma once
#ifndef NODO_H
#define NODO_H
#include <string>
class Nodo {
    private:
        std::string dato;
        Nodo* siguiente;

    public:
        Nodo();
        std::string getDato();
        void setDato(const std::string& dato);
        Nodo* getSiguiente();
        void setSiguiente(Nodo* siguiente);
};

#endif // NODO_H


