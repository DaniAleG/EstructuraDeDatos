#include "Nodo.cpp"
using namespace std;
class MayorMenor{
    private:
        Nodo* cabeza;
    public:
        MayorMenor();
        void insertar(Nodo*&,int);
        void mayor(Nodo*);
        void menor(Nodo*);
        void imprimir(Nodo*);
        void liberar(Nodo*);
};