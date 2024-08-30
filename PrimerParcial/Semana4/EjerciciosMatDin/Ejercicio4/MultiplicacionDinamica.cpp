#include <iostream>
#include <stdlib.h>
using namespace std;

void imprimir(int **matriz, int orden){
    for(int i = 0; i < orden ; i++){
        for(int j = 0; j < orden; j++){
            cout << *(*(matriz+i)+j) << " ";
        }
    cout << endl;
    }
}
void multiplicacion(int **matrizA, int **matrizB, int **resultado, int orden, int i, int j, int k){
    if(i >= orden){
        return;
    }
    if(j < orden){
        if(k < orden){
            *(*(resultado+i)+j) += (*(*(matrizA+i)+k))*(*(*(matrizB+k)+j));
            multiplicacion(matrizA,matrizB,resultado,orden,i,j,k+1);
        }else{
            multiplicacion(matrizA,matrizB,resultado,orden,i,j+1,0);
        }
    }else{
        multiplicacion(matrizA,matrizB,resultado,orden,i+1,0,0);
    }
}
int main(){
    int **matrizA, **matrizB, **resultado, orden;
    cout << "Ingrese el orden de las matrices: ";
    cin >> orden;
    //Reservar MEMORIA A
    matrizA = new int*[orden];
    matrizB = new int*[orden];
    resultado = new int*[orden];

    for(int i = 0; i< orden; i++){
        matrizA[i] = new int[orden];
        matrizB[i] = new int[orden];
        resultado[i] = new int[orden];
    }
    cout << "Ingrese la matriz 1: " << endl;
    //Ingreso de datos A
    for(int i = 0; i< orden; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el elemento [" << i <<"][" << j <<"]: ";
            cin >>*(*(matrizA+i)+j);
        }
    }

    cout << "Ingrese la matriz 2: " << endl;
    //Ingreso de datos B
    for(int i = 0; i< orden; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el elemento [" << i <<"][" << j <<"]: ";
            cin >>*(*(matrizB+i)+j);
        }
    }

    //Inicializar resultado
    for(int i = 0; i< orden; i++){
        for(int j = 0; j < orden; j++){
            *(*(resultado+i)+j) = 0;
        }
    }
    multiplicacion(matrizA,matrizB,resultado,orden,0,0,0);
    cout << "La primera matriz es: " << endl;
    imprimir(matrizA,orden);
    cout << "La segunda matriz es: " << endl;
    imprimir(matrizB, orden);
    cout << "El resultado de la multiplicacion de las matrices es: " << endl;
    imprimir(resultado,orden);
    for (int i = 0; i < orden; i++) {
        delete[] matrizA[i];
        delete[] matrizB[i];
        delete[] resultado[i];
    }
    delete[] matrizA;
    delete[] matrizB;
    delete[] resultado;
    return 0;
}