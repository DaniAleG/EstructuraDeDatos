/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Clase calculos que devuelve los datos en float
    Autor: César González
    Fecha de Creación: 08/05/2024       Fecha de Modificación: 09/05/2024
    */
#include "Proceso.h"
#include <iostream>
using namespace std;
Racional fraccion1, fraccion2;
float resultado;
class Calculos : public Proceso{
    public:
    int calcular1(int num, int den){
        return num/den;
    }
    Racional calcular2(int num, int den)  {
        resultado = ((float)num/(float)den);
        return resultado;
    }
    float calcular3(int num, int den) override{
        return (float)num/(float)den;
    }
    float calcular4(float num, float den){
        return (float)num/(float)den;
    }
    float sumar(float fraccion1, float fraccion2){
        return fraccion1 + fraccion2;
    }
    void imprimir(float suma){
        std:: cout << "El resultado es: " << suma << std ::endl; 
    }

};