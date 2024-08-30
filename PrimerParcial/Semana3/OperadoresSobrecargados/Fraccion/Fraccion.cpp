/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Operadores sobrecargados
    Autor: César González
    Fecha de Creación: 17/05/2024       Fecha de Modificación: 17/05/2024
    */
#include <iostream>
#include <conio.h>
#include <string>
#include "Fraccion.h"
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
        } else if (c >= '0' && c <= '9') {
            dato += c;
            printf("%c", c);
        }
    }
    printf("\n");
    return dato;
}
void Fraccion :: in(){
    a = stoi(ingresar("Ingrese el numerador: "));
    b = stoi(ingresar("Ingrese el denominador: "));
}
//Sobrecarga de operador
Fraccion Fraccion :: operator*(const Fraccion &objeto){
    Fraccion temporal;
    temporal.a = a * objeto.a;
    temporal.b = b * objeto.b;
    return temporal;
}
void Fraccion :: out(){
    cout << "La multiplicacion de la fraccion es: " << a << "/" << b << endl;
}


