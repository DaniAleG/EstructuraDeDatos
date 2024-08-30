#ifndef CUADROLATINO_H
#define CUADROLATINO_H

#include <graphics.h>
#include <iostream>
#include <limits>
#include <cstring>
#include <functional>

class CuadroLatino {
public:
    CuadroLatino();
    ~CuadroLatino();
    void iniciar();
    void dibujarCuadroLatino(int size);
    void dibujarTextoCelda(int row, int col, int num);
    void limpiarPantalla();
    void dibujarCeldasRecursivamente(int row, int col);
    bool verificarCuadroLatino();
    int validarNumeros(const char* msj);

private:
    int n; // Tamaño del cuadrado latino
    int size; // Tamaño de la ventana
    int** square; // Matriz del cuadrado latino
};

#endif // CUADROLATINO_H