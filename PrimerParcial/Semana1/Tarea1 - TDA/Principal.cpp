/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Clase main para enviar datos y recibirlos
    Autor: César González
    Fecha de Creación: 08/05/2024       Fecha de Modificación: 09/05/2024
    */

#include <iostream>
using namespace std;
#include "Racional.cpp"
#include "Proceso.h"
#include "Racional.h"
#include "Calculos.cpp"
int main(){
    //Declaracion de Variables y objetos de tipo Racional, int , float, Calculos
    Racional fraccion1, fraccion2, res1, res2;
    int num1, num2 , den1, den2;
    float respuesta1, respuesta2, suma;
    Calculos calculadora;
    //Ingreso de datos
    std :: cout << "Ingrese el numerador 1: ";
    std :: cin >> num1 ;
    fraccion1.setNumerador(num1);
    std :: cout << "Ingrese el denominador 1: ";
    std :: cin >> den1 ;
    //Validación denominador igual a cero
    while(den1 == 0){
        std :: cout << "El denominador no puede ser 0, ingrese el denominador 1 de nuevo: ";
        std :: cin >> den1 ;
    };
    fraccion1.setDenominador(den1);
    std :: cout << "Ingrese el numerador 2: ";
    std :: cin >> num2 ;
    fraccion2.setNumerador(num2);
    std :: cout << "Ingrese el denominador 2: ";
    std :: cin >> den2 ;
    //Validación denominador igual a cero
    while(den2 == 0){
        std :: cout << "El denominador no puede ser 0, ingrese el denominador 2 de nuevo: ";
        std :: cin >> den2 ;
    };
    //Envio de datos a la clase Calculos
    fraccion2.setDenominador(den2);
    respuesta1 = calculadora.calcular1(fraccion1.getNumerador(), fraccion1.getDenominador());
    respuesta2 = calculadora.calcular1(fraccion2.getNumerador(), fraccion2.getDenominador());
    suma = calculadora.sumar(respuesta1,respuesta2);
    calculadora.imprimir(suma);
    res1 = calculadora.calcular1(fraccion1.getNumerador(), fraccion1.getDenominador());
    res2 = calculadora.calcular1(fraccion2.getNumerador(), fraccion2.getDenominador());
    suma = calculadora.sumar(res1.toFloat(),res2.toFloat());
    calculadora.imprimir(suma);
    respuesta1 = calculadora.calcular1((float)fraccion1.getNumerador(), (float)fraccion1.getDenominador());
    respuesta2 = calculadora.calcular1((float)fraccion2.getNumerador(), (float)fraccion2.getDenominador());
    suma = calculadora.sumar(respuesta1,respuesta2);
    calculadora.imprimir(suma);
    respuesta1 = calculadora.calcular1((float)fraccion1.getNumerador(), (float)fraccion1.getDenominador());
    respuesta2 = calculadora.calcular1((float)fraccion2.getNumerador(), (float)fraccion2.getDenominador());
    suma = calculadora.sumar(respuesta1,respuesta2);
    calculadora.imprimir(suma);
    return 0;
}