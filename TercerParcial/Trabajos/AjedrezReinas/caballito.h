#ifndef CABALLITO_H
#define CABALLITO_H

#include <graphics.h>
#include <cstdlib>
#include <ctime>

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Caballito {
public:
    Caballito();
    void mostrarTableroVacio();
    void dibujarCaballo(Position pos);
    void mostrarMovimientosCaballo(Position knightPos);
    void mostrarMovimientosCaballoRec(Position posCaballo, int movimientos[][2], bool visitado[][8], int i, int &posTextoY);
    void ejecutar();

private:
    int tamanoCuadro;
    int xInicio;
    int yInicio;

    bool isValid(Position pos);
    void dibujarImagenBMP(int x, int y, const char* archivo);
};

#endif // CABALLITO_H
