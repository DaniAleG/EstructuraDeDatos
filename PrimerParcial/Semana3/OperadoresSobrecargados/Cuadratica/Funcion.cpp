/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados Funcion Cuadratica
    Autor: César González
    Fecha de Creación: 19/05/2024       Fecha de Modificación: 19/05/2024
    */
#include <iostream>
#include <conio.h>
#include <string>
#include "Funcion.h"
using namespace std;

std::string ingresar(const char* msj) {
    std::string dato;
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (c == 13) {  
            if (!dato.empty()) {  
                break;
            }
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                printf("\b \b"); 
            }
        } else if (c >= '0' && c <= '9' || c == '.' || c == '-') {
            dato += c;
            printf("%c", c);
        }
    }
    printf("\n");
    return dato;
}
void Funcion :: in(){
    a = stod(ingresar("Ingrese el valor de a: "));
    b = stod(ingresar("Ingrese el valor de b: "));
    c = stod(ingresar("Ingrese el valor de c: "));
}
//Sobrecarga de operador
double Funcion :: operator()(double x) const{

    return ((a * x * x) + (b * x) + c);
}
void Funcion :: out(){
    std :: cout << "La funcion es: " << a << "x^2 + " << b << "x + " <<  c << std :: endl;
}
