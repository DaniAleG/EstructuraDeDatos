#include <iostream>
#include <stdlib.h>
using namespace std;


void impresion(int **matriz1, int nF){
    //Impresion matriz1
    for(int i = 0; i < nF; i++){
        for(int j = 0; j < nF; j++){
            cout << *(*(matriz1+i)+j) << " ";
        }
        cout << endl;
    }

}
int** potencia(int** matriz1, int** matriz2, int exponente, int nF){
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
    //Caso base cuando el exponente es 1 devuelve la matriz2
    if(exponente == 1){
        return matriz2;
    }
    else if(exponente > 1){
        //Proceso multiplicacion de matrices
        for(int i = 0; i < nF ; i++){
            for(int j = 0; j < nF; j++){
                for(int k = 0; k < nF; k++){
                    *(*(matriz3+i)+j) += (*(*(matriz1+i)+k))*(*(*(matriz2+k)+j));
                }
            }
        }
    //Llamada recursiva a la funcion potencia restando 1 al exponente
    return potencia(matriz1,matriz3,exponente-1,nF);
    }
    else{
    return nullptr;
    }
}
int main(){
    int **matriz1, nF, exponente;
    //Ingreso Orden de la matriz
    cout << "Ingrese el orden de la matriz cuadrada (nxn): ";
    cin >> nF;

    //Reserva Memoria matriz1
    matriz1 = new int*[nF];
    for(int i = 0; i < nF; i++){
        matriz1[i] = new int[nF];
    }
    
    cout << "Ingreso de la matriz 1: " << endl;
    //Ingreso de datos matriz1
    for(int i = 0; i < nF; i++){
        for(int j = 0; j < nF; j++){
            cout << "Ingrese el elemento en la posicion [" << i << "][" << j<<"]: ";
            cin >> *(*(matriz1+i)+j);
        }
    }
    cout << "Ingrese el exponente: ";
    cin >> exponente;
    int **respuesta = potencia(matriz1,matriz1,exponente,nF);
    cout << "Matriz original: " << endl;
    impresion(matriz1,nF);
    cout << "La matriz elevada al exponente " << exponente <<" es: "<< endl;
    impresion(respuesta,nF);
//Borrar memoria 
for(int i = 0; i <nF; i++){
    delete[]  matriz1[i];
    delete[] respuesta[i];
}

    delete[]  matriz1;
    delete[] respuesta;
    return 0;
}