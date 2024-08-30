/*Universidad de las Fuerzas Armadas ESPE
            SUDOKU
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include <graphics.h>
#include "Sudoku.cpp"

int main() {
    int anchoPantalla = getmaxwidth();
    int altoPantalla = getmaxheight();

    initwindow(anchoPantalla, altoPantalla, "Sudoku", -3, -3);

    setbkcolor(WHITE);
    cleardevice();

    Sudoku sudoku;
    sudoku.generarSudoku();
    sudoku.eliminarNumeros();

    int inicioX = (anchoPantalla - Sudoku::tamanoTablero * Sudoku::tamanoCelda) / 2;
    int inicioY = (altoPantalla - Sudoku::tamanoTablero * Sudoku::tamanoCelda) / 3;

    int inicioBotonX = (anchoPantalla - 9 * Sudoku::tamanoBoton) / 2;
    int inicioBotonY = inicioY + Sudoku::tamanoTablero * Sudoku::tamanoCelda + 20;

    sudoku.dibujarTablero(inicioX, inicioY);
    sudoku.dibujarBotones(inicioBotonX, inicioBotonY);

    sudoku.manejarEntrada(inicioX, inicioY, inicioBotonX, inicioBotonY);

    getch();
    closegraph();
    return 0;
}