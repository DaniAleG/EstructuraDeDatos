#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;

public:
    Nodo(const T& valor);
    T getValor() const;
    void setValor(const T& valor);
    Nodo<T>* getSiguiente() const;
    void setSiguiente(Nodo<T>* siguiente);
};



#endif
