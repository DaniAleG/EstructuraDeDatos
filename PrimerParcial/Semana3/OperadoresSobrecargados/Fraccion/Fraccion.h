/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados
    Autor: César González
    Fecha de Creación: 17/05/2024       Fecha de Modificación: 17/05/2024
    */
#include <iostream>
using namespace std;
class Fraccion{
    private:
    int a;
    int b;
    public:
        Fraccion() : a(0), b(0){}
        void in();
        Fraccion operator*(const Fraccion &objeto);
        void out();
};