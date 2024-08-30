#include "cuadroMagico.h"

void dibujarCuadradoVacio() {
    std::function<void(int)> dibujarLineas = [&](int i) {
        if (i > N) return;
        line(OFFSET_X, OFFSET_Y + i * CELL_SIZE, OFFSET_X + N * CELL_SIZE, OFFSET_Y + i * CELL_SIZE); // Líneas horizontales
        line(OFFSET_X + i * CELL_SIZE, OFFSET_Y, OFFSET_X + i * CELL_SIZE, OFFSET_Y + N * CELL_SIZE); // Líneas verticales
        dibujarLineas(i + 1);
    };
    dibujarLineas(0);
}

void dibujarNumero(int num, int fila, int columna, bool esFilaNumeros) {
    char numero[2];
    sprintf(numero, "%d", num);
    int x = (OFFSET_X) + columna * CELL_SIZE + CELL_SIZE / 2;
    int y = esFilaNumeros ? NUMERO_Y : OFFSET_Y + fila * CELL_SIZE + CELL_SIZE / 2;
    outtextxy(x - 10, y - 10, numero);
}

int obtenerFila(int y) {
    return (y - OFFSET_Y) / CELL_SIZE;
}

int obtenerColumna(int x) {
    return (x - OFFSET_X) / CELL_SIZE;
}

bool estaDentroDelCuadrado(int x, int y) {
    return x >= OFFSET_X && x <= OFFSET_X + N * CELL_SIZE && y >= OFFSET_Y && y <= OFFSET_Y + N * CELL_SIZE;
}

bool estaEnFilaNumeros(int x, int y) {
    return y >= NUMERO_Y - 10 && y <= NUMERO_Y + 10 && x >= OFFSET_X && x <= OFFSET_X + (N * CELL_SIZE * N);
}

bool esCuadradoMagico(int cuadrado[N][N]) {
    int sumaMagica = 15; // Para un cuadrado mágico 3x3, la suma mágica es 15

    std::function<bool(int)> sumarFilas = [&](int i) {
        if (i >= N) return true;
        int sumaFila = 0;
        std::function<void(int)> sumarFila = [&](int j) {
            if (j >= N) return;
            sumaFila += cuadrado[i][j];
            sumarFila(j + 1);
        };
        sumarFila(0);
        return sumaFila == sumaMagica && sumarFilas(i + 1);
    };
    if (!sumarFilas(0)) return false;

    std::function<bool(int)> sumarColumnas = [&](int j) {
        if (j >= N) return true;
        int sumaColumna = 0;
        std::function<void(int)> sumarColumna = [&](int i) {
            if (i >= N) return;
            sumaColumna += cuadrado[i][j];
            sumarColumna(i + 1);
        };
        sumarColumna(0);
        return sumaColumna == sumaMagica && sumarColumnas(j + 1);
    };
    if (!sumarColumnas(0)) return false;

    int sumaDiagonal1 = 0, sumaDiagonal2 = 0;
    std::function<void(int)> sumarDiagonales = [&](int i) {
        if (i >= N) return;
        sumaDiagonal1 += cuadrado[i][i];
        sumaDiagonal2 += cuadrado[i][N - 1 - i];
        sumarDiagonales(i + 1);
    };
    sumarDiagonales(0);

    return sumaDiagonal1 == sumaMagica && sumaDiagonal2 == sumaMagica;
}