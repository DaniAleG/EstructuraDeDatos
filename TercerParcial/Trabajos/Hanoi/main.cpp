/*Universidad de las Fuerzas Armadas ESPE
            HANOI
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include "hanoi.cpp"  // Asegurate de tener el encabezado adecuado
#include <iostream>
#include <cctype> // Para toupper
#include <graphics.h>
#include <vector>
#include <string>

#define MAX_DISCOS 8
#define MAX_TORRES 5

int main() {
    int n, numTorres;
    char torreInicio, torreDestino;

    // Solicitar y validar el numero de torres
    do {
        std::cout << "Ingrese el numero de torres (maximo " << MAX_TORRES << "): ";
        std::cin >> numTorres;

        if (numTorres < 3 || numTorres > MAX_TORRES) {
            std::cerr << "Numero de torres fuera de rango. Debe ser entre 3 y " << MAX_TORRES << "." << std::endl;
        }
    } while (numTorres < 3 || numTorres > MAX_TORRES);

    // Solicitar y validar el numero de discos
    do {
        std::cout << "Ingrese el numero de discos (maximo " << MAX_DISCOS << "): ";
        std::cin >> n;

        if (n < 1 || n > MAX_DISCOS) {
            std::cerr << "Numero de discos fuera de rango. Debe ser entre 1 y " << MAX_DISCOS << "." << std::endl;
        }
    } while (n < 1 || n > MAX_DISCOS);

    // Solicitar y validar la torre inicial
    do {
        std::cout << "Ingrese la torre inicial (letra A, B, C, ...): ";
        std::cin >> torreInicio;
        torreInicio = toupper(torreInicio);

        if (torreInicio < 'A' || torreInicio >= 'A' + numTorres) {
            std::cerr << "Torre inicial no valida. Debe ser una letra entre A y " << static_cast<char>('A' + numTorres - 1) << "." << std::endl;
        }
    } while (torreInicio < 'A' || torreInicio >= 'A' + numTorres);

    // Solicitar y validar la torre destino
    do {
        std::cout << "Ingrese la torre destino (letra A, B, C, ...): ";
        std::cin >> torreDestino;
        torreDestino = toupper(torreDestino);

        if (torreDestino < 'A' || torreDestino >= 'A' + numTorres) {
            std::cerr << "Torre destino no valida. Debe ser una letra entre A y " << static_cast<char>('A' + numTorres - 1) << "." << std::endl;
        } else if (torreDestino == torreInicio) {
            std::cerr << "La torre destino no puede ser la misma que la torre inicial." << std::endl;
        }
    } while (torreDestino < 'A' || torreDestino >= 'A' + numTorres || torreInicio == torreDestino);

    // Encontrar una torre auxiliar
    char torreAuxiliar = 'A';
    for (char c = 'A'; c < 'A' + numTorres; ++c) {
        if (c != torreInicio && c != torreDestino) {
            torreAuxiliar = c;
            break;
        }
    }

    // Inicializar el estado de las torres
    std::vector<std::vector<int>> varillas(numTorres);
    for (int i = n; i > 0; --i) {
        varillas[torreInicio - 'A'].push_back(i);
    }

    // Calcular los pasos
    std::vector<std::pair<char, char>> pasos;
    torresHanoi(n, numTorres, torreInicio, torreDestino, torreAuxiliar, pasos);


    // Inicializar la ventana grafica
    initwindow(getmaxwidth(), getmaxheight(), "Torres de Hanoi");

    // Animar los pasos
    animarPasosHanoi(pasos, n, numTorres, varillas);

    // Cerrar la ventana grafica
    closegraph();

    return 0;
}
