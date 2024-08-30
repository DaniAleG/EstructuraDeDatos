#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Tolerancia para comparar con cero (para evitar problemas con números flotantes)
const double EPSILON = 1e-9;

// Función para imprimir una matriz
void imprimirMatriz(const vector<vector<double>>& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            // Ajuste para evitar imprimir -0
            if (fabs(elemento) < EPSILON) {
                cout << "0.0000" << " ";
            } else {
                cout << fixed << setprecision(4) << elemento << " ";
            }
        }
        cout << endl;
    }
}
// Función para intercambiar dos filas en una matriz
void intercambiarFilas(vector<vector<double>>& matriz, int fila1, int fila2) {
    swap(matriz[fila1], matriz[fila2]);
}

// Función para normalizar una fila
void normalizarFila(vector<vector<double>>& matriz, int fila, int col) {
    double divisor = matriz[fila][col];
    if (fabs(divisor) > EPSILON) {
        for (int i = 0; i < matriz[fila].size(); ++i) {
            matriz[fila][i] /= divisor;
            // Ajuste para evitar -0
            if (fabs(matriz[fila][i]) < EPSILON) {
                matriz[fila][i] = 0;
            }
        }
    }
}

// Función para eliminar el elemento en la columna 'col' de todas las filas excepto la 'fila'
void eliminarColumna(vector<vector<double>>& matriz, int fila, int col) {
    for (int i = 0; i < matriz.size(); ++i) {
        if (i != fila) {
            double factor = matriz[i][col];
            for (int j = 0; j < matriz[i].size(); ++j) {
                matriz[i][j] -= factor * matriz[fila][j];
                // Ajuste para evitar -0
                if (fabs(matriz[i][j]) < EPSILON) {
                    matriz[i][j] = 0;
                }
            }
        }
    }
}

// Función para encontrar la fila con el máximo valor absoluto en la columna 'col' a partir de la fila 'filaInicio'
int encontrarFilaMaxima(const vector<vector<double>>& matriz, int filaInicio, int col) {
    int filaMaxima = filaInicio;
    for (int i = filaInicio + 1; i < matriz.size(); ++i) {
        if (fabs(matriz[i][col]) > fabs(matriz[filaMaxima][col])) {
            filaMaxima = i;
        }
    }
    return filaMaxima;
}

// Función recursiva para convertir la matriz en su forma escalonada reducida por filas
void gaussJordanRecursivo(vector<vector<double>>& matriz, int numFilas, int numCols) {
    // Caso base: Si hemos recorrido todas las filas o columnas, detener la recursión
    if (numFilas == matriz.size() || numCols == matriz[0].size()) {
        return;
    }

    // Encontrar la fila con el valor máximo en la columna actual
    int filaMaxima = encontrarFilaMaxima(matriz, numFilas, numCols);

    // Intercambiar la fila actual con la fila del valor máximo
    if (filaMaxima != numFilas) {
        intercambiarFilas(matriz, numFilas, filaMaxima);
    }

    // Normalizar la fila actual
    normalizarFila(matriz, numFilas, numCols);

    // Eliminar el valor en la columna actual de todas las demás filas
    eliminarColumna(matriz, numFilas, numCols);

    // Llamar recursivamente a la función para la siguiente fila y columna
    gaussJordanRecursivo(matriz, numFilas + 1, numCols + 1);
}



int main() {
    int n;
    cout << "Ingrese el tamanio de la matriz (n x n): ";
    cin >> n;

    vector<vector<double>> matriz(n, vector<double>(n));

    cout << "Ingrese los valores de la matriz:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matriz[i][j];
        }
    }

    cout << "Matriz original:" << endl;
    imprimirMatriz(matriz);

    gaussJordanRecursivo(matriz,0,0);

    cout << "Matriz transformada en identidad:" << endl;
    imprimirMatriz(matriz);

    return 0;
}
