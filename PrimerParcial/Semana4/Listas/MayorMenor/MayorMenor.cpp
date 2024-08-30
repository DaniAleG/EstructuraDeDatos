#include <iostream>
#include "C:\Users\ASUS\Documents\C++ Ejercicios\Listas\MayorMenor\MayorMenor.h"
using namespace std;

MayorMenor :: MayorMenor(){
    cabeza = NULL;
}
void MayorMenor :: insertar( Nodo *&lista, int elemento){
    Nodo *nuevo = new Nodo(elemento);
    Nodo *auxiliar;
    nuevo ->setDato(elemento);
    nuevo ->setSiguiente(NULL);
    if(lista == NULL){
        lista = nuevo;
    }else{
        auxiliar = lista;
        while (auxiliar->getSiguiente() != NULL){
            auxiliar = auxiliar->getSiguiente();
        }
        auxiliar->setSiguiente(nuevo);

    }
    cout << "Elemento " << elemento << " insertado correctamente" << endl;
};

void MayorMenor :: mayor(Nodo* lista){
    int mayor = 0;
    while(lista != NULL){
        if(lista->getDato() > mayor){
            mayor = lista->getDato();
        }
    lista = lista->getSiguiente();
    }
    
    cout << "El dato mayor es: " << mayor << endl;
}
void MayorMenor :: menor(Nodo* lista){
    int menor = 10000000;
    while(lista != NULL){
        if(lista->getDato() < menor){
            menor = lista->getDato();
        }
    lista = lista->getSiguiente();
    }
    
    cout << "El dato menor es: " << menor << endl;
}
void MayorMenor :: imprimir(Nodo* lista){
    while(lista != NULL){
        cout << lista->getDato() << " -> ";
        lista = lista->getSiguiente();
    }
    cout << "NULL" << endl;
}
void MayorMenor::liberar(Nodo* lista){
    Nodo* aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->getSiguiente();
        delete aux;
    }
}