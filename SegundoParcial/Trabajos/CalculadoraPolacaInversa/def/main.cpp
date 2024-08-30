#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <stdexcept>
#include "conversions.cpp"

enum OpcionMenu {
    INFIX_TO_POSTFIX_AND_PREFIX,
    EXIT,
    MENU_OPTIONS_COUNT
};

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    std::string opcionesMenu[MENU_OPTIONS_COUNT] = {
        "Convertir infijo a sufijo y prefijo",
        "Salir"
    };
    std::cout << "------------Conversor de expresiones------------\n";
    std::cout << "Seleccione una opcion:\n";
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        if (i == opcionSeleccionada) {
            std::cout << "> " << opcionesMenu[i] << " <" <<"\n";
        } else {
            std::cout << "   " << opcionesMenu[i] << "\n";
        }
    }
}

int main() {
    std::string expresion;
    int opcionSeleccionada = 0;
    char tecla;

    do {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();
        switch (tecla) {
        case 72: 
            if (opcionSeleccionada > 0) {
                --opcionSeleccionada;
            }
            break;
        case 80: 
            if (opcionSeleccionada < MENU_OPTIONS_COUNT - 1) {
                ++opcionSeleccionada;
            }
            break;
        case 13: 
            system("cls");
            if (opcionSeleccionada != EXIT) {
                while (true) {
                    std::cout << "Ingrese la expresion: ";
                    std::getline(std::cin, expresion);

                    expresion = insertarEspacios(expresion);
                    
                    if (!validarCaracteres(expresion)) {
                        std::cerr << "Error: La expresion contiene caracteres no permitidos. Intentelo de nuevo." << std::endl;
                        continue; 
                    }

                    bool expresionValida = false;
                    try {
                        switch (opcionSeleccionada) {
                        case INFIX_TO_POSTFIX_AND_PREFIX:
                            expresionValida = esInfijo(expresion);
                            break;

                        }
                        if (!expresionValida) {
                            throw std::invalid_argument("Entrada invalida para la opcion seleccionada.");
                        }
                        switch (opcionSeleccionada) {
                        case INFIX_TO_POSTFIX_AND_PREFIX: {
                            std::string sufijo = infijoASufijo(expresion);
                            std::string prefijo = infijoAPrefijo(expresion);
                            std::cout << "Expresion infija: " << expresion << std::endl;
                            std::cout << "--------------------------------------------------\n";
                            std::cout << "Conversion a sufijo: " << sufijo << std::endl;
                            std::cout << "Conversion a prefijo: " << prefijo << std::endl;
                            std::cout << "--------------------------------------------------\n";
                            std::cout << "Resultado: " << evaluarInfijo(expresion) << std::endl;
                            break;
                        }
                    
                        }
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    std::cout << "Presione cualquier tecla para continuar...\n";
                    _getch();
                    system("cls");
                    break;
                }
            } else {
                std::cout << "Saliendo...\n";
            }
            break;
        }

    } while (tecla != 13 || opcionSeleccionada != EXIT);

    return 0;
}
