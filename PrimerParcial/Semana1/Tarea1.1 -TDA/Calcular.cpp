/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Calcular potencias sin usar math
    Autor: César González
    Fecha de Creación: 0/05/2024       Fecha de Modificación: 09/05/2024
    */
#include "Procesos.h"
#include <iostream>
using namespace std;

class Calcular : public Procesos{
    public: 
    int calcular1(int base, int exponente){
        float potencia = 1;
        for (int i = 0; i < exponente; i++) {
        potencia *= base;
        }
        return potencia;
    }
    float calcular2(float base, int exponente){
        float potencia = 1;
        for (int j = 0; j < exponente; j++) {
            potencia *= base;
        }
        return potencia;  
    }
    Potencia calcular3(float base, int exponente){
        float potencia = 1;
        for (int k = 0; k < exponente; k++) {
            potencia *= base;
        }
        return potencia; 
    }
    void imprimir(float respuesta){
        std:: cout << "El resultado es: " << respuesta << std ::endl; 
    }

};