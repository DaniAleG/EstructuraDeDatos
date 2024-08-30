#include "Sudoku.h"

Sudoku::Sudoku() {
    std::srand(std::time(0));
    for (int i = 0; i < tamanoTablero; ++i) {
        for (int j = 0; j < tamanoTablero; ++j) {
            tablero[i][j] = 0;
            celdasIniciales[i][j] = false;
        }
    }
}

void Sudoku::dibujarTablero(int inicioX, int inicioY) {
    int x, y;
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    setcolor(DARKGRAY);
    for (int i = 0; i <= tamanoTablero; ++i) {
        line(inicioX + i * tamanoCelda, inicioY, inicioX + i * tamanoCelda, inicioY + tamanoTablero * tamanoCelda);
        line(inicioX, inicioY + i * tamanoCelda, inicioX + tamanoTablero * tamanoCelda, inicioY + i * tamanoCelda);
    }

    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);

    for (int i = 0; i <= tamanoTablero; ++i) {
        if (i % 3 == 0) {
            line(inicioX + i * tamanoCelda, inicioY, inicioX + i * tamanoCelda, inicioY + tamanoTablero * tamanoCelda);
        }
    }
    
    for (int i = 0; i <= tamanoTablero; ++i) {
        if (i % 3 == 0) {
            line(inicioX, inicioY + i * tamanoCelda, inicioX + tamanoTablero * tamanoCelda, inicioY + i * tamanoCelda);
        }
    }

    setlinestyle(SOLID_LINE, 0, 1);

    setcolor(BLACK);
    for (int i = 0; i < tamanoTablero; ++i) {
        for (int j = 0; j < tamanoTablero; ++j) {
            if (tablero[i][j] != 0) {
                x = inicioX + j * tamanoCelda + tamanoCelda / 2;
                y = inicioY + i * tamanoCelda + tamanoCelda / 2;
                char num[2];
                sprintf(num, "%d", tablero[i][j]);
                outtextxy(x, y, num);

                celdasIniciales[i][j] = true;
            }
        }
    }
}

void Sudoku::dibujarBotones(int inicioX, int inicioY) {
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    for (int i = 0; i < 9; i++) {
        int x = inicioX + i * tamanoBoton + tamanoBoton / 2;
        int y = inicioY + tamanoBoton / 2;
        char num[2];
        sprintf(num, "%d", i + 1);
        rectangle(inicioX + i * tamanoBoton, inicioY, inicioX + (i + 1) * tamanoBoton, inicioY + tamanoBoton);
        outtextxy(x, y, num);
    }
}

bool Sudoku::estaDentroDelRectangulo(int x, int y, int rectX, int rectY, int ancho, int alto) {
    return (x >= rectX && x <= rectX + ancho && y >= rectY && y <= rectY + alto);
}

