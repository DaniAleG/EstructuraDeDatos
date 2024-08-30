#include "Operaciones.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iostream>
int main() {
    system("cls");
    
    const char* menu[] = {
        "Ingresar datos",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;
Operaciones operaciones;
do {
    system("cls");
    std::cout << "\t\t.:MENU PRINCIPAL:." << std::endl;
    operaciones.printMenuMain(menu, size, currentSelection);

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
            if (currentSelection == 0) {
                operaciones.operarConjuntosMenu(0); // Ir a la parte de ingresar cadenas de texto
            } else if (currentSelection == 1) {
                std::cout << "Saliendo del programa..." << std::endl;
                return 0;
            }
            break;
    }
} while (true);

return 0;
}