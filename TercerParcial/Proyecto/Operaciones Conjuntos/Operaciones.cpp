#include "Operaciones.h"
#include "Dibujar.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;
void Operaciones::gotoxyMain(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Operaciones::printMenuMain(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; i++) {
        if (i == currentSelection) {
            std::cout << "> " << menu[i] << std::endl;
        } else {
            std::cout << "  " << menu[i] << std::endl;
        }
    }
}

void Operaciones::operarConjuntosMenu(int conjuntoType) {
    Dibujar dibujar;
    const char* operMenu[] = {
        "Union",
        "Interseccion",
        "Diferencia",
        "Diferencia Simetrica",
        "Complemento",
        "Regresar"
    };
    int size = sizeof(operMenu) / sizeof(operMenu[0]);
    int currentSelection = 0;
    int key;

    ListaSimple<string> A_str, B_str;

    cout << "Conjunto A (cadenas de texto)" << endl;
    ingresarConjunto(A_str);
    cout << "Conjunto B (cadenas de texto)" << endl;
    ingresarConjunto(B_str);

    do {
        system("cls");
        cout << "\t\t.:MENU DE OPERACIONES:." << endl;
        printMenuMain(operMenu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: // Flecha abajo
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: // Enter
                if (currentSelection == 5) {
                    return; // Regresar al menu principal
                } else {
                    switch (currentSelection) {
                        case 0: mostrarUnion(A_str, B_str); dibujar.dibujarUnion(A_str, B_str); break;
                        case 1: mostrarInterseccion(A_str, B_str); dibujar.dibujarInterseccion(A_str, B_str); break;
                        case 2: mostrarDiferencia(A_str, B_str); dibujar.dibujarDiferencia(A_str, B_str); break;
                        case 3: mostrarDiferenciaSimetrica(A_str, B_str); dibujar.dibujarDiferenciaSimetrica(A_str, B_str); break;
                        case 4: mostrarComplemento(A_str, B_str); dibujar.dibujarComplemento(A_str, B_str); break;
                    }
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}

template <typename T>
void Operaciones::ingresarConjunto(ListaSimple<T>& conjunto) {
    const char* opciones[] = {"Si", "No"};
    int size = sizeof(opciones) / sizeof(opciones[0]);
    int currentSelection = 0;
    int key;

    do {
        T elemento;
        std::cout << "Ingrese un elemento: ";
        std::cin >> elemento;
        std::cin.ignore();

        if (conjunto.buscar(elemento) != nullptr) {
            std::cout << "El elemento " << elemento << " ya está en el conjunto. Intente de nuevo." << std::endl;
            _getch();
        } else {
            conjunto.insertar(elemento);
        }

        do {
            system("cls");
            std::cout << "¿Desea agregar otro elemento?" << std::endl;
            printMenuMain(opciones, size, currentSelection);

            key = _getch();

            switch (key) {
                case 72: // Flecha arriba
                    if (currentSelection > 0) {
                        currentSelection--;
                    }
                    break;
                case 80: // Flecha abajo
                    if (currentSelection < size - 1) {
                        currentSelection++;
                    }
                    break;
                case 13: // Enter
                    if (currentSelection == 1) { // "No"
                        return; // Salir del bucle
                    }
                    break;
            }
        } while (key != 13); // Esperar a que se presione Enter para continuar
    } while (true);
}

template <typename T>
void Operaciones::mostrarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> unionAB = A.unionList(B);
    std::cout << "Union: ";
    unionAB.mostrar();
}

template <typename T>
void Operaciones::mostrarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> interseccionAB = A.interseccion(B);
    std::cout << "Interseccion: ";
    interseccionAB.mostrar();
}

template <typename T>
void Operaciones::mostrarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaAB = A.diferencia(B, true);
    ListaSimple<T> diferenciaBA = A.diferencia(B, false);
    std::cout << "Diferencia A - B: ";
    diferenciaAB.mostrar();
    std::cout << "Diferencia B - A: ";
    diferenciaBA.mostrar();
}

template <typename T>
void Operaciones::mostrarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaSimetrica = A.diferenciaSimetrica(B);
    std::cout << "Diferencia Simetrica: ";
    diferenciaSimetrica.mostrar();
}

template <typename T>
void Operaciones::mostrarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> complementoAB = A.complemento(B, true);
    ListaSimple<T> complementoBA = B.complemento(A, true);
    std::cout << "Complemento A - B: ";
    complementoAB.mostrar();
    std::cout << "Complemento B - A: ";
    complementoBA.mostrar();
}