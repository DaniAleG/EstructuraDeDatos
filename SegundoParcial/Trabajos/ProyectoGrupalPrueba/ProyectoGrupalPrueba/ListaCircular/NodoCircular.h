#ifndef NODOCIRCULAR_H
#define NODOCIRCULAR_H

template <typename T>
class NodoCircular {
private:
    T numCedula;
    T primerNombre;
    T apellido;
    NodoCircular* siguiente;

public:
    NodoCircular(T, T, T);
    void setNumCedula(T);
    void setPrimerNombre(T);
    void setApellido(T);
    void setSiguiente(NodoCircular*);
    T getNumCedula();
    T getPrimerNombre();
    T getApellido();
    NodoCircular* getSiguiente();
};

#include "NodoCircular.cpp"
#endif // NODOCIRCULAR_H
