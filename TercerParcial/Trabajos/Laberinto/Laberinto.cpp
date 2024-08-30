#include "laberinto.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

// Constructor para inicializar el laberinto
Laberinto::Laberinto() {
    generarLaberinto();
}

// Funcion para generar el laberinto
void Laberinto::generarLaberinto() {
    srand(time(0));

    // Inicializar el laberinto con paredes
    for (int i = 0; i < TAMANO_LABERINTO; i++) {
        for (int j = 0; j < TAMANO_LABERINTO; j++) {
            laberinto[i][j] = 1;  // Pared
        }
    }

    // Crear caminos
    for (int i = 1; i < TAMANO_LABERINTO - 1; i++) {
        for (int j = 1; j < TAMANO_LABERINTO - 1; j++) {
            laberinto[i][j] = 2;  // Camino
        }
    }

    // Crear entrada y salida con espacios libres alrededor
    laberinto[1][0] = 3;               // Entrada
    laberinto[1][1] = 2;               // Camino
    laberinto[2][1] = 2;               // Camino

    laberinto[TAMANO_LABERINTO - 2][TAMANO_LABERINTO - 1] = 4;  // Salida
    laberinto[TAMANO_LABERINTO - 2][TAMANO_LABERINTO - 2] = 2;  // Camino
    laberinto[TAMANO_LABERINTO - 3][TAMANO_LABERINTO - 2] = 2;  // Camino

    // Agregar algunas paredes aleatorias dentro del laberinto
    for (int i = 0; i < TAMANO_LABERINTO * 2; i++) {
        int x = rand() % (TAMANO_LABERINTO - 2) + 1;
        int y = rand() % (TAMANO_LABERINTO - 2) + 1;

        // Asegurarse de no colocar paredes cerca de la entrada y la salida
        if ((x >= 0 && x <= 2 && y >= 0 && y <= 2) || 
            (x >= TAMANO_LABERINTO - 3 && x <= TAMANO_LABERINTO - 1 && y >= TAMANO_LABERINTO - 3 && y <= TAMANO_LABERINTO - 1)) {
            continue;
        }

        laberinto[x][y] = 1;  // Pared
    }
}

// Funcion para guardar el laberinto en un archivo de texto
void Laberinto::guardarLaberintoEnArchivo(const string &nombreArchivo) const {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (int i = 0; i < TAMANO_LABERINTO; i++) {
        for (int j = 0; j < TAMANO_LABERINTO; j++) {
            archivoSalida << laberinto[i][j] << ' ';
        }
        archivoSalida << endl;
    }

    archivoSalida.close();
}

// Funcion para dibujar el laberinto en la ventana grafica
void Laberinto::dibujarLaberinto() const {
    for (int i = 0; i < TAMANO_LABERINTO; i++) {
        for (int j = 0; j < TAMANO_LABERINTO; j++) {
            int x = j * TAMANO_CELDA;
            int y = i * TAMANO_CELDA;

            // Seleccionar color segun el valor de la celda
            if (laberinto[i][j] == 1) {
                setfillstyle(SOLID_FILL, BROWN);  // Pared
            } else if (laberinto[i][j] == 2) {
                setfillstyle(SOLID_FILL, LIGHTGRAY);  // Camino
            } else if (laberinto[i][j] == 3) {
                setfillstyle(SOLID_FILL, GREEN);  // Entrada
            } else if (laberinto[i][j] == 4) {
                setfillstyle(SOLID_FILL, RED);  // Salida
            }

            // Dibujar la celda
            bar(x, y, x + TAMANO_CELDA, y + TAMANO_CELDA);
        }
    }
}

// Funcion para mover el jugador en el laberinto
void Laberinto::moverJugador(Posicion &jugador, bool &finJuego) {
    if (kbhit()) {  // Verifica si una tecla fue presionada
        int tecla = getch();  // Captura la tecla presionada
        int dx = 0, dy = 0;

        switch (tecla) {
            case KEY_UP: dy = -1; break; // Flecha arriba
            case KEY_DOWN: dy = 1; break;  // Flecha abajo
            case KEY_LEFT: dx = -1; break; // Flecha izquierda
            case KEY_RIGHT: dx = 1; break;  // Flecha derecha
        }

        int nuevoX = jugador.x + dx;
        int nuevoY = jugador.y + dy;

        // Comprobar si el nuevo movimiento es valido
        if (nuevoX >= 0 && nuevoX < TAMANO_LABERINTO && nuevoY >= 0 && nuevoY < TAMANO_LABERINTO && (laberinto[nuevoY][nuevoX] == 2 || laberinto[nuevoY][nuevoX] == 4)) {
            jugador.x = nuevoX;
            jugador.y = nuevoY;

            // Si el jugador llega a la salida
            if (laberinto[jugador.y][jugador.x] == 4) {
                outtextxy(50, TAMANO_LABERINTO * TAMANO_CELDA + 10, const_cast<char*>("Felicidades, has llegado a la salida"));
                finJuego = true;
            }
        }
    }
}

// Funcion para dibujar al jugador
void Laberinto::dibujarJugador(const Posicion &jugador) const {
    setfillstyle(SOLID_FILL, BLUE);
    bar(jugador.x * TAMANO_CELDA, jugador.y * TAMANO_CELDA, (jugador.x + 1) * TAMANO_CELDA, (jugador.y + 1) * TAMANO_CELDA);
}
