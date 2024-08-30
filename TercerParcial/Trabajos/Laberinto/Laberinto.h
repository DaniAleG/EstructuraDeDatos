#ifndef LABERINTO_H
#define LABERINTO_H

#include <string>

const int TAMANO_LABERINTO = 10;  // Tamano del laberinto
const int TAMANO_CELDA = 40;  // Tamano de cada celda en pixeles

struct Posicion {
    int x;
    int y;
};

class Laberinto {
public:
    Laberinto();
    void generarLaberinto();
    void guardarLaberintoEnArchivo(const std::string &nombreArchivo) const;
    void dibujarLaberinto() const;
    void moverJugador(Posicion &jugador, bool &finJuego);
    void dibujarJugador(const Posicion &jugador) const;
private:
    int laberinto[TAMANO_LABERINTO][TAMANO_LABERINTO];
};

#endif // LABERINTO_H
