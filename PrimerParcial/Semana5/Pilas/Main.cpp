#include <iostream>
#include <conio.h>
#include <stack> 
#include <vector> 
#include "RecursionPilas.cpp"
using namespace std;

int main(){
    stack<int> pila;
    RecursionPilas objeto(pila);
    vector<int> elementos = {5, 3, 1, 4, 2};
    for (int i :elementos){
        pila.push(i);
    }
    cout << "Pila original: ";
    objeto.imprimirPila(pila);
    objeto.clasificarPila(pila);
    cout << "\nPila ordenada: ";
    objeto.imprimirPila(pila);
}

