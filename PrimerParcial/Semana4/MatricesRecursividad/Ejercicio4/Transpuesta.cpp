#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir la matriz
void imprimir(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int elem : fila) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Función recursiva para calcular la transpuesta de una matriz
void transponer(vector<vector<int>>& matriz, int i, int j) {
    if (i == matriz.size() - 1 && j == matriz.size() - 1) {
        return; // Caso base: hemos llegado al final de la matriz
    }
    swap(matriz[i][j], matriz[j][i]); // Intercambiar elementos
    if (j == matriz.size() - 1) {
        transponer(matriz, i + 1, i + 1); // Avanzar a la siguiente fila
    } else {
        transponer(matriz, i, j + 1); // Avanzar a la siguiente columna
    }
}

int main() {
    int n;
    cout << "Ingrese el tamanio de la matriz cuadrada (nxn): ";
    cin >> n;

    // Inicializar la matriz con ceros
    vector<vector<int>> matriz(n, vector<int>(n, 0));

    cout << "Ingrese los elementos de la matriz:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matriz[i][j];
        }
    }

    cout << "Matriz original:" << endl;
    imprimir(matriz);

    transponer(matriz, 0, 0);

    cout << "Transpuesta de la matriz:" << endl;
    imprimir(matriz);

    return 0;
}
