#ifndef NODOSIMPLE_H
#define NODOSIMPLE_H

template <typename T>
class NodoSimple {
private:
    T numCedula;
    T primerNombre;
    T apellido;
    NodoSimple* siguiente;

public:
    NodoSimple(T, T, T);
    void setNumCedula(T);
    void setPrimerNombre(T);
    void setApellido(T);
    void setSiguiente(NodoSimple*);
    T getNumCedula() const;
    T getPrimerNombre() const;
    T getApellido() const;
    NodoSimple* getSiguiente() const;
};

#include "NodoSimple.cpp"
#endif // NODOSIMPLE_H
