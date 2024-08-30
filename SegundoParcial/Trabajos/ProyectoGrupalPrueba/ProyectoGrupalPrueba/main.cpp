#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include "TipoOrdenamiento.h"
#include "..\ProyectoGrupalPrueba(2)\ListaSimple\mainSimple.cpp"
#include "..\ProyectoGrupalPrueba(2)\ListaDoble\mainDoble.cpp"
#include "..\ProyectoGrupalPrueba(2)\ListaCircular\mainCircular.cpp"

using namespace std;

void gotoxyMain(int x, int y);
void printMenuMain(const char* menu[], int size, int currentSelection);
void menuOrdenamiento(int listType);

int main() {
    system("cls");

    const char* menu[] = {
        "Menu de Registro Lista Simple",
        "Menu de Registro Lista Doble",
        "Menu de Registro Lista Circular",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU PRINCIPAL:." << endl;
        printMenuMain(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                if (currentSelection == 3) {
                    cout << "Saliendo del programa..." << endl;
                    exit(0); 
                } else {
                    menuOrdenamiento(currentSelection);
                }
                break;
        }
    } while (true);

    return 0;
}

void gotoxyMain(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenuMain(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; ++i) {
        if (i == currentSelection) {
            cout << "> " << menu[i] << " <" << endl;
        } else {
            cout << "  " << menu[i] << endl;
        }
    }
}

void menuOrdenamiento(int listType) {
    const char* ordenMenu[] = {
        "Ordenamiento por Intercambio",
        "Odenamiento por Burbuja",
        "Ordenamiento por QuickSort",
        "Ordenamiento Shellsort",
        "Ordenamiento por Distribucion",
        "Ordenamiento por Radix",
        "Regresar"
    };
    int size = sizeof(ordenMenu) / sizeof(ordenMenu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU DE ORDENAMIENTO:." << endl;
        printMenuMain(ordenMenu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                if (currentSelection == 6) {
                    return; 
                } else {
                    TipoOrdenamiento tipoOrden;
                    if (currentSelection == 0) {
                        tipoOrden = INTERCAMBIO;
                    } else if (currentSelection == 1) {
                        tipoOrden = BURBUJA;
                    } else if (currentSelection == 2) {
                        tipoOrden = QUICKSORT;
                    } else if (currentSelection == 3) {
                        tipoOrden = SHELLSORT;
                    } else if (currentSelection == 4) {
                        tipoOrden = DISTRIBUCION;
                    } else if (currentSelection == 5) {
                        tipoOrden = RADIX;
                    }
                    switch (listType) {
                        case 0:
                            mainSimple(tipoOrden);
                            break;
                        case 1:
                            mainDoble(tipoOrden);
                            break;
                        case 2:
                            mainCircular(tipoOrden);
                            break;
                    }
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}
