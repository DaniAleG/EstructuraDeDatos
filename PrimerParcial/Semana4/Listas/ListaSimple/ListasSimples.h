#include "Nodo.cpp"
using namespace std;
class ListaSimples {
    private:
        Nodo* cabeza;
    public:
        ListaSimples();
        void insertar(Nodo*&,int);
        void buscar(Nodo*&,int);
        void eliminar(Nodo*&,int);
        void mostrar(Nodo*);
};