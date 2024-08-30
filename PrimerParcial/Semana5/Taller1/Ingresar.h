#include <iostream>
#include "Nodo.cpp"
using namespace std;

class Ingresar
{
    private:
        Nodo* primero;
        Nodo* ultimo;
    public:
        Ingresar();
        ~Ingresar();
        void setPrimero(Nodo*);
        Nodo* getPrimero();
        void setUltimo(Nodo*);
        Nodo* getUltimo();
        void ingresarInicio(string);
        string crearCorreo(string);
        string nombre(string,string,string);
        string validar(const char*);
        void guardarDatos(string,string,string);
        string anadirNumero(string,string,int);
        string transformarMinusculas(string);
        void mostrarContenido(const string&);
};