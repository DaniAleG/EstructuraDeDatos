#include <iostream>
#include <stdlib.h>
using namespace std;

void imprimir(int** matriz, int orden){
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            cout << *(*(matriz+i)+j) <<" ";
        }
        cout << endl;
    }
}
void recursivo(int** matriz, int** respuesta, int orden, int fila, int columna){
    if (fila == orden) {
        // Hemos terminado de procesar todas las filas
        return;
    }
    if (columna == orden) {
        // Hemos terminado de procesar todas las columnas en la fila actual, pasamos a la siguiente fila
        recursivo(matriz, respuesta, orden, fila + 1, 0);
        return;
    }
    // Transponemos el elemento actual
    *(*(respuesta+columna)+fila) = *(*(matriz+fila)+columna);
    // Llamamos recursivamente para el siguiente elemento en la misma fila
    recursivo(matriz, respuesta, orden, fila, columna + 1);
}
int** transpuesta(int** matriz, int orden){
// Crear matriz resultado
    int** resultado = new int*[orden];
    // Reservar memoria matriz resultado
    for (int i = 0; i < orden; i++) {
        resultado[i] = new int[orden];
    }
    // Llamamos a la función recursiva para llenar la matriz transpuesta
    recursivo(matriz, resultado, orden, 0, 0);
    return resultado;
}
int main(){
    int **matriz, orden, **resultado;
    cout << "Ingrese el orden de la matriz: ";
    cin >> orden;

    //Reservar memoria para la matriz
    matriz = new int*[orden];
    for(int i = 0; i < orden; i++){
        matriz[i] = new int[orden];
    }
    //Ingreso de datos matriz de orden n
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el elemento [" << i << "][" << j <<"]: ";
            cin >> *(*(matriz+i)+j);
        }
    }
    resultado = transpuesta(matriz,orden);
    cout << "La matriz original es: " << endl;
    imprimir(matriz,orden);
    cout << "La matriz transpuesta es: " << endl;
    imprimir(resultado,orden);
}