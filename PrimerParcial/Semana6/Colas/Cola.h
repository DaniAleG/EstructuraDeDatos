#ifndef COLA_H
#define COLA_H

template <typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* fondo;

public:
    Cola();
    ~Cola();
    void encolar(T valor);
    void desencolar();
    T obtenerFrente() const;
    bool estaVacia() const;
};

#include "Cola.cpp" // Incluir la implementación para plantillas

#endif // COLA_H

