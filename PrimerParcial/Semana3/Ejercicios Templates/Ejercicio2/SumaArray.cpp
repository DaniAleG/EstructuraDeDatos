#include <iostream>
template <typename T>
T sumitas(const T* array, int dimension){
    T suma = 0;
    for(int i = 0; i < dimension; i++){
        suma += array[i];
    }
    return suma;
}
int main(){
    int array1[] = {1,2,3,4,5,6};
    double array2[] = {2.5,3.2,3.5,9.7,4.0};
    std :: cout << "La suma de los datos pares del array tipo int es: " << sumitas(array1,6) << std :: endl;
    std :: cout << "La suma de los datos pares del array tipo float es: " << sumitas(array2,5) << std :: endl;
}