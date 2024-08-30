#include "Caballito.h"
#include <sstream>
#include <cstring>
#include <functional>

Caballito::Caballito() {}

void Caballito::dibujarImagenBMP(int x, int y, const char* archivo) {
    readimagefile(("ImagenesPiezas/" + std::string(archivo)).c_str(), x, y, x + 50, y + 50);
}

bool Caballito::isValid(Position pos) {
    return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
}

void Caballito::mostrarTableroVacio() {
    int n = 8; 
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Tablero Vacío");

    tamanoCuadro = std::min(anchoVentana, altoVentana) / (n + 2);
    int anchoTablero = tamanoCuadro * n;
    int altoTablero = tamanoCuadro * n;

    xInicio = (anchoVentana - anchoTablero) / 2;
    yInicio = (altoVentana - altoTablero) / 2;

    setbkcolor(BLACK);

    std::function<void(int, int)> dibujarTableroRec = [&](int fila, int col) {
        if (fila == n) return;

        if (col == n) {
            dibujarTableroRec(fila + 1, 0);
            return;
        }

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
            char letra = '1' + col;
            std::string texto(1, letra);
            outtextxy(x + tamanoCuadro / 2 - 4, yInicio - 20, const_cast<char*>(texto.c_str()));
        }

        if (col == 0) {
            char numero = '8' - (n - 1 - fila);
            std::string texto(1, numero);
            outtextxy(xInicio - 20, y + tamanoCuadro / 2 - 4, const_cast<char*>(texto.c_str()));
        }

        dibujarTableroRec(fila, col + 1);
    };
    dibujarTableroRec(0, 0);
}

void Caballito::dibujarCaballo(Position pos) {
    int left = xInicio + pos.y * tamanoCuadro + (tamanoCuadro - 50) / 2;
    int top = yInicio + pos.x * tamanoCuadro + (tamanoCuadro - 50) / 2;
    dibujarImagenBMP(left, top, "caballo_negro.bmp");
}

void Caballito::mostrarMovimientosCaballoRec(Position posCaballo, int movimientos[][2], bool visitado[][8], int i, int &posTextoY) {
    if (i >= 8) return;

    Position nuevaPos(posCaballo.x + movimientos[i][0], posCaballo.y + movimientos[i][1]);
    
    if (isValid(nuevaPos) && !visitado[nuevaPos.x][nuevaPos.y]) {
        visitado[nuevaPos.x][nuevaPos.y] = true;

        int left = xInicio + nuevaPos.y * tamanoCuadro;
        int top = yInicio + nuevaPos.x * tamanoCuadro;
        setcolor(RED);
        rectangle(left, top, left + tamanoCuadro, top + tamanoCuadro);

        dibujarCaballo(nuevaPos);

        std::ostringstream oss;
        oss << "Fila " << nuevaPos.x + 1 << " - Columna " << nuevaPos.y + 1;

        char buffer[100];
        std::strncpy(buffer, oss.str().c_str(), sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        setcolor(WHITE);
        outtextxy(xInicio + tamanoCuadro * 8 + 20, posTextoY, buffer);

        posTextoY += 20;
    }

    mostrarMovimientosCaballoRec(posCaballo, movimientos, visitado, i + 1, posTextoY);
}

void Caballito::mostrarMovimientosCaballo(Position posicionCaballo) {
    int movimientosCaballo[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    bool visitado[8][8] = {false};
    int posTextoY = 50;

    setlinestyle(SOLID_LINE, 0, 3);

    mostrarMovimientosCaballoRec(posicionCaballo, movimientosCaballo, visitado, 0, posTextoY);
}

void Caballito::ejecutar() {
    mostrarTableroVacio();

    srand(static_cast<unsigned int>(time(0)));

    Position knightPos(rand() % 8, rand() % 8);

    dibujarCaballo(knightPos);

    mostrarMovimientosCaballo(knightPos);

    getch();
    closegraph();
}
