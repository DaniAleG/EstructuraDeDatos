#ifndef SNAKE_H
#define SNAKE_H

#include "ListaDoble.cpp"

// Snake.h
class Snake {
public:
    // Métodos públicos
    Snake(int x, int y);
    void cambiarDireccion(int dx, int dy);
    void mover();
    void moverSinBordes(int ancho, int alto);
    void crecer();
    bool verificarComida(int comidaX, int comidaY);
    bool verificarColision(int ancho, int alto);
    ListaDoble* obtenerCuerpo();
    bool verificarColisioSinBordes();
    void reiniciar();
private:
    ListaDoble cuerpo;
    int direccionX, direccionY;
    bool colision;  // Añadir esta línea para la variable de colisión
};


#endif
