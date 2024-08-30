#include <iostream>
using namespace std;


int fibonacci(int numero, int a, int b){
    if(numero == 0){
        return 0;
    }else if(numero == 1){
        return 1;
    }
    //Recursividad por cabeza
    a = fibonacci((numero-1), a,b);
    b = fibonacci((numero-2),a,b);

    return a+b;
}   
int main(){
    int numero;
    cout << "Ingrese el numero entero: ";
    cin >> numero;
    int resultado = fibonacci(numero,0,0);
    cout << "El termino numero " << numero << " es: " << resultado << endl; 
}