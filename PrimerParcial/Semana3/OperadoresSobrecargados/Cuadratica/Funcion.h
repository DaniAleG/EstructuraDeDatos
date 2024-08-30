/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados Funcion Cuadratica
    Autor: César González
    Fecha de Creación: 19/05/2024       Fecha de Modificación: 19/05/2024
    */
#include <iostream>
using namespace std;
class Funcion{
    private:
    double a;
    double b;
    double c;
    double x;
    public:
        Funcion() : a(0), b(0), c(0), x(0){}
        void in();
        double operator()(double x)const;
        void out();
};