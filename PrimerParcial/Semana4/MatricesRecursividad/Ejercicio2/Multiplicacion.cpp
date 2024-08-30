#include <iostream>
using namespace std;

// Función para imprimir una matriz 3x3
void imprimir(int matriz[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std :: cout << matriz[i][j] << " ";
        }
        std :: cout <<  std :: endl;
    }
}

// Función recursiva para multiplicar matrices
void multiplicacion(int A[3][3], int B[3][3], int C[3][3], int i, int j, int k) {
    // Caso base
    if (i >= 3) return;

    if (j < 3) {
        if (k < 3) {
            C[i][j] += A[i][k] * B[k][j];
            multiplicacion(A, B, C, i, j, k + 1);
        } else {
            multiplicacion(A, B, C, i, j + 1, 0);
        }
    } else {
        multiplicacion(A, B, C, i + 1, 0, 0);
    }
}

int main() {
    int matrizA[3][3], matrizB[3][3], matrizResultado[3][3] = {0};
    // Ingreso de los valores a las dos matrices    
    cout << "Ingrese los elementos de la matriz A (3x3):" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std ::cin >> matrizA[i][j];
        }
    }
    std :: cout << "La matriz A ingresada es: " << std ::endl;
    imprimir(matrizA);

    cout << "Ingrese los elementos de la matriz B (3x3):" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std :: cin >> matrizB[i][j];
        }
    }
    std :: cout << "La matriz B ingresada es: " << std ::endl;
    imprimir(matrizB);

    // Llamar a la función recursiva para multiplicar matrices
    multiplicacion(matrizA, matrizB, matrizResultado, 0, 0, 0);

    // Imprimiendo la matriz resultado
    std :: cout << "Resultado de la multiplicacion de las matrices A y B es:" << std :: endl;
    imprimir(matrizResultado);

    return 0;
}