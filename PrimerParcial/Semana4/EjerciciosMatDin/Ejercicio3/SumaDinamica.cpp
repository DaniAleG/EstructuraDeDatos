#include <iostream>
#include <stdlib.h>
using namespace std;


void imprimir(int** matriz, int nFilas, int nColumnas){
    for(int i = 0; i < nFilas; i++){
        for(int j = 0; j < nColumnas; j++){
            cout << *(*(matriz+i)+j) <<" ";
        }
        cout << endl;
    }
}
void sumar(int** matriz1,int** matriz2,int** respuesta, int fila, int columna, int nFilas, int nColumnas){
    // Caso base: si hemos llegado al final de la matriz, retornamos
    if (fila == nFilas)
        return;

    // Sumar los elementos correspondientes y guardar el resultado en la matriz resultado
    *(*(respuesta+fila)+columna)=(*(*(matriz1+fila)+columna))+(*(*(matriz2+fila)+columna));

    // Mover a la siguiente columna
    if (columna + 1 < nColumnas){
        sumar(matriz1, matriz2, respuesta, fila, columna + 1, nFilas, nColumnas);
    }
    // Mover a la siguiente fila si hemos llegado al final de la fila actual
    else
        sumar(matriz1, matriz2, respuesta, fila + 1, 0, nFilas, nColumnas);
}
int main(){
    int **matriz1, **matriz2, nFilas, nColumnas, **respuesta;
    cout << "Ingrese el numero de filas: ";
    cin >> nFilas;
    cout << "Ingrese el numero de columnas: ";
    cin >> nColumnas;
    //Reservar memoria matriz1
    matriz1 = new int*[nFilas];
    for(int i = 0; i<nFilas; i++){
        matriz1[i] = new int[nColumnas];
    }
    //Reservar memoria matriz2
    matriz2 = new int*[nFilas];
    for(int i = 0; i<nFilas; i++){
        matriz2[i] = new int[nColumnas];
    }
    //Ingreso matriz1
    cout << "Ingrese la matriz 1: " << endl;
    for(int i = 0; i < nFilas; i++){
        for(int j = 0; j < nColumnas; j++){
            cout << "Ingrese el elemento [" << i << "]["<< j << "]: ";
            cin >> *(*(matriz1+i)+j);
        }
    }
    //Ingreso matriz2
    cout << "Ingrese la matriz 2: " << endl;
    for(int i = 0; i < nFilas; i++){
        for(int j = 0; j < nColumnas; j++){
            cout << "Ingrese el elemento [" << i << "]["<< j << "]: ";
            cin >> *(*(matriz2+i)+j);
        }
    }
        //Reservar memoria respuesta
    respuesta = new int*[nFilas];
    for(int i = 0; i < nFilas; i++){
        respuesta[i] = new int[nColumnas];
    }
    //Inicializar en 0
    for(int i = 0; i < nFilas; i++){
        for(int j = 0; j < nColumnas; j++){
            *(*(respuesta+i)+j) = 0;
        }
    }
    sumar(matriz1,matriz2,respuesta,0,0, nFilas,nColumnas);
    cout << "La matriz 1 es: " << endl;
    imprimir(matriz1,nFilas,nColumnas);
    cout << "La matriz 2 es: " << endl;
    imprimir(matriz2,nFilas,nColumnas);
    cout << "El resultado de la suma es: " << endl;
    imprimir(respuesta,nFilas,nColumnas);

}