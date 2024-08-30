#ifndef CUADROMAGICO_H
#define CUADROMAGICO_H

#include <graphics.h>
#include <iostream>
#include <functional>

const int N = 3;  // Tamaño del cuadrado mágico
const int CELL_SIZE = 100;  // Tamaño de cada celda
const int OFFSET_X = 600;  // Desplazamiento en X para dibujar el cuadrado
const int OFFSET_Y = 200;  // Desplazamiento en Y para dibujar el cuadrado
const int NUMERO_Y = OFFSET_Y + N * CELL_SIZE + 50;  // Y para la fila de números debajo del cuadrado

void dibujarCuadradoVacio();
void dibujarNumero(int num, int fila, int columna, bool esFilaNumeros = false);
int obtenerFila(int y);
int obtenerColumna(int x);
bool estaDentroDelCuadrado(int x, int y);
bool estaEnFilaNumeros(int x, int y);
bool esCuadradoMagico(int cuadrado[N][N]);

#endif // CUADROMAGICO_H