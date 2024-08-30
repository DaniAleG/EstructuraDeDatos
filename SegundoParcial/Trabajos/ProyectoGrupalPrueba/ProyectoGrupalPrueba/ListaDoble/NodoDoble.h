#ifndef NODODOBLE_H
#define NODODOBLE_H

template <typename T>
class NodoDoble {
private:
    T numCedula;
    T primerNombre;
    T apellido;
    NodoDoble* siguiente;
    NodoDoble* anterior;

public:
    NodoDoble(T, T, T);
    void setNumCedula(T);
    void setPrimerNombre(T);
    void setApellido(T);
    void setSiguiente(NodoDoble*);
    void setAnterior(NodoDoble*);
    T getNumCedula();
    T getPrimerNombre();
    T getApellido();
    NodoDoble* getSiguiente();
    NodoDoble* getAnterior();
};

#include "NodoDoble.cpp"
#endif // NODODOBLE_H
