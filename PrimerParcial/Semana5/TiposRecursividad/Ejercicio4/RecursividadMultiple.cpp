#include <iostream>
#include <stdlib.h>
using namespace std;

void multiplicarMatrices(int**  matrizA, int** matrizB, int** matrizC, int orden, int i, int j, int k){
    if(i >= orden){
        return;
    }
    if(j < orden){

        if(k < orden){
            *(*(matrizC+i)+j) += (*(*(matrizA+i)+k))*(*(*(matrizB+k)+j));
            multiplicarMatrices(matrizA,matrizB,matrizC,orden,i,j,k+1);
        }else{
            multiplicarMatrices(matrizA,matrizB,matrizC,orden,i,j+1,0);
        }
    }else{
        multiplicarMatrices(matrizA,matrizB,matrizC,orden,i+1,0,0);
    }
    
}
void imprimirMatriz(int** matriz, int orden){
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            cout << *(*(matriz+i)+j) << " ";
        }
        cout << endl;
    }
}
int main(){
    int **matrizA, **matrizB, **matrizC, orden;
    cout << "Ingrese el orden de las matrices: ";
    cin >> orden;
    //Reservar Memoria
    matrizA = new int*[orden];
    matrizB = new int*[orden];
    matrizC = new int*[orden];
    for(int i = 0 ; i< orden; i++){
        matrizA[i] = new int[orden]; 
        matrizB[i] = new int[orden];
        matrizC[i] = new int[orden];    
    }
    //Inicializar matriz C
    for (int i = 0; i < orden ; i++){
        for(int j = 0; j < orden; j++){
            *(*(matrizC+i)+j) = 0;
        }
    }
    //Ingreso de datos matriz A y B
    cout << "Ingrese los datos de la primera matriz: " << endl;
    for (int i = 0; i < orden ; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el dato de la posicion [" << i << "][" << j << "]: ";
            cin >> *(*(matrizA+i)+j);
        }
    }
    cout << "Ingrese los datos de la segunda matriz: " << endl;
    for (int i = 0; i < orden ; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el dato de la posicion [" << i << "][" << j << "]: ";
            cin >> *(*(matrizB+i)+j);
        }
    }
    multiplicarMatrices(matrizA,matrizB,matrizC,orden,0,0,0);
    cout << "La primera matriz es: " << endl;
    imprimirMatriz(matrizA, orden);
    cout << "La segunda matriz es: " << endl;
    imprimirMatriz(matrizB, orden);
    cout << "La matriz resultante es: " << endl;
    imprimirMatriz(matrizC,orden);
}