#include <iostream>
#include <vector>
#include <string>
#include <graphics.h>
#include <conio.h>
#include <limits>

void dibujarImagenBMP(int x, int y, const char* archivo) {
    readimagefile(("ImagenesPiezas/" + std::string(archivo)).c_str(), x, y, x + 50, y + 50);
}

void dibujarTableroConImagenes(int n) {
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Ajedrez");

    int tamanoCuadro = std::min(anchoVentana, altoVentana) / (n + 2);
    int anchoTablero = tamanoCuadro * n;
    int altoTablero = tamanoCuadro * n;

    int xInicio = (anchoVentana - anchoTablero) / 2;
    int yInicio = (altoVentana - altoTablero) / 2;

    setbkcolor(BLACK);

    // Dibujar el tablero
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            int x = xInicio + col * tamanoCuadro;
            int y = yInicio + fila * tamanoCuadro;

            if ((fila + col) % 2 == 0) {
                setfillstyle(SOLID_FILL, BLUE);
            } else {
                setfillstyle(SOLID_FILL, DARKGRAY);
            }

            bar(x, y, x + tamanoCuadro, y + tamanoCuadro);

            setcolor(WHITE);
            setbkcolor(BLACK);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

            if (fila == 0) {
                char letra = 'a' + col;
                std::string texto(1, letra);
                outtextxy(x + tamanoCuadro / 2 - 4, yInicio - 20, const_cast<char*>(texto.c_str()));
            }

            if (col == 0) {
                char numero = '1' + (n - 1 - fila);
                std::string texto(1, numero);
                outtextxy(xInicio - 20, y + tamanoCuadro / 2 - 4, const_cast<char*>(texto.c_str()));
            }
        }
    }

    // Función para dibujar las piezas en sus posiciones iniciales
    auto dibujarPieza = [&](const char* archivo, int fila, int col) {
        int x = xInicio + col * tamanoCuadro;
        int y = yInicio + fila * tamanoCuadro;
        dibujarImagenBMP(x, y, archivo);
    };

    // Dibujar las piezas blancas
    for (int col = 0; col < n; col++) {
        dibujarPieza("peon_blanco.bmp", 6, col);
    }
    dibujarPieza("torre_blanca.bmp", 7, 0);
    dibujarPieza("caballo_blanco.bmp", 7, 1);
    dibujarPieza("alfil_blanco.bmp", 7, 2);
    dibujarPieza("reina_blanca.bmp", 7, 3);
    dibujarPieza("rey_blanco.bmp", 7, 4);
    dibujarPieza("alfil_blanco.bmp", 7, 5);
    dibujarPieza("caballo_blanco.bmp", 7, 6);
    dibujarPieza("torre_blanca.bmp", 7, 7);

    // Dibujar las piezas negras
    for (int col = 0; col < n; col++) {
        dibujarPieza("peon_negro.bmp", 1, col);
    }
    dibujarPieza("torre_negra.bmp", 0, 0);
    dibujarPieza("caballo_negro.bmp", 0, 1);
    dibujarPieza("alfil_negro.bmp", 0, 2);
    dibujarPieza("reina_negra.bmp", 0, 3);
    dibujarPieza("rey_negro.bmp", 0, 4);
    dibujarPieza("alfil_negro.bmp", 0, 5);
    dibujarPieza("caballo_negro.bmp", 0, 6);
    dibujarPieza("torre_negra.bmp", 0, 7);

    _getch();
    closegraph();
}

int main() {
    int n = 8; // Para el tablero de ajedrez, n siempre es 8

    dibujarTableroConImagenes(n);

    return 0;
}
