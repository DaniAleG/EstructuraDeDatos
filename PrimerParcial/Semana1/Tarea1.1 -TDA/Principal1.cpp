/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Clase main para enviar datos y recibirlos
    Autor: César González
    Fecha de Creación: 09/05/2024       Fecha de Modificación: 09/05/2024
    */
#include <iostream>
using namespace std;
#include "Potencia.cpp"
#include "Potencia.h"
#include "Procesos.h"
#include "Calcular.cpp"

int main(){
    //Declaracion variables
    Potencia potencia, resp;
    Calcular calcular;
    float base, respuesta;
    int exponente;
    std :: cout << "Ingrese la base: ";
    std :: cin >> base;
    potencia.setBase(base);
    std :: cout << "Ingrese el exponente: ";
    std :: cin >> exponente;
    while(exponente < 0){
        std :: cout << "Exponente invalido, ingrese el exponente de nuevo: ";
        std :: cin >> exponente;
    }
    potencia.setExponente(exponente);
    respuesta = calcular.calcular1(potencia.getBase(),potencia.getExponente());
    calcular.imprimir(respuesta);
    respuesta = calcular.calcular2(potencia.getBase(),potencia.getExponente());
    calcular.imprimir(respuesta);
    resp = calcular.calcular3(potencia.getBase(),potencia.getExponente());
    respuesta = resp.toFloat();
    calcular.imprimir(respuesta);
    return 0;
}