#ifndef TETRIS_H
#define TETRIS_H

#include <string>
#include "ListaSimple.cpp"
class Tetris {
public:
    int ANCHO =154;
    int ALTO =43;
    static const char VACIO;

    Tetris();
    ~Tetris();

    void iniciar(ListaSimple<std::string>& lista);

private:
    char** tablero;
    int posX, posY;
    char piezaActual;
    

    void inicializarTablero();
    void imprimirTablero() const;
    bool verificarColision(int x, int y) const;
    void fusionarPieza(char pieza, int x, int y);
    void eliminarPieza(int x, int y);
    void generarPieza();
    void moverIzquierda();
    void moverDerecha();
    void moverAbajo();
    void gotoxySimple(int x, int y) const;
    std::string aMayusculas(const std::string& str) const;
};

#endif // TETRIS_H
