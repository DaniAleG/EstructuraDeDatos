#include <iostream>
#include <stack>
#include <vector>
#include "RecursionPilas.h"
using namespace std;



void RecursionPilas::ordenadoInsertar(int key, stack<int>& pila)
{
    if (pila.empty() || key > pila.top())
    {
        pila.push(key);
        return;
    }
    int top = pila.top();
    pila.pop();
    ordenadoInsertar(key, pila);
    pila.push(top);
}
void RecursionPilas::clasificarPila(stack<int>& pila)
{
    if (pila.empty())
        return;
    int top = pila.top();
    pila.pop();
    clasificarPila(pila);
    ordenadoInsertar(top, pila);
}
void RecursionPilas::imprimirPila(stack<int>& pila)
{
    if (pila.empty())
        return;
    int top = pila.top();
    pila.pop();
    imprimirPila(pila);
    cout << top << " ";
    pila.push(top);
}