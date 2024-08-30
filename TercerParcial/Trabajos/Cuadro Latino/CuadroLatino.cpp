#include "CuadroLatino.h"

CuadroLatino::CuadroLatino() : n(0), size(0), square(nullptr) {}

CuadroLatino::~CuadroLatino() {
    if (square) {
        for (int i = 0; i < n; i++) {
            delete[] square[i];
        }
        delete[] square;
    }
}

void CuadroLatino::iniciar() {
    bool continueProgram = true;

    while (continueProgram) {
        n = validarNumeros("Ingrese el valor de n para el cuadrado latino (entero positivo, diferente de 2 y 6): ");

        // Liberar la memoria anterior, si existe
        if (square) {
            for (int i = 0; i < n; i++) {
                delete[] square[i];
            }
            delete[] square;
        }

        // Inicializar la matriz para el cuadrado latino
        square = new int*[n];
        for (int i = 0; i < n; i++) {
            square[i] = new int[n];
            std::fill(square[i], square[i] + n, 0);
        }

        // Inicializar graphics mode en pantalla completa
        int maxX = getmaxwidth();
        int maxY = getmaxheight();
        initwindow(maxX, maxY, "Cuadrado Latino");

        // Configurar el fondo de la ventana
        setbkcolor(BLACK);
        cleardevice();

        size = (maxX < maxY) ? maxX / 2 : maxY / 2;
        dibujarCuadroLatino(size);

        int selectedNumber = 0;
        bool windowClosed = false;

        while (!windowClosed) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x != -1 && y != -1) {
                int startX = (maxX - size) / 2;
                int startY = (maxY - size) / 2;
                int cellSize = size / n;

                int buttonSize = 60;
                for (int i = 1; i <= n; i++) {
                    int buttonX = startX + size + 20;
                    int buttonY = startY + (i - 1) * (buttonSize + 10);
                    if (x >= buttonX && x <= buttonX + buttonSize && y >= buttonY && y <= buttonY + buttonSize) {
                        selectedNumber = i;
                        break;
                    }
                }

                int buttonX = startX + size + 20;
                int buttonY = startY + n * (buttonSize + 10);
                if (x >= buttonX && x <= buttonX + 200 && y >= buttonY && y <= buttonY + 50) {
                    if (verificarCuadroLatino()) {
                        setcolor(GREEN);
                        char correctText[] = "Correcto";
                        outtextxy(maxX / 2 - 50, maxY / 2 + size / 2 + 50, correctText);
                        delay(2000);
                        limpiarPantalla();
                        windowClosed = true; // Salir del bucle actual y volver a pedir un nuevo valor de n
                    } else {
                        setcolor(RED);
                        char incorrectText[] = "Incorrecto";
                        outtextxy(maxX / 2 - 50, maxY / 2 + size / 2 + 50, incorrectText);
                        delay(2000);
                        limpiarPantalla();
                        // No se borra la matriz, solo se redibuja la pantalla con los datos incorrectos
                    }
                } else {
                    int row = (y - startY) / cellSize;
                    int col = (x - startX) / cellSize;

                    if (row >= 0 && row < n && col >= 0 && col < n && selectedNumber != 0) {
                        square[row][col] = selectedNumber;
                        limpiarPantalla();
                        dibujarCeldasRecursivamente(0, 0);
                    }
                }
            }

            if (kbhit() && getch() == 27) { // Tecla ESC
                windowClosed = true;
                continueProgram = false; // Salir del bucle principal
            }
        }

        // Liberar la memoria
        if (square) {
            for (int i = 0; i < n; i++) {
                delete[] square[i];
            }
            delete[] square;
        }

        closegraph();
    }
}

void CuadroLatino::dibujarCuadroLatino(int size) {
    int maxX = getmaxx();
    int maxY = getmaxy();
    int startX = (maxX - size) / 2;
    int startY = (maxY - size) / 2;
    int cellSize = size / n;

    setfillstyle(SOLID_FILL, MAGENTA);
    setcolor(WHITE);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rectangle(startX + j * cellSize, startY + i * cellSize,
                      startX + (j + 1) * cellSize, startY + (i + 1) * cellSize);
            floodfill(startX + j * cellSize + 1, startY + i * cellSize + 1, WHITE);
        }
    }

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);

    int buttonSize = 60;
    for (int i = 1; i <= n; i++) {
        int buttonX = startX + size + 20;
        int buttonY = startY + (i - 1) * (buttonSize + 10);
        rectangle(buttonX, buttonY, buttonX + buttonSize, buttonY + buttonSize);
        setcolor(WHITE);
        char numText[3];
        sprintf(numText, "%d", i);
        outtextxy(buttonX + 15, buttonY + 15, numText);
    }

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    int buttonX = startX + size + 20;
    int buttonY = startY + n * (buttonSize + 10);
    int buttonWidth = 200;
    int buttonHeight = 50;
    rectangle(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);
    setcolor(RED);

    char comprobarText[] = "Comprobar"; // Variable temporal
    outtextxy(buttonX + 20, buttonY + 15, comprobarText);
}

void CuadroLatino::dibujarTextoCelda(int row, int col, int num) {
    int maxX = getmaxx();
    int maxY = getmaxy();
    int startX = (maxX - size) / 2;
    int startY = (maxY - size) / 2;
    int cellSize = size / n;

    int textX = startX + col * cellSize + cellSize / 2;
    int textY = startY + row * cellSize + cellSize / 2;

    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);

    char numText[3];
    sprintf(numText, "%d", num);
    outtextxy(textX - 15, textY - 15, numText);
}

void CuadroLatino::limpiarPantalla() {
    setbkcolor(BLACK);
    cleardevice();
    dibujarCuadroLatino(size);
}

void CuadroLatino::dibujarCeldasRecursivamente(int row, int col) {
    if (row < n) {
        if (col < n) {
            if (square[row][col] != 0) {
                dibujarTextoCelda(row, col, square[row][col]);
            }
            dibujarCeldasRecursivamente(row, col + 1);
        } else {
            dibujarCeldasRecursivamente(row + 1, 0);
        }
    }
}

bool CuadroLatino::verificarCuadroLatino() {
    for (int i = 0; i < n; i++) {
        bool* rowCheck = new bool[n];
        bool* colCheck = new bool[n];

        std::fill(rowCheck, rowCheck + n, false);
        std::fill(colCheck, colCheck + n, false);

        for (int j = 0; j < n; j++) {
            if (square[i][j] < 1 || square[i][j] > n || rowCheck[square[i][j] - 1]) {
                delete[] rowCheck;
                delete[] colCheck;
                return false;
            }
            rowCheck[square[i][j] - 1] = true;

            if (square[j][i] < 1 || square[j][i] > n || colCheck[square[j][i] - 1]) {
                delete[] rowCheck;
                delete[] colCheck;
                return false;
            }
            colCheck[square[j][i] - 1] = true;
        }

        delete[] rowCheck;
        delete[] colCheck;
    }
    return true;
}

int CuadroLatino::validarNumeros(const char* msj) {
    int num;
    while (true) {
        std::cout << msj;
        std::cin >> num;

        if (std::cin.fail() || num <= 0 || num == 2 || num == 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero positivo diferente de 2 y 6.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return num;
        }
    }
}