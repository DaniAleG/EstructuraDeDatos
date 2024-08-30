#include "Snake.h"

// Snake.cpp
Snake::Snake(int x, int y) : direccionX(0), direccionY(0), colision(false) {
    cuerpo.insertarAlFinal(x, y);
}


void Snake::mover() {
    int nuevoX = cuerpo.obtenerCola()->x + direccionX;
    int nuevoY = cuerpo.obtenerCola()->y + direccionY;

    cuerpo.insertarAlFinal(nuevoX, nuevoY);
    cuerpo.eliminarAlInicio();
}

void Snake::cambiarDireccion(int nuevaDireccionX, int nuevaDireccionY) {
    // Evita que la serpiente se mueva en dirección opuesta
    if (direccionX + nuevaDireccionX != 0 || direccionY + nuevaDireccionY != 0) {
        direccionX = nuevaDireccionX;
        direccionY = nuevaDireccionY;
    }
}

bool Snake::verificarColision(int ancho, int alto) {
    Nodo* cabeza = cuerpo.obtenerCola();
    Nodo* actual = cuerpo.obtenerCabeza();

    // Colisión con el cuerpo
    while (actual != cabeza) {
        if (actual->x == cabeza->x && actual->y == cabeza->y) {
            return true;
        }
        actual = actual->siguiente;
    }

    // Colisión con los bordes del área de juego
    if (cabeza->x < 0 || cabeza->y < 0 || cabeza->x >= ancho || cabeza->y >= alto) {
        return true;
    }

    return false;
}

bool Snake::verificarComida(int comidaX, int comidaY) {
    Nodo* cabeza = cuerpo.obtenerCola();
    return (cabeza->x == comidaX && cabeza->y == comidaY);
}

void Snake::crecer() {
    Nodo* cabeza = cuerpo.obtenerCola();
    cuerpo.insertarAlFinal(cabeza->x + direccionX, cabeza->y + direccionY);
}

ListaDoble* Snake::obtenerCuerpo() {
    return &cuerpo;
}

void Snake::moverSinBordes(int ancho, int alto) {
    Nodo* cabeza = cuerpo.obtenerCola();
    int nuevoX = cabeza->x + direccionX;
    int nuevoY = cabeza->y + direccionY;

    // Teletransporte si la serpiente alcanza los bordes
    if (nuevoX >= ancho) nuevoX = 0;
    else if (nuevoX < 0) nuevoX = ancho - 1;

    if (nuevoY >= alto) nuevoY = 0;
    else if (nuevoY < 0) nuevoY = alto - 1;

    // Verificar si la nueva posición colisiona con el cuerpo
    Nodo* actual = cuerpo.obtenerCabeza();
    colision = false;  // Resetea la colisión
    while (actual != cabeza) {  // Excluir la cabeza de la verificación
        if (actual->x == nuevoX && actual->y == nuevoY) {
            colision = true;
            return;
        }
        actual = actual->siguiente;
    }

    cuerpo.insertarAlFinal(nuevoX, nuevoY);
    cuerpo.eliminarAlInicio();
}

bool Snake::verificarColisioSinBordes() {
    Nodo* cabeza = cuerpo.obtenerCola();
    Nodo* actual = cuerpo.obtenerCabeza();

    // Colisión con el cuerpo
    while (actual != cabeza) {
        if (actual->x == cabeza->x && actual->y == cabeza->y) {
            return true;
        }
        actual = actual->siguiente;
    }

    return colision;
}

