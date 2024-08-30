#ifndef SUDOKU_H
#define SUDOKU_H

#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <functional>

class Sudoku {
public:
    Sudoku();
    void dibujarTablero(int inicioX, int inicioY);
    void dibujarBotones(int inicioX, int inicioY);
    void manejarEntrada(int inicioX, int inicioY, int inicioBotonX, int inicioBotonY);
    void generarSudoku();
    void eliminarNumeros();
    static const int tamanoTablero = 9;
    static const int tamanoCelda = 50;
    static const int tamanoBoton = 40;
    static const int celdasVacias = 40;
private:


    int tablero[tamanoTablero][tamanoTablero];
    bool celdasIniciales[tamanoTablero][tamanoTablero];

    bool esSeguro(int fila, int columna, int num);
    bool resolverSudoku(int fila, int columna);
    bool estaDentroDelRectangulo(int x, int y, int rectX, int rectY, int ancho, int alto);
};

#endif // SUDOKU_H