#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX 3

using namespace std;

//====================================================================================
// Application Entry Point
//====================================================================================
int main(int argc, char** argv) {
    int** mat1 = nullptr;
    int** mat2 = nullptr;
    int** matR = nullptr;

    mat1 = (int**)malloc(MAX * sizeof(int*));
    mat2 = (int**)malloc(MAX * sizeof(int*));
    matR = (int**)malloc(MAX * sizeof(int*));
    for (int j = 0; j < MAX; j++) {
        *(mat1 + j) = (int*)malloc(MAX * sizeof(int));
        *(mat2 + j) = (int*)malloc(MAX * sizeof(int));
        *(matR + j) = (int*)malloc(MAX * sizeof(int));
    }

    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            *(*(mat1 + i) + j) = rand() % 1000;
            *(*(mat2 + i) + j) = rand() % 1000;
            *(*(matR + i) + j) = 0;
        }
    }

    cout << "\nLa matriz 1 es:\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d", *(*(mat1 + i) + j));
            printf("%*s", j + 5, "");
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "\nLa matriz 2 es:\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d", *(*(mat2 + i) + j));
            printf("%*s", j + 5, "");
        }
        cout << "\n";
    }

    // Lambda para sumar matrices recursivamente
    auto sumaRecursivaMatrices = [](auto& mat1, auto& mat2, auto& matR, int f, int c, auto& lambda) -> void {
        if (f >= 0 && c >= 0) {
            matR[f][c] = mat1[f][c] + mat2[f][c];
            if (c > 0) {
                lambda(mat1, mat2, matR, f, c - 1, lambda);
            }
            if (f > 0) {
                lambda(mat1, mat2, matR, f - 1, MAX - 1, lambda);
            }
        }
    };

    // Sumar las matrices recursivamente
    sumaRecursivaMatrices(mat1, mat2, matR, MAX - 1, MAX - 1, sumaRecursivaMatrices);

    cout << "\nLa matriz R es:\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d", *(*(matR + i) + j));
            printf("%*s", j + 5, "");
        }
        cout << "\n";
    }

    // Liberar memoria
    for (int j = 0; j < MAX; j++) {
        free(*(mat1 + j));
        free(*(mat2 + j));
        free(*(matR + j));
    }
    free(mat1);
    free(mat2);
    free(matR);

    return 0;
}
