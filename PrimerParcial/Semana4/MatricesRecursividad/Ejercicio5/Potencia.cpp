#include <iostream>

using namespace std;

typedef int** Matriz;

// Función para crear una matriz dinámica
Matriz crearMatriz(int n) {
    Matriz matriz = new int*[n];
    for (int i = 0; i < n; ++i) {
        matriz[i] = new int[n];
    }
    return matriz;
}

// Función para eliminar una matriz dinámica
void eliminarMatriz(Matriz matriz, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Función para copiar una matriz
Matriz copiarMatriz(const Matriz& A, int n) {
    Matriz copia = crearMatriz(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            copia[i][j] = A[i][j];
        }
    }
    return copia;
}

// Función para multiplicar dos matrices
Matriz operarMatriz(const Matriz& A, const Matriz& B, int n, bool esPotencia, int exponente) {
    if (esPotencia) {
        if (exponente == 1) {
            return copiarMatriz(A, n);
        } else if (exponente % 2 == 0) {
            Matriz mitad = operarMatriz(A, B, n, true, exponente / 2);
            Matriz resultado = operarMatriz(mitad, mitad, n, false, 0);
            eliminarMatriz(mitad, n);
            return resultado;
        } else {
            Matriz temp = operarMatriz(A, B, n, true, exponente - 1);
            Matriz resultado = operarMatriz(A, temp, n, false, 0);
            eliminarMatriz(temp, n);
            return resultado;
        }
    } else {
        Matriz C = crearMatriz(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }
}

// Función para imprimir una matriz
void imprimirMatriz(const Matriz& A, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese el tamanio de la matriz cuadrada (n x n): ";
    cin >> n;

    Matriz A = crearMatriz(n);
    cout << "Ingrese los elementos de la matriz:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    int exponente;
    cout << "Ingrese el exponente: ";
    cin >> exponente;

    cout << "Matriz original:" << endl;
    imprimirMatriz(A, n);

    Matriz resultado = operarMatriz(A, A, n, true, exponente);

    cout << "Matriz elevada a la potencia " << exponente << ":" << endl;
    imprimirMatriz(resultado, n);

    eliminarMatriz(A, n);
    eliminarMatriz(resultado, n);

    return 0;
}
