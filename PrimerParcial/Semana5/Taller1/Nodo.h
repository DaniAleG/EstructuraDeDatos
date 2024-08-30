#include <iostream>
#include <string>
using namespace std;

class Nodo{
    private:
        string dato;
        Nodo* siguiente;
        Nodo* anterior;
    public:
        Nodo();
        void setDato(string);
        string getDato();
        void setSiguiente(Nodo*);
        Nodo* getSiguiente();
        void setAnterior(Nodo*);
        Nodo* getAnterior();
};
