#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX 3

using namespace std;

//====================================================================================
// Application Entry Point
//====================================================================================
int main() {
    int mat1[MAX][MAX], mat2[MAX][MAX];
    srand(static_cast<unsigned>(time(NULL)));

    // Inicializar las matrices con valores aleatorios
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            mat1[i][j] = rand() % 10;
            mat2[i][j] = rand() % 10;
        }
    }

    // Imprimir las matrices
    cout << "Matrix 1:" << endl;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            cout << mat1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matrix 2:" << endl;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            cout << mat2[i][j] << "\t";
        }
        cout << endl;
    }

    // Lambda para sumar matrices recursivamente
    auto sumaRecursivaMatrices = [](auto& mat1, auto& mat2, auto f, auto c, auto& lambda) -> int {
        if (f == 0 && c == 0) {
            return mat1[f][c] + mat2[f][c];
        } else {
            if (f > -1) {
                c--;
                if (c >= -1) {
                    return mat1[f][c + 1] + mat2[f][c + 1] + lambda(mat1, mat2, f, c, lambda);
                }
                return lambda(mat1, mat2, f - 1, MAX - 1, lambda);
            }
        }
        return 0; // Fallback return (shouldn't reach here)
    };

    cout << "Suma de Matrices es: " << sumaRecursivaMatrices(mat1, mat2, MAX - 1, MAX - 1, sumaRecursivaMatrices) << endl;

    return 0;
}
