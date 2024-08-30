#include <iostream>
#include <vector>
template <typename T>
void ordenar(T array[], int dimension){
    for(int i = 0; i < dimension-1; i++){
        for(int j = 0; j < dimension - 1; j++){
            if(array[j]>array[j+1]){
                T auxiliar = array[j];
                array[j] = array[j+1];
                array[j+1] = auxiliar;
            }
        }
    }
}
int main(){
    int arreglo1[] = {1,8,2,5,0};
    double arreglo2[] = {2.5,3.9,7.5,0.1,5.4};
    char arreglo3[] = {'m','a','n','o','r','t'};
    int dim1 = sizeof(arreglo1)/sizeof(arreglo1[0]);
    int dim2 = sizeof(arreglo2)/sizeof(arreglo2[0]);
    int dim3 = sizeof(arreglo3)/sizeof(arreglo3[0]);
    std :: cout << "Arrays sin ordenar: " << std :: endl;    
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo1[i];
    }
    std :: cout << std :: endl;
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo2[i];
    }
    std :: cout << std :: endl;
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo3[i];
    }
    std :: cout << std :: endl;
    ordenar(arreglo1,dim1);
    ordenar(arreglo2,dim2);
    ordenar(arreglo3,dim3);
    std :: cout << "Arrays ordenados: " << std :: endl; 
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo1[i];
    }
    std :: cout << std :: endl;
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo2[i];
    }
    std :: cout << std :: endl;
    for(int i = 0; i < dim1; i++){
        std :: cout << " " << arreglo3[i];
    }
    std :: cout << std :: endl;
}