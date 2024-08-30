/*Universidad de las Fuerzas Armadas ESPE
            SNAKE
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include "Snake.cpp"

using namespace std;

const int ANCHO = 30;
const int ALTO = 30;
const int TAM_CELDA = 20;
const int TAM_VENTANA_X = ANCHO * TAM_CELDA;
const int TAM_VENTANA_Y = ALTO * TAM_CELDA;

void generarComida(int& comidaX, int& comidaY, int ancho, int alto) {
    comidaX = rand() % ancho;
    comidaY = rand() % alto;
}

void dibujarJuego(Snake& snake, int comidaX, int comidaY, int offsetX, int offsetY, int windowWidth, int windowHeight, bool conBordes) {
    cleardevice();
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(windowWidth / 2, windowHeight / 2, LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(offsetX, offsetY, offsetX + TAM_VENTANA_X, offsetY + TAM_VENTANA_Y);

    // Dibuja la comida
    setfillstyle(SOLID_FILL, RED);
    int comidaX0 = offsetX + comidaX * TAM_CELDA;
    int comidaY0 = offsetY + comidaY * TAM_CELDA;
    bar(comidaX0, comidaY0, comidaX0 + TAM_CELDA, comidaY0 + TAM_CELDA);

    // Dibuja la serpiente
    setfillstyle(SOLID_FILL, BLUE);
    ListaDoble* cuerpo = snake.obtenerCuerpo();
    Nodo* actual = cuerpo->obtenerCabeza();
    while (actual) {
        int x0 = offsetX + actual->x * TAM_CELDA;
        int y0 = offsetY + actual->y * TAM_CELDA;
        bar(x0, y0, x0 + TAM_CELDA, y0 + TAM_CELDA);
        actual = actual->siguiente;
    }

    // Dibuja bordes solo si es necesario
    if (conBordes) {
        setcolor(BLACK);
        setlinestyle(SOLID_LINE, 0, 3);
        rectangle(offsetX, offsetY, offsetX + TAM_VENTANA_X, offsetY + TAM_VENTANA_Y);
    }
}

void dibujarBoton(int x1, int y1, int x2, int y2, const char* texto) {
    setbkcolor(LIGHTGRAY);
    setcolor(WHITE);
    rectangle(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, RED);
    floodfill((x1 + x2) / 2, (y1 + y2) / 2, WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(BLACK);
    outtextxy((x1 + x2) / 2 - textwidth(const_cast<char*>(texto)) / 2, (y1 + y2) / 2 - textheight(const_cast<char*>(texto)) / 2, const_cast<char*>(texto));
}

bool clicEnBoton(int x1, int y1, int x2, int y2) {
    int x = mousex();
    int y = mousey();
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

int mostrarMenu(int windowWidth, int windowHeight) {
    int anchoBoton = 200;
    int altoBoton = 50;
    int espacio = 20;
    int x1 = (windowWidth - anchoBoton) / 2;
    int y1 = (windowHeight - 4 * (altoBoton + espacio)) / 2;
    int x2 = x1 + anchoBoton;
    int y2 = y1 + altoBoton;
    setbkcolor(LIGHTGRAY);
    // Dibuja título
    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy((windowWidth - textwidth(const_cast<char*>("SNAKE"))) / 2, y1 - altoBoton - espacio * 2, const_cast<char*>("SNAKE"));
    // Dibuja botones
    dibujarBoton(x1, y1, x2, y2, "NIVEL 1");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "NIVEL 2");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "NIVEL 3");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Salir");

    // Detección de clic en botones
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            if (clicEnBoton(x1, y1 - 3 * (altoBoton + espacio), x2, y1 - 3 * (altoBoton + espacio) + altoBoton)) {
                return 0;
            } else if (clicEnBoton(x1, y1 - 2 * (altoBoton + espacio), x2, y1 - 2 * (altoBoton + espacio) + altoBoton)) {
                return 1;
            } else if (clicEnBoton(x1, y1 - (altoBoton + espacio), x2, y1 - (altoBoton + espacio) + altoBoton)) {
                return 2;
            } else if (clicEnBoton(x1, y1, x2, y1 + altoBoton)) {
                return 3;
            }
        }
    }
}

int mostrarGameOver(int windowWidth, int windowHeight) {
    cleardevice();
    setbkcolor(RED);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy((windowWidth - textwidth(const_cast<char*>("GAME OVER"))) / 2, windowHeight / 3, const_cast<char*>("GAME OVER"));

    // Dibuja botones
    int anchoBoton = 200;
    int altoBoton = 50;
    int espacio = 20;
    int x1 = (windowWidth - anchoBoton) / 2;
    int y1 = (windowHeight - 2 * (altoBoton + espacio)) / 2 + 100;
    int x2 = x1 + anchoBoton;
    int y2 = y1 + altoBoton;

    dibujarBoton(x1, y1, x2, y2, "Reintentar");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Volver al Menu");

    while (true) {
        delay(10);  // Añade un pequeño retraso para evitar el bucle rápido

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int clickX = mousex();
            int clickY = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if (clicEnBoton(x1, y1 - (altoBoton + espacio), x2, y1 - (altoBoton + espacio) + altoBoton)) {
                return 0;  // Reintentar
            } else if (clicEnBoton(x1, y1, x2, y1 + altoBoton)) {
                return 1;  // Volver al menú
            }
        }
    }
}

void nivel2(Snake& snake, int offsetX, int offsetY, int windowWidth, int windowHeight) {
    int comidaX, comidaY;
    int puntuacion = 0; // Variable para la puntuación
    generarComida(comidaX, comidaY, ANCHO, ALTO);

    while (true) {
        if (kbhit()) {
            char tecla = getch();
            switch (tecla) {
                case 'w': snake.cambiarDireccion(0, -1); break;
                case 'W': snake.cambiarDireccion(0, -1); break;
                case 's': snake.cambiarDireccion(0, 1); break;
                case 'S': snake.cambiarDireccion(0, 1); break;
                case 'a': snake.cambiarDireccion(-1, 0); break;
                case 'A': snake.cambiarDireccion(-1, 0); break;
                case 'd': snake.cambiarDireccion(1, 0); break;
                case 'D': snake.cambiarDireccion(1, 0); break;
            }
        }

        snake.mover();

        if (snake.verificarComida(comidaX, comidaY)) {
            snake.crecer();
            puntuacion += 5; // Aumenta la puntuación en 5
            generarComida(comidaX, comidaY, ANCHO, ALTO);
        }

        if (snake.verificarColision(ANCHO, ALTO)) {
            break;
        }

        dibujarJuego(snake, comidaX, comidaY, offsetX, offsetY, windowWidth, windowHeight, true);
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char textoPuntuacion[50];
        sprintf(textoPuntuacion, "Puntuacion: %d", puntuacion);
        outtextxy(offsetX + 10, offsetY - 30, textoPuntuacion); // Muestra la puntuación
        delay(100);
    }
}

void nivel1(Snake& snake, int offsetX, int offsetY, int windowWidth, int windowHeight) {
    int comidaX, comidaY;
    int puntuacion = 0;
    generarComida(comidaX, comidaY, ANCHO, ALTO);

    while (true) {
        if (kbhit()) {
            char tecla = getch();
            switch (tecla) {
                case 'w': snake.cambiarDireccion(0, -1); break;
                case 'W': snake.cambiarDireccion(0, -1); break;
                case 's': snake.cambiarDireccion(0, 1); break;
                case 'S': snake.cambiarDireccion(0, 1); break;
                case 'a': snake.cambiarDireccion(-1, 0); break;
                case 'A': snake.cambiarDireccion(-1, 0); break;
                case 'd': snake.cambiarDireccion(1, 0); break;
                case 'D': snake.cambiarDireccion(1, 0); break;
            }
        }

        snake.moverSinBordes(ANCHO, ALTO);

        if (snake.verificarComida(comidaX, comidaY)) {
            snake.crecer();
            puntuacion += 5;
            generarComida(comidaX, comidaY, ANCHO, ALTO);
        }

        if (snake.verificarColisioSinBordes()) {
            cout << "Game Over! Presiona cualquier tecla para volver al menu..." << endl;
            getch();
            break;
        }

        dibujarJuego(snake, comidaX, comidaY, offsetX, offsetY, windowWidth, windowHeight, false);
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char textoPuntuacion[50];
        sprintf(textoPuntuacion, "Puntuacion: %d", puntuacion);
        outtextxy(offsetX + 10, offsetY - 30, textoPuntuacion);
        delay(100);
    }
}

void nivel3(Snake& snake, int offsetX, int offsetY, int windowWidth, int windowHeight) {
    int comidaX, comidaY;
    int puntuacion = 0;
    int velocidad = 150;
    const int VELOCIDAD_MINIMA = 10;
    generarComida(comidaX, comidaY, ANCHO, ALTO);

    while (true) {
        if (kbhit()) {
            char tecla = getch();
            switch (tecla) {
                case 'w': snake.cambiarDireccion(0, -1); break;
                case 'W': snake.cambiarDireccion(0, -1); break;
                case 's': snake.cambiarDireccion(0, 1); break;
                case 'S': snake.cambiarDireccion(0, 1); break;
                case 'a': snake.cambiarDireccion(-1, 0); break;
                case 'A': snake.cambiarDireccion(-1, 0); break;
                case 'd': snake.cambiarDireccion(1, 0); break;
                case 'D': snake.cambiarDireccion(1, 0); break;
            }
        }

        snake.mover();

        if (snake.verificarComida(comidaX, comidaY)) {
            snake.crecer();
            puntuacion += 5;
            velocidad -= 10;
            if (velocidad < VELOCIDAD_MINIMA) {
                velocidad = VELOCIDAD_MINIMA;
            }
            generarComida(comidaX, comidaY, ANCHO, ALTO);
        }

        if (snake.verificarColision(ANCHO, ALTO)) {
            cout << "Game Over! Presiona cualquier tecla para volver al menu..." << endl;
            break;
        }

        dibujarJuego(snake, comidaX, comidaY, offsetX, offsetY, windowWidth, windowHeight, true);
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        char textoPuntuacion[50];
        sprintf(textoPuntuacion, "Puntuacion: %d", puntuacion);
        outtextxy(offsetX + 10, offsetY - 30, textoPuntuacion);
        delay(velocidad);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int windowPosX = 0;
    int windowPosY = 0;
    int windowWidth = screenWidth;
    int windowHeight = screenHeight;

    initwindow(windowWidth, windowHeight, "Snake Game", windowPosX, windowPosY);
    setbkcolor(LIGHTGRAY);

    int offsetX = (windowWidth - TAM_VENTANA_X) / 2;
    int offsetY = (windowHeight - TAM_VENTANA_Y) / 2;

    while (true) {
        int opcion = mostrarMenu(windowWidth, windowHeight);
        
        if (opcion == 3) break; // Salir del juego si se elige salir

        bool jugarNivel = true;
        while (jugarNivel) {
            Snake snake(10, 10);  // Inicializa la serpiente para el nuevo nivel
            cleardevice(); // Limpia la pantalla antes de empezar el nivel
            setbkcolor(LIGHTGRAY); // Establece el color de fondo

            if (opcion == 0) {
                nivel1(snake, offsetX, offsetY, windowWidth, windowHeight);
            } else if (opcion == 1) {
                nivel2(snake, offsetX, offsetY, windowWidth, windowHeight);
            } else if (opcion == 2) {
                nivel3(snake, offsetX, offsetY, windowWidth, windowHeight);
            }

            // Mostrar pantalla de Game Over después de terminar un nivel
            int resultado = mostrarGameOver(windowWidth, windowHeight);
            if (resultado == 1) {
                // Volver al menú sin cerrar la ventana
                cleardevice(); // Limpiar la pantalla
                setbkcolor(LIGHTGRAY); // Asegurarse de que el fondo es gris claro
                jugarNivel = false; // Salir del bucle del nivel para volver al menú
            } else if (resultado == 0) {
        // Reintentar el nivel, sin necesidad de inicializar nuevamente la serpiente ni limpiar la pantalla aquí.
        // La variable `opcion` ya tiene el nivel seleccionado, simplemente se mantiene en el bucle.
        continue;
            }
        }
    }
    closegraph();
    return 0;
}

