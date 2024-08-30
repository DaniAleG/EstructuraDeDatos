#include <iostream>
#include <stdlib.h>
using namespace std;

void sumaArray(int *arr, int tam, int &suma){
    if(tam == 0){
        suma = 0;
    }else{
        sumaArray(arr, tam-1, suma);
        suma += (*(arr + tam-1));
    }
};


int main(){
    int *array;
    // Reservar memoria
    array = new int[5];
    // Ingresa los valores
    for(int i = 0; i < 5; i++){
        std::cout << "Ingrese el valor " << i+1 << ": ";
        std::cin >> *(array + i);
    }
    

    int suma = 0;    
    sumaArray(array, 5, suma);
    std :: cout << "La suma de los elementos del arreglo es: " << suma << endl;
    return 0;
    delete[] array;
}