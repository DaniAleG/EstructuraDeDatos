#include <iostream>
using namespace std;


int** multiplicarMatrices(int** matriz1, int** matriz2, int nF) {
    int **matriz3 = nullptr;
    //Reserva Memoria matriz3
    matriz3 = new int*[nF];
    for(int i = 0; i < nF; i++){
        matriz3[i] = new int[nF];
    }
    //.Inicializar matriz3 en 0
    for(int i = 0; i<nF; i++){
        for(int j = 0; j<nF;j++){
            *(*(matriz3+i)+j) = 0;
        }
    }
    //Proceso multiplicacion de matrices
    for(int i = 0; i < nF ; i++){
        for(int j = 0; j < nF; j++){
            for(int k = 0; k < nF; k++){
                *(*(matriz3+i)+j) += (*(*(matriz1+i)+k))*(*(*(matriz2+k)+j));
            }
        }
    }
    return matriz3;
}

int** potencia(int** matriz1, int**matriz2, int exponente, int nF){
    //Caso base cuando el exponente es 1 devuelve la matriz1
    if(exponente == 1){
        return matriz2;
    }
    else if(exponente > 1){
        //Llamada recursiva a la funcion multiplicarMatrices
        int** matriz3 = multiplicarMatrices(matriz1, matriz2, nF);
        return potencia(matriz1,matriz3, exponente-1, nF);
    }
    else{
        return nullptr;
    }
}


void imprimir(int **matriz1, int nF){
    //Impresion matriz1
    for(int i = 0; i < nF; i++){
        for(int j = 0; j < nF; j++){
            cout << *(*(matriz1+i)+j) << " ";
        }
        cout << endl;
    }
}
int main(){
    int **matriz1, **matriz3, orden, exponente;
    // Ingresar el orden de la matriz
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> orden;
    cout << "Ingrese el exponente al que desea elevar la matriz: ";
    cin >> exponente;
    // Reservar memoria  
    matriz1 = new int*[orden];
    matriz3 = new int*[orden];
    for(int i = 0; i < orden; i++){
        matriz1[i] = new int[orden];
        matriz3[i] = new int[orden];
    }
    
    //Inicializar matriz3 en 0
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            *(*(matriz3 + i) + j) = 0;
        }
    }   
    //Ingreso de datos matriz1
    cout << "Ingrese los elementos de la matriz: " << endl;
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el elemento [" << i << "][" << j << "]: ";
            cin >> *(*(matriz1 + i) + j);
        }
    }
    matriz3 = potencia(matriz1,matriz1, exponente, orden);
    cout << "La matriz original es: " << endl;
    imprimir(matriz1, orden);
    cout << "La matriz elevada a la potencia " << exponente << " es: " << endl;
    imprimir(matriz3, orden);
}