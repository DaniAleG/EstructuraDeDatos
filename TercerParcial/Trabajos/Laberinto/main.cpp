#include "laberinto.cpp"
#include <graphics.h>
#include <conio.h>

int main() {
    // Inicializar la ventana gráfica
    initwindow(TAMANO_LABERINTO * TAMANO_CELDA, TAMANO_LABERINTO * TAMANO_CELDA + 50, "Laberinto 10x10");

    // Crear una instancia del laberinto
    Laberinto laberinto;

    // Guardar el laberinto en un archivo de texto
    laberinto.guardarLaberintoEnArchivo("laberinto.txt");

    // Posición inicial del jugador
    Posicion jugador = {0, 1};  // Posición inicial en la entrada

    bool finJuego = false;

    while (!finJuego) {
        cleardevice();  // Limpia la pantalla
        laberinto.dibujarLaberinto();  // Dibuja el laberinto
        laberinto.dibujarJugador(jugador);  // Dibuja al jugador
        laberinto.moverJugador(jugador, finJuego);  // Mueve al jugador si es posible
        delay(100);  // Pequeño retraso para suavizar el movimiento
    }

    getch();  // Esperar una tecla para salir
    closegraph();

    return 0;
}
