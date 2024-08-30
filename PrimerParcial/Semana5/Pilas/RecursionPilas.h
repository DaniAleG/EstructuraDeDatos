#pragma once
#include <iostream>
#include <stack>
using namespace std;
class RecursionPilas
{ 
    private:
        stack<int>& pila;
        int key;
    public:
        void ordenadoInsertar(int,int);
        RecursionPilas(std::stack<int>& pila) : pila(pila) {}
        void ordenadoInsertar(int key, stack<int> &pila);
        void clasificarPila(stack<int>&);
        void imprimirPila(stack<int>&);

};
