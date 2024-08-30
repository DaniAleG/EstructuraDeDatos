/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Calcular raiz cuadrada sin utilizar sqrt
    Autor: César González
    Fecha de Creación: 06/05/2024       Fecha de Modificación: 06/05/2024
    */

#include <iostream>
//Funcion que se encarga de hacer el calculo de la raiz cuadrada
float raizCuadrada(float numero, float tolerancia = 0.0001){
    //Estimacion inicial
    float estimacion = numero / 2;
    while(true){
        //Formula de Newton Raphson para calcular estimaciones
        float nuevaEstimacion = 0.5 * (estimacion + numero / estimacion);
        //Comprobar la estimación más cercana
        if(std::abs(estimacion - nuevaEstimacion) < tolerancia)
            break;
        //Guardar la nueva estimacion para la siguiente iteración
        estimacion = nuevaEstimacion;
    }
    return estimacion;
}


int main() {
    //Declaración variable e ingreso de numero a calcular
    float numero;
    std::cout << "Ingrese un numero para calcular su raiz cuadrada: ";
    std::cin >> numero;
    //Validación de numeros negativos
    while(numero < 0){
        std::cout << "No existen raices cuadradas negativas, ingrese nuevamente: ";
        std::cin >> numero;
    }
    //Llamada de funcion para el cálculo e impresion del resultado
        float resultado = raizCuadrada(numero);
        std::cout << "La raiz cuadrada de " << numero << " es aproximadamente: " << resultado << std::endl;
    return 0;
}