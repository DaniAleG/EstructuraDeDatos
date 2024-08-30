/*Universidad de las Fuerzas Armadas ESPE
            N REINAS
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <limits>
#include "n_reinas.cpp"
#include "Caballito.cpp"

// Función para dibujar imágenes BMP
void dibujarImagenBMP(int x, int y, const char* archivo) {
    readimagefile(("ImagenesPiezas/" + std::string(archivo)).c_str(), x, y, x + 50, y + 50);
}

void dibujarTableroConImagenes(const std::vector<int>* solucion, int n) {
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Ajedrez");

    int tamanoCuadro = std::min(anchoVentana, altoVentana) / (n + 2);
    int anchoTablero = tamanoCuadro * n;
    int altoTablero = tamanoCuadro * n;

    int xInicio = (anchoVentana - anchoTablero) / 2;
    int yInicio = (altoVentana - altoTablero) / 2;

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
            char letra = 'a' + col;
            std::string texto(1, letra);
            outtextxy(x + tamanoCuadro / 2 - 4, yInicio - 20, const_cast<char*>(texto.c_str()));
        }

        if (col == 0) {
            char numero = '1' + (n - 1 - fila);
            std::string texto(1, numero);
            outtextxy(xInicio - 20, y + tamanoCuadro / 2 - 4, const_cast<char*>(texto.c_str()));
        }

        dibujarTableroRec(fila, col + 1);
    };

    std::function<void(int)> dibujarPiezasRec = [&](int fila) {
        if (fila == n) return;

        int columna = (*solucion)[fila];
        int x = xInicio + columna * tamanoCuadro + tamanoCuadro / 4;
        int y = yInicio + fila * tamanoCuadro + tamanoCuadro / 4;

        dibujarImagenBMP(x, y, "reina_blanca.bmp");

        dibujarPiezasRec(fila + 1);
    };

    dibujarTableroRec(0, 0);
    dibujarPiezasRec(0);

    std::cout << "Presiona Enter para volver al menu..." << std::endl;
    while (getch() != '\r'); 

    closegraph();
}
// Función para dibujar un botón
void dibujarBoton(int x1, int y1, int x2, int y2, const char* texto) {
    setcolor(WHITE);
    rectangle(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill((x1 + x2) / 2, (y1 + y2) / 2, WHITE);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    outtextxy((x1 + x2) / 2 - textwidth(const_cast<char*>(texto)) / 2, (y1 + y2) / 2 - textheight(const_cast<char*>(texto)) / 2, const_cast<char*>(texto));
}

// Función para verificar si el clic está dentro de un botón
bool clicEnBoton(int x1, int y1, int x2, int y2) {
    int x = mousex();
    int y = mousey();
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

// Función para mostrar el menú y detectar la opción seleccionada por clic
int mostrarMenu() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char*>("C:\\Turboc3\\BGI"));

    if (graphresult() != grOk) {
        std::cerr << "Error al inicializar el modo gráfico." << std::endl;
        return -1;
    }

    setbkcolor(BLACK);
    cleardevice();

    // Definir los botones
    const int anchoBoton = 300;
    const int altoBoton = 50;
    const int espacio = 20;

    int x1 = (getmaxx() - anchoBoton) / 2;
    int y1 = (getmaxy() - 5 * (altoBoton + espacio)) / 2;
    int x2 = x1 + anchoBoton;
    int y2 = y1 + altoBoton;

    // Dibujar los botones
    dibujarBoton(x1, y1, x2, y2, "Mostrar tablero vacio");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Mostrar tablero con todas las piezas");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Resolver problema de las N reinas");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Caballito");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Salir");

    // Mostrar el menú
    int seleccion = -1;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) { // Si se hace clic con el botón izquierdo del ratón
            if (clicEnBoton(x1, y1 - 4 * (altoBoton + espacio), x2, y1 - 4 * (altoBoton + espacio) + altoBoton)) {
                seleccion = 0; // Opción "Mostrar tablero vacío"
                break;
            } else if (clicEnBoton(x1, y1 - 3 * (altoBoton + espacio), x2, y1 - 3 * (altoBoton + espacio) + altoBoton)) {
                seleccion = 1; // Opción "Mostrar tablero con todas las piezas"
                break;
            } else if (clicEnBoton(x1, y1 - 2 * (altoBoton + espacio), x2, y1 - 2 * (altoBoton + espacio) + altoBoton)) {
                seleccion = 2; // Opción "Resolver problema de las N reinas"
                break;
            } else if (clicEnBoton(x1, y1 - (altoBoton + espacio), x2, y1 - (altoBoton + espacio) + altoBoton)) {
                seleccion = 3; // Opción "Caballito"
                break;
            } else if (clicEnBoton(x1, y1, x2, y1 + altoBoton)) {
                seleccion = 4; // Opción "Salir"
                break;
            }
        }
    }

    closegraph();
    return seleccion;
}

void dibujarTableroVacio() {
    int n = 8; 
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Tablero Vacío");

    int tamanoCuadro = std::min(anchoVentana, altoVentana) / (n + 2);
    int anchoTablero = tamanoCuadro * n;
    int altoTablero = tamanoCuadro * n;

    int xInicio = (anchoVentana - anchoTablero) / 2;
    int yInicio = (altoVentana - altoTablero) / 2;

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
            char letra = 'a' + col;
            std::string texto(1, letra);
            outtextxy(x + tamanoCuadro / 2 - 4, yInicio - 20, const_cast<char*>(texto.c_str()));
        }

        if (col == 0) {
            char numero = '1' + (n - 1 - fila);
            std::string texto(1, numero);
            outtextxy(xInicio - 20, y + tamanoCuadro / 2 - 4, const_cast<char*>(texto.c_str()));
        }

        dibujarTableroRec(fila, col + 1);
    };
    dibujarTableroRec(0, 0);
    std::cout << "Presiona Enter para volver al menu..." << std::endl;
    while (getch() != '\r'); 

    closegraph();
}

void dibujarTableroConTodasLasPiezas() {
    int n = 8; 
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Tablero con Piezas");

    int tamanoCuadro = std::min(anchoVentana, altoVentana) / (n + 2);
    int anchoTablero = tamanoCuadro * n;
    int altoTablero = tamanoCuadro * n;

    int xInicio = (anchoVentana - anchoTablero) / 2;
    int yInicio = (altoVentana - altoTablero) / 2;

    setbkcolor(BLACK);

    // Inicializar el tablero con las piezas
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
            char letra = 'a' + col;
            std::string texto(1, letra);
            outtextxy(x + tamanoCuadro / 2 - 4, yInicio - 20, const_cast<char*>(texto.c_str()));
        }

        if (col == 0) {
            char numero = '1' + (n - 1 - fila);
            std::string texto(1, numero);
            outtextxy(xInicio - 20, y + tamanoCuadro / 2 - 4, const_cast<char*>(texto.c_str()));
        }

        // Dibujar piezas en sus posiciones iniciales
        if (fila == 0 || fila == 1 || fila == 6 || fila == 7) {
            const char* imagen;
            if (fila == 0) { // Primera fila
                if (col == 0 || col == 7) imagen = "torre_blanca.bmp";
                else if (col == 1 || col == 6) imagen = "caballo_blanco.bmp";
                else if (col == 2 || col == 5) imagen = "alfil_blanco.bmp";
                else if (col == 3) imagen = "reina_blanca.bmp";
                else if (col == 4) imagen = "rey_blanco.bmp";
            } else if (fila == 1) { // Segunda fila
                imagen = "peon_blanco.bmp";
            } else if (fila == 6) { // Séptima fila
                imagen = "peon_negro.bmp";
            } else { // Última fila
                if (col == 0 || col == 7) imagen = "torre_negra.bmp";
                else if (col == 1 || col == 6) imagen = "caballo_negro.bmp";
                else if (col == 2 || col == 5) imagen = "alfil_negro.bmp";
                else if (col == 3) imagen = "reina_negra.bmp";
                else if (col == 4) imagen = "rey_negro.bmp";
            }

            dibujarImagenBMP(x + tamanoCuadro / 4, y + tamanoCuadro / 4, imagen);
        }

        dibujarTableroRec(fila, col + 1);
    };

    dibujarTableroRec(0, 0);
    std::cout << "Presiona Enter para volver al menu..." << std::endl;
    while (getch() != '\r'); 

    closegraph();
}
// Función para resolver el problema de las N reinas
void resolverProblemaNReinas(int n) {
    std::vector<int> solucion = resolverNReinas(n);

    if (solucion.empty()) {
        std::cerr << "No se encontro ninguna solucion para el numero de reinas ingresado " << n << ".\n";
        return;
    }

    dibujarTableroConImagenes(&solucion, n);
}

// Función principal
int main() {
    Caballito caballito;
    int opcion, n;
    while ((opcion = mostrarMenu()) != 4) { // Mientras no se elija la opción de salir
        switch (opcion) {
            case 0: // Mostrar tablero vacío
                dibujarTableroVacio();
                break;
            case 1: // Mostrar tablero con todas las piezas
                dibujarTableroConTodasLasPiezas();
                break;
            case 2: // Resolver problema de las N reinas
                std::cout << "Ingrese el número de reinas (1-8): ";
                while (!(std::cin >> n) || n < 1 || n > 8) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Número inválido. Por favor ingrese un número entre 1 y 8: ";
                }
                resolverProblemaNReinas(n);
                break;
            case 3: // Caballito
                caballito.ejecutar();
                break;
            default:
                std::cerr << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }
    }

    std::cout << "Programa terminado." << std::endl;
    return 0;
}