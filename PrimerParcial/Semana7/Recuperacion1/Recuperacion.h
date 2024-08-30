#include "Nodo.cpp"
#include <functional>
using namespace std;
class ListaSimple{
    private:
        Nodo* cabeza;
        
    public:
        ListaSimple();
        int sumarDigitosLista(int);
        void insertar(Nodo*&,int);
        void imprimir(Nodo*);

};