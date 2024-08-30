/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados Funcion Cuadratica
    Autor: César González
    Fecha de Creación: 19/05/2024       Fecha de Modificación: 19/05/2024
    */
#include <iostream>
#include "Funcion.cpp"
using namespace std;

int main(){
    Funcion funcionsita;
    double x;   
    x = stod(ingresar("Ingrese el valor de x: "));
    funcionsita.in();
    funcionsita.out();
    std :: cout << "El resultado de la funcion evaluada en " << x << " es: " << funcionsita(x);
    return 0;
}