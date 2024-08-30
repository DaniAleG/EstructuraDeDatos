#include <iostream>
#include <string>   
#include "C:\Users\ASUS\Documents\C++ Ejercicios\Listas\ListaSimple\ListasSimples.h"
using namespace std;

ListaSimples :: ListaSimples(){
    cabeza = NULL;
};
void ListaSimples::insertar(Nodo *&lista, int elemento){
    Nodo *nuevo = new Nodo(elemento);
    nuevo -> setDato(elemento);
    Nodo *aux1 = lista;
    Nodo *aux2;
    while((aux1 != NULL)&& (aux1->getDato()<elemento)){
        aux2 = aux1;
        aux1 = aux1->getSiguiente();
    }
    if(lista == aux1){
        lista = nuevo;
    }
    else{
        aux2 ->setSiguiente(nuevo);
    }
    nuevo ->setSiguiente(aux1);
    cout << "Elemento " << elemento << " insertado correctamente" << endl;
};
void ListaSimples::mostrar(Nodo *lista){
    if(lista == NULL){
        cout << "La lista esta vacia" << endl;
        return;
    }
    Nodo *actual = new Nodo(0);
    actual = lista;
    while(actual != NULL){
        cout << actual->getDato() << " -> ";
        actual = actual->getSiguiente();
    }
    cout << "NULL" << endl;
};

void ListaSimples::buscar(Nodo *&lista,int elemento){
    if(lista == NULL){
        cout << "La lista esta vacia" << endl;
        return;
    }
    cout << "Ingrese un dato a buscar: ";
    cin >> elemento;
    Nodo *actual = lista;
    bool validar = false;
    while((actual != NULL) && (actual->getDato() <= elemento)){
        if(actual -> getDato() == elemento){
            cout << "Elemento " << elemento << " encontrado" << endl;
            validar = true;
            break;
        }
        actual = actual->getSiguiente();

    }
    if(actual == NULL && validar == false){
        cout << "Elemento no encontrado" << endl;
    }
};

void ListaSimples::eliminar(Nodo *&lista,int elemento){
    if(lista != NULL){
        Nodo *aux_borrar;
        Nodo *anterior = NULL; 
        aux_borrar = lista;
        cout << "Ingrese un dato a eliminar: ";
        cin >> elemento;
        while((aux_borrar != NULL)&&(aux_borrar->getDato() != elemento)){
            anterior = aux_borrar;
            aux_borrar = aux_borrar->getSiguiente();
        }
        if(aux_borrar == NULL){
            cout << "El elemento ha buscar no se encuentra en la lista" << endl;
        }else if(anterior == NULL){
            lista = lista->getSiguiente();
            delete aux_borrar;
            cout << "Elemento " << elemento << " eliminado correctamente" << endl;
        }else{
            anterior ->setSiguiente(aux_borrar->getSiguiente());
            delete aux_borrar;
            cout << "Elemento " << elemento << " eliminado correctamente" << endl;
        }
    }else{
        cout << "La lista esta vacia" << endl;
        return;
    }

};

