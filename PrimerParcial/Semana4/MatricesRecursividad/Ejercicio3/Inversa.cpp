#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir una matriz
void imprimirMatriz(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para calcular el determinante de una submatriz
double determinanteSubmatriz(const vector<vector<double>>& matriz) {
    int n = matriz.size();

    if (n == 1) {
        return matriz[0][0];
    }

    double det = 0;
    int signo = 1;

    for (int i = 0; i < n; ++i) {
        vector<vector<double>> submatriz(n - 1, vector<double>(n - 1));

        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (k < i) {
                    submatriz[j - 1][k] = matriz[j][k];
                } else if (k > i) {
                    submatriz[j - 1][k - 1] = matriz[j][k];
                }
            }
        }

        det += signo * matriz[0][i] * determinanteSubmatriz(submatriz);
        signo = -signo;
    }

    return det;
}

// Función para calcular la inversa de una matriz 3x3 utilizando recursividad
vector<vector<double>> inversaMatrizRecursiva(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<vector<double>> inversa(n, vector<double>(n));

    // Calcular el determinante de la matriz
    double det = determinanteSubmatriz(matriz);

    if (det == 0) {
        cout << "La matriz no tiene inversa." << endl;
        return inversa;
    }

    // Calcular la matriz adjunta
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<vector<double>> submatriz(n - 1, vector<double>(n - 1));

            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    for (int l = 0; l < n; ++l) {
                        if (l != j) {
                            submatriz[k < i ? k : k - 1][l < j ? l : l - 1] = matriz[k][l];
                        }
                    }
                }
            }

            inversa[j][i] = determinanteSubmatriz(submatriz) * ((i + j) % 2 == 0 ? 1 : -1) / det;
        }
    }

    return inversa;
}

int main() {
    // Solicitar al usuario que ingrese los elementos de la matriz 3x3
    vector<vector<double>> matriz(3, vector<double>(3));
    cout << "Ingrese los elementos de la matriz 3x3:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> matriz[i][j];
        }
    }

    cout << "Matriz original:" << endl;
    imprimirMatriz(matriz);
    // Calcular la inversa de la matriz
    vector<vector<double>> inversa = inversaMatrizRecursiva(matriz);

    // Imprimir la matriz inversa
    cout << "La matriz inversa es:" << endl;
    imprimirMatriz(inversa);

    return 0;
}