void Sudoku::manejarEntrada(int inicioX, int inicioY, int inicioBotonX, int inicioBotonY) {
    int filaSeleccionada = -1, columnaSeleccionada = -1;
    int filaSeleccionadaAnterior = -1, columnaSeleccionadaAnterior = -1;

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if (estaDentroDelRectangulo(x, y, inicioX, inicioY, tamanoTablero * tamanoCelda, tamanoTablero * tamanoCelda)) {
                if (filaSeleccionadaAnterior != -1 && columnaSeleccionadaAnterior != -1) {
                    setcolor(DARKGRAY);
                    rectangle(inicioX + columnaSeleccionadaAnterior * tamanoCelda, inicioY + filaSeleccionadaAnterior * tamanoCelda, 
                              inicioX + (columnaSeleccionadaAnterior + 1) * tamanoCelda, inicioY + (filaSeleccionadaAnterior + 1) * tamanoCelda);
                }

                columnaSeleccionada = (x - inicioX) / tamanoCelda;
                filaSeleccionada = (y - inicioY) / tamanoCelda;

                if (!celdasIniciales[filaSeleccionada][columnaSeleccionada]) {
                    setcolor(RED);
                    rectangle(inicioX + columnaSeleccionada * tamanoCelda, inicioY + filaSeleccionada * tamanoCelda, 
                              inicioX + (columnaSeleccionada + 1) * tamanoCelda, inicioY + (filaSeleccionada + 1) * tamanoCelda);
                    setcolor(BLACK);

                    filaSeleccionadaAnterior = filaSeleccionada;
                    columnaSeleccionadaAnterior = columnaSeleccionada;
                } else {
                    filaSeleccionada = -1;
                    columnaSeleccionada = -1;
                }
            }

            for (int i = 0; i < 9; i++) {
                if (estaDentroDelRectangulo(x, y, inicioBotonX + i * tamanoBoton, inicioBotonY, tamanoBoton, tamanoBoton)) {
                    if (filaSeleccionada != -1 && columnaSeleccionada != -1) {
                        int num = i + 1;

                        if (esSeguro(filaSeleccionada, columnaSeleccionada, num)) {
                            setfillstyle(SOLID_FILL, WHITE);
                            bar(inicioX + columnaSeleccionada * tamanoCelda + 1, inicioY + filaSeleccionada * tamanoCelda + 1,
                                inicioX + (columnaSeleccionada + 1) * tamanoCelda - 1, inicioY + (filaSeleccionada + 1) * tamanoCelda - 1);

                            setcolor(BLACK);
                            rectangle(inicioX + columnaSeleccionada * tamanoCelda, inicioY + filaSeleccionada * tamanoCelda, 
                                      inicioX + (columnaSeleccionada + 1) * tamanoCelda, inicioY + (filaSeleccionada + 1) * tamanoCelda);

                            tablero[filaSeleccionada][columnaSeleccionada] = num;
                            dibujarTablero(inicioX, inicioY);
                        } else {
                            setfillstyle(SOLID_FILL, LIGHTRED);
                            bar(inicioX + columnaSeleccionada * tamanoCelda + 1, inicioY + filaSeleccionada * tamanoCelda + 1,
                                inicioX + (columnaSeleccionada + 1) * tamanoCelda - 1, inicioY + (filaSeleccionada + 1) * tamanoCelda - 1);

                            setcolor(RED);
                            rectangle(inicioX + columnaSeleccionada * tamanoCelda, inicioY + filaSeleccionada * tamanoCelda, 
                                      inicioX + (columnaSeleccionada + 1) * tamanoCelda, inicioY + (filaSeleccionada + 1) * tamanoCelda);
                            setcolor(BLACK);

                            // Imprimir el número encima de la casilla roja
                            int x = inicioX + columnaSeleccionada * tamanoCelda + tamanoCelda / 2;
                            int y = inicioY + filaSeleccionada * tamanoCelda + tamanoCelda / 2;
                            char numStr[2];
                            sprintf(numStr, "%d", num);
                            outtextxy(x, y, numStr);
                        }

                        dibujarBotones(inicioBotonX, inicioBotonY);
                    }
                }
            }
        }
    }
}

bool Sudoku::esSeguro(int fila, int columna, int num) {
    std::function<bool(int)> checkRow = [&](int x) {
        if (x >= tamanoTablero) return true;
        if (tablero[fila][x] == num) return false;
        return checkRow(x + 1);
    };

    std::function<bool(int)> checkCol = [&](int x) {
        if (x >= tamanoTablero) return true;
        if (tablero[x][columna] == num) return false;
        return checkCol(x + 1);
    };

    if (!checkRow(0) || !checkCol(0)) return false;

    int inicioFila = fila - fila % 3, inicioColumna = columna - columna % 3;
    std::function<bool(int, int)> checkBox = [&](int i, int j) {
        if (i >= 3) return true;
        if (j >= 3) return checkBox(i + 1, 0);
        if (tablero[i + inicioFila][j + inicioColumna] == num) return false;
        return checkBox(i, j + 1);
    };

    return checkBox(0, 0);
}

bool Sudoku::resolverSudoku(int fila, int columna) {
    if (fila == tamanoTablero - 1 && columna == tamanoTablero) {
        return true;
    }

    if (columna == tamanoTablero) {
        fila++;
        columna = 0;
    }

    if (tablero[fila][columna] != 0) {
        return resolverSudoku(fila, columna + 1);
    }

    for (int num = 1; num <= tamanoTablero; num++) {
        if (esSeguro(fila, columna, num)) {
            tablero[fila][columna] = num;
            if (resolverSudoku(fila, columna + 1)) {
                return true;
            }
            tablero[fila][columna] = 0;
        }
    }

    return false;
}

void Sudoku::generarSudoku() {
    std::function<void(int, int)> clearBoard = [&](int i, int j) {
        if (i >= tamanoTablero) return;
        if (j >= tamanoTablero) return clearBoard(i + 1, 0);
        tablero[i][j] = 0;
        clearBoard(i, j + 1);
    };

    clearBoard(0, 0);
    resolverSudoku(0, 0);
}

void Sudoku::eliminarNumeros() {
    int count = celdasVacias;
    std::function<void()> removeNumbers = [&]() {
        if (count <= 0) return;
        int idCelda = std::rand() % (tamanoTablero * tamanoTablero);
        int i = idCelda / tamanoTablero;
        int j = idCelda % tamanoTablero;
        if (tablero[i][j] != 0) {
            tablero[i][j] = 0;
            count--;
        }
        removeNumbers();
    };

    removeNumbers();
}