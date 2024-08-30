#include "hanoi.h"
#include <graphics.h>
#include <fstream>
#include <iostream>
#include <conio.h> // Para _getch()

const int MAX_DISCOS = 8; // Numero maximo de discos permitido
const int MAX_TORRES = 5; // Numero maximo de torres permitido

std::string obtenerNombreColor(int colorIndex) {
    switch (colorIndex) {
        case RED: return "Rojo";
        case GREEN: return "Verde";
        case BLUE: return "Azul";
        case YELLOW: return "Amarillo";
        case CYAN: return "Cian";
        case MAGENTA: return "Magenta";
        case WHITE: return "Blanco";
        case LIGHTGRAY: return "Gris Claro";
        default: return "Desconocido";
    }
}

bool esLetraValida(char varilla, int numTorres) {
    return varilla >= 'A' && varilla < 'A' + numTorres;
}

void torresHanoi(int n, int numTorres, char deVarilla, char aVarilla, char auxVarilla, std::vector<std::pair<char, char>>& pasos) {
    if (!esLetraValida(deVarilla, numTorres) || !esLetraValida(aVarilla, numTorres) || !esLetraValida(auxVarilla, numTorres)) {
        std::cerr << "Error: Varilla no valida." << std::endl;
        return;
    }
    if (n == 1) {
        pasos.push_back({deVarilla, aVarilla});
        return;
    }
    torresHanoi(n - 1, numTorres, deVarilla, auxVarilla, aVarilla, pasos);
    pasos.push_back({deVarilla, aVarilla});
    torresHanoi(n - 1, numTorres, auxVarilla, aVarilla, deVarilla, pasos);
}

void guardarPasosEnArchivo(const std::vector<std::string>& mensajes, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    for (const auto& mensaje : mensajes) {
        archivo << mensaje << std::endl;
    }
    archivo.close();
}

void dibujarDisco(int x, int y, int ancho, int alto, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x + ancho, y + alto);
    setcolor(WHITE);
    rectangle(x, y, x + ancho, y + alto);
}

void dibujarEstadoHanoi(const std::vector<std::vector<int>>& varillas, int n, int numTorres, const std::string& mensajePaso, const std::string& mensajeDisco) {
    cleardevice();
    
    setcolor(WHITE);
    int posicionesVarillas[MAX_TORRES];
    for (int i = 0; i < numTorres; ++i) {
        posicionesVarillas[i] = 100 + i * 200;
        line(posicionesVarillas[i], 100, posicionesVarillas[i], 300);
    }

    std::vector<int> coloresDiscos = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, LIGHTGRAY};

    for (int varilla = 0; varilla < numTorres; ++varilla) {
        for (int i = varillas[varilla].size() - 1; i >= 0; --i) {
            int numDisco = varillas[varilla][i];
            int ancho = 30 + 10 * (MAX_DISCOS - numDisco); // Mayor tamaño para discos mas grandes
            int alto = 20;
            int x = posicionesVarillas[varilla] - ancho / 2;
            int y = 300 - alto * (varillas[varilla].size() - i); // Ajustar la posicion y para que los discos mas grandes esten abajo

            dibujarDisco(x, y, ancho, alto, coloresDiscos[numDisco % coloresDiscos.size()]);
        }
    }

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, 10, const_cast<char*>(mensajePaso.c_str()));
    outtextxy(10, 30, const_cast<char*>(mensajeDisco.c_str()));
}

void animarPasosHanoi(const std::vector<std::pair<char, char>>& pasos, int n, int numTorres, std::vector<std::vector<int>>& varillas) {
    int posicionesVarillas[MAX_TORRES];
    for (int i = 0; i < numTorres; ++i) {
        posicionesVarillas[i] = 100 + i * 200;
    }
    std::vector<int> coloresDiscos = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, LIGHTGRAY};

    std::vector<std::string> mensajes; // Vector para almacenar los mensajes

    // Configurar el estado inicial
    dibujarEstadoHanoi(varillas, n, numTorres, "Estado inicial", "Color del disco: Ninguno");
    std::cout << "Presione espacio para continuar..." << std::endl;
    while (true) {
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 32) // Tecla espacio
                break;
            else if (tecla == 27) // Tecla ESC
                return;
        }
    }

    // Animar los pasos
    for (const auto& paso : pasos) {
        char deVarilla = paso.first;
        char aVarilla = paso.second;

        if (!esLetraValida(deVarilla, numTorres) || !esLetraValida(aVarilla, numTorres)) {
            std::cerr << "Error: Varilla no valida en los pasos." << std::endl;
            return;
        }

        int indexDe = deVarilla - 'A';
        int indexA = aVarilla - 'A';

        // Mover el disco desde la cima hacia abajo
        int disco = varillas[indexDe].front();
        varillas[indexDe].erase(varillas[indexDe].begin());

        // Buscar la posicion correcta para insertar el disco en la torre de destino
        int pos = 0;
        while (pos < varillas[indexA].size() && varillas[indexA][pos] > disco) {
            pos++;
        }
        varillas[indexA].insert(varillas[indexA].begin() + pos, disco);

        // Actualizar y mostrar el estado
        std::string mensajeDisco = "Color del disco: " + obtenerNombreColor(coloresDiscos[disco % coloresDiscos.size()]);
        std::string mensajePaso = "Mover disco de " + std::string(1, deVarilla) + " a " + std::string(1, aVarilla);
        dibujarEstadoHanoi(varillas, n, numTorres, mensajePaso, mensajeDisco);

        // Almacenar los mensajes en el vector
        mensajes.push_back(mensajePaso);
        mensajes.push_back(mensajeDisco);

        std::cout << "Presione espacio para continuar..." << std::endl;
        while (true) {
            if (kbhit()) {
                int tecla = getch();
                if (tecla == 32) // Tecla espacio
                    break;
                else if (tecla == 27) // Tecla ESC
                    return;
            }
        }

        // Depuracion del estado de las torres
        std::cout << "Estado de las torres despues del movimiento:" << std::endl;
        for (int i = 0; i < numTorres; ++i) {
            std::cout << "Torre " << static_cast<char>('A' + i) << ": ";
            for (int disco : varillas[i]) {
                std::cout << disco << " ";
            }
            std::cout << std::endl;
        }
    }

    // Guardar los mensajes en el archivo
    guardarPasosEnArchivo(mensajes, "pasos.txt");
}