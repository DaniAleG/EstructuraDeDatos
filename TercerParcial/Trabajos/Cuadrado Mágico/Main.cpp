/*Universidad de las Fuerzas Armadas ESPE
                CUADRO MAGICO
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include "cuadroMagico.cpp"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, ""); // Inicializar modo gráfico
    int x = getmaxwidth();
    int y = getmaxheight();

    initwindow(x, y); // Inicializar ventana gráfica
    setbkcolor(WHITE); // Establecer fondo blanco
    cleardevice(); // Limpiar pantalla con el color de fondo
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // Aumentar el tamaño del texto
    setcolor(RED); // Color del texto y del cuadrado

    int cuadrado[N][N] = {0};  // Cuadrado mágico vacío
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Números disponibles
    bool numeroDisponible[9] = {true, true, true, true, true, true, true, true, true};  // Estado de los números
    int seleccionado = -1;

    // Dibujar cuadrado vacío
    dibujarCuadradoVacio();

    // Dibujar números debajo del cuadrado
    std::function<void(int)> dibujarNumeros = [&](int i) {
        if (i >= N * N) return;
        dibujarNumero(numeros[i], 0, i, true);  // Colocar correctamente los números en la fila inferior
        dibujarNumeros(i + 1);
    };
    dibujarNumeros(0);

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex();
            int y = mousey();

            if (seleccionado == -1 && estaEnFilaNumeros(x, y)) {
                int columna = obtenerColumna(x);
                int indice = columna; // Índice correcto en el array de números
                if (numeroDisponible[indice]) {
                    seleccionado = numeros[indice];
                    numeroDisponible[indice] = false;
                    setcolor(RED);
                    rectangle(OFFSET_X + columna * CELL_SIZE, NUMERO_Y - 20,
                              (OFFSET_X) + (columna + 1) * CELL_SIZE, NUMERO_Y + 20);
                }
            } else if (seleccionado != -1 && estaDentroDelCuadrado(x, y)) {
                int fila = obtenerFila(y);
                int columna = obtenerColumna(x);

                if (cuadrado[fila][columna] == 0) {
                    cuadrado[fila][columna] = seleccionado;
                    seleccionado = -1;

                    cleardevice();
                    setbkcolor(WHITE); // Asegurarse de que el fondo sigue siendo blanco
                    setcolor(RED);
                    dibujarCuadradoVacio();

                    // Redibujar números colocados en el cuadrado
                    std::function<void(int)> redibujarNumerosCuadrado = [&](int i) {
                        if (i >= N) return;
                        std::function<void(int)> redibujarFila = [&](int j) {
                            if (j >= N) return;
                            if (cuadrado[i][j] != 0) {
                                dibujarNumero(cuadrado[i][j], i, j);
                            }
                            redibujarFila(j + 1);
                        };
                        redibujarFila(0);
                        redibujarNumerosCuadrado(i + 1);
                    };
                    redibujarNumerosCuadrado(0);

                    // Redibujar números en la fila de selección
                    std::function<void(int)> redibujarNumerosSeleccion = [&](int i) {
                        if (i >= N * N) return;
                        if (numeroDisponible[i]) {
                            dibujarNumero(numeros[i], 0, i, true);
                        }
                        redibujarNumerosSeleccion(i + 1);
                    };
                    redibujarNumerosSeleccion(0);

                    // Verificar si se ha completado el cuadrado mágico
                    bool completo = true;
                    std::function<void(int)> verificarCuadrado = [&](int i) {
                        if (i >= N || !completo) return;
                        std::function<void(int)> verificarFila = [&](int j) {
                            if (j >= N || !completo) return;
                            if (cuadrado[i][j] == 0) {
                                completo = false;
                            }
                            verificarFila(j + 1);
                        };
                        verificarFila(0);
                        verificarCuadrado(i + 1);
                    };
                    verificarCuadrado(0);

                    if (completo) {
                        if (esCuadradoMagico(cuadrado)) {
                            outtextxy(OFFSET_X + N * CELL_SIZE + 20, OFFSET_Y + CELL_SIZE, "Cuadrado Magico!");
                        } else {
                            outtextxy(OFFSET_X + N * CELL_SIZE + 20, OFFSET_Y + CELL_SIZE, "Intenta de Nuevo!");
                        }
                        delay(3000); // Esperar 3 segundos
                        closegraph(); // Cerrar modo gráfico y salir
                        return 0;
                    }
                }
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

    closegraph();  // Cerrar modo gráfico
    return 0;
}