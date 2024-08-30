#include "n_reinas.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <functional>

std::ofstream abrirArchivoRegistro(int n) {
    std::ofstream archivo("registro_n_reinas_" + std::to_string(n) + ".txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de registro.\n";
        exit(1);
    }
    return archivo;
}

void escribirEnRegistro(std::ofstream& archivo, const std::string& mensaje) {
    archivo << mensaje << std::endl;
}

void cerrarArchivoRegistro(std::ofstream& archivo) {
    archivo.close();
}

bool esValida(const std::vector<int>& solucion, int fila, int columna, std::ofstream& archivo, bool registrar) {
    std::function<bool(int)> verificarColumnaRec = [&](int i) -> bool {
        if (i == fila) {
            return true;
        }

        if (solucion[i] == columna || 
            solucion[i] - columna == i - fila || 
            solucion[i] - columna == fila - i) {
            if (registrar) {
                escribirEnRegistro(archivo, "Columna " + std::to_string(columna) + " en fila " + std::to_string(fila) + " no es válida.");
            }
            return false;
        }

        return verificarColumnaRec(i + 1);
    };

    bool esValida = verificarColumnaRec(0);

    if (registrar && esValida) {
        escribirEnRegistro(archivo, "Columna " + std::to_string(columna) + " en fila " + std::to_string(fila) + " es válida.");
    }

    return esValida;
}

void resolverNReinasRec(int n, std::vector<int>& solucion, int fila, std::vector<std::vector<int>>& soluciones, std::ofstream& archivo, bool registrar) {
    if (fila == n) {
        soluciones.push_back(solucion);
        if (registrar) {
            escribirEnRegistro(archivo, "Solución encontrada: " + std::to_string(solucion.size()));
            escribirEnRegistro(archivo, "Solución: ");
            for (int i = 0; i < n; ++i) {
                escribirEnRegistro(archivo, "Fila " + std::to_string(i) + ": Columna " + std::to_string(solucion[i]));
            }
        }
        return;
    }

    std::function<void(int)> probarColumnasRec = [&](int columna) {
        if (columna == n) {
            return;
        }

        if (esValida(solucion, fila, columna, archivo, registrar)) {
            solucion[fila] = columna;
            resolverNReinasRec(n, solucion, fila + 1, soluciones, archivo, registrar);
        }

        probarColumnasRec(columna + 1);
    };

    probarColumnasRec(0);
}

std::vector<std::vector<int>> generarTodasLasSoluciones(int n, std::ofstream& archivo) {
    std::vector<std::vector<int>> soluciones;
    std::vector<int> solucion(n, -1);
    escribirEnRegistro(archivo, "Inicio de la generación de soluciones.");
    resolverNReinasRec(n, solucion, 0, soluciones, archivo, false);
    escribirEnRegistro(archivo, "Generación de soluciones finalizada.");
    return soluciones;
}

std::vector<int> seleccionarSolucionAleatoria(const std::vector<std::vector<int>>& soluciones, std::ofstream& archivo) {
    if (soluciones.empty()) {
        std::cerr << "No se encontraron soluciones.\n";
        return std::vector<int>();
    }

    unsigned int semilla = static_cast<unsigned int>(std::time(nullptr));
    std::srand(semilla);

    int max = static_cast<int>(soluciones.size()) - 1;
    int index = std::rand() % (max + 1);

    escribirEnRegistro(archivo, "Selección de solución aleatoria: Índice " + std::to_string(index) + " de " + std::to_string(soluciones.size()) + " soluciones.");
    return soluciones[index];
}

std::vector<int> resolverNReinas(int n) {
    std::ofstream archivo = abrirArchivoRegistro(n);
    std::vector<std::vector<int>> soluciones = generarTodasLasSoluciones(n, archivo);
    std::vector<int> solucionAleatoria = seleccionarSolucionAleatoria(soluciones, archivo);

    std::vector<int> solucionActual(n, -1);
    escribirEnRegistro(archivo, "Proceso para encontrar la solución aleatoria seleccionada:");
    std::vector<std::vector<int>> emptyVector;
    resolverNReinasRec(n, solucionActual, 0, emptyVector, archivo, true);

    cerrarArchivoRegistro(archivo);
    return solucionAleatoria;
}
