/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados
    Autor: César González
    Fecha de Creación: 17/05/2024       Fecha de Modificación: 17/05/2024
    */
#include <iostream>
#include "Fraccion.cpp"
using namespace std;


int main(){
    Fraccion fraccionsita1, fraccionsita2, resultado; 
    cout << "Ingresar la primera fraccion: " << endl;
    fraccionsita1.in();
    cout << "Ingresar la segunda fraccion: " << endl;
    fraccionsita2.in();
    resultado = fraccionsita1 * fraccionsita2;
    resultado.out();
    return 0;
}