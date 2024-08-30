#include "Tetris.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const char Tetris::VACIO = ' '; 

Tetris::Tetris() : posX(ANCHO / 2), posY(0) {
    tablero = new char*[ALTO];
    for (int i = 0; i < ALTO; ++i) {
        tablero[i] = new char[ANCHO];
    }
    inicializarTablero();
    generarPieza();
}

Tetris::~Tetris() {
    for (int i = 0; i < ALTO; ++i) {
        delete[] tablero[i];
    }
    delete[] tablero;
}

void Tetris::gotoxySimple(int x, int y) const {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Tetris::inicializarTablero() {
    for (int i = 0; i < ALTO; ++i) {
        for (int j = 0; j < ANCHO; ++j) {
            tablero[i][j] = VACIO;
        }
    }
}

void Tetris::imprimirTablero() const {
    gotoxySimple(0, 0);
    for (int i = 0; i < ALTO; ++i) {
        cout << "|";
        for (int j = 0; j < ANCHO; ++j) {
            cout << tablero[i][j];
        }
        cout << "|" << endl;
    }
    cout << string(ANCHO + 2, '-') << endl;
}

bool Tetris::verificarColision(int x, int y) const {
    return y >= ALTO || x < 0 || x >= ANCHO || tablero[y][x] != VACIO;
}

void Tetris::fusionarPieza(char pieza, int x, int y) {
    if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
        tablero[y][x] = pieza;
    }
}

void Tetris::eliminarPieza(int x, int y) {
    if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
        tablero[y][x] = VACIO;
    }
}

std::string Tetris::aMayusculas(const std::string& str) const {
    std::string strMayusculas = str;
    for (char& c : strMayusculas) {
        c = toupper(c);
    }
    return strMayusculas;
}

void Tetris::generarPieza() {
    piezaActual = 'A' + rand() % 26;
    posX = ANCHO / 2;
    posY = 0;
}

void Tetris::moverIzquierda() {
    if (!verificarColision(posX - 1, posY)) {
        posX--;
    }
}

void Tetris::moverDerecha() {
    if (!verificarColision(posX + 1, posY)) {
        posX++;
    }
}

void Tetris::moverAbajo() {
    if (!verificarColision(posX, posY + 1)) {
        posY++;
    } else {
        fusionarPieza(piezaActual, posX, posY);
        if (posY + 1 < ALTO && tablero[posY + 1][posX] == piezaActual) {
            eliminarPieza(posX, posY);
            eliminarPieza(posX, posY + 1);
            gotoxySimple(posX, posY);
            cout << VACIO;
            gotoxySimple(posX, posY + 1);
            cout << VACIO;
        }
        generarPieza();
        if (verificarColision(posX, posY)) {
            system("cls");
            cout << "Juego terminado. Presiona cualquier tecla para continuar...";
            _getch();
            exit(0);
        }
    }
}

void Tetris::iniciar(ListaSimple<std::string>& lista) {
    inicializarTablero();
    Nodo<std::string>* aux = lista.getPrimero();
    int y = ALTO - 1;
    int x = 0;
    while (aux != nullptr) {
        std::string nombre = aMayusculas(aux->getValor());
        for (char c : nombre) {
            if (x < ANCHO) {
                tablero[y][x++] = c;
            }
        }
        if (x < ANCHO) {
            tablero[y][x++] = VACIO;
        }
        aux = aux->getSiguiente();
    }
    srand(time(0));
    generarPieza();
    bool jugando = true;
    DWORD ultimoTiempoMovimiento = GetTickCount();
    bool caidaRapida = false;
    while (jugando) {
        imprimirTablero();
        gotoxySimple(posX, posY);
        cout << piezaActual;
        if (_kbhit()) {
            char tecla = _getch();
            gotoxySimple(posX, posY);
            cout << VACIO;
            switch (tecla) {
                case 75: 
                    moverIzquierda();
                    break;
                case 77: 
                    moverDerecha();
                    break;
                case 80: 
                    caidaRapida = true;
                    break;
                case 27: 
                    jugando = false;
                    break;
            }
            gotoxySimple(posX, posY);
            cout << piezaActual;
        }
        Sleep(100);
        if (caidaRapida || GetTickCount() - ultimoTiempoMovimiento >= 1000) {
            ultimoTiempoMovimiento = GetTickCount();
            caidaRapida = false;
            moverAbajo();
        }
    }
    system("cls");
    cout << "Juego terminado. Presiona cualquier tecla para salir...";
    _getch();
    exit(0);
}

