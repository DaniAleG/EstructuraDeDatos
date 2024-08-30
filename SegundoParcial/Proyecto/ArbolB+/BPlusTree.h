#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include "Node.cpp"
#include <queue>
#include <vector>

class ArbolBPlus {
private:
    Nodo* raiz;
    int grado;

    void dividirHijo(Nodo* padre, int indice, Nodo* hijo);
    void insertarNoLleno(Nodo* nodo, int clave);
    void eliminarDeNodo(Nodo* nodo, int clave);
    int obtenerPredecesor(Nodo* nodo);
    int obtenerSucesor(Nodo* nodo);
    void fusionarNodos(Nodo* padre, int idx);
    void prestarDelAnterior(Nodo* padre, int idx);
    void prestarDelSiguiente(Nodo* padre, int idx);
    void inOrden(Nodo* nodo);
    void preOrden(Nodo* nodo);
    void postOrden(Nodo* nodo);

public:
    ArbolBPlus(int grado);
    void insertar(int clave);
    void eliminar(int clave);
    bool buscar(int clave) const;  
    void mostrar();
    Nodo* obtenerRaiz() const; 
    void recorridoInOrden();
    void recorridoPreOrden();
    void recorridoPostOrden();
};

#endif  // ARBOLBPLUS_H
