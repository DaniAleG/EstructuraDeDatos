#include <iostream>
using namespace std;

// Función auxiliar que realiza la recursión de cola
int multiplicarElementos(int* array, int n, int contador, int acumulador) {
    // Caso base: si hemos alcanzado el final del array
    if (contador == n) {
        return acumulador;
    }
    
    // Llamada recursiva de cola
    return multiplicarElementos(array, n, contador + 1, acumulador * array[contador]);
}



int main() {
    int n;
    cout << "Introduce el numero de elementos del array: ";
    cin >> n;

    int *arr;
    //Reservar memoria
    arr = new int[n];

    cout << "Introduce los elementos del array: ";
    for (int i = 0; i < n; ++i) {
        cin >> *(arr + i);
    }
    
    int resultado = multiplicarElementos(arr, n,0,1);
    cout << "El producto de los elementos del array es: " << resultado << endl;
    
    return 0;
}
