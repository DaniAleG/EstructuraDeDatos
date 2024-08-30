/*Lista simple
Funcion recursiva lambda
Que sume los digitos hasta que llegue a 1 solo digito*/
#include <iostream>
#include <functional>
#include <conio.h>
#include "Recuperacion.h"
using namespace std;


ListaSimple :: ListaSimple() {
    cabeza = nullptr;
};

void ListaSimple :: insertar( Nodo *&lista, int elemento){
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
std::string validar(const char* msj) {
    std::string dato;
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (c == 13) {  
            if (!dato.empty()) {  
                break;
            }
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                printf("\b \b"); 
            }
        } else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
            dato += c;
            printf("%c", c);
        }
    }
    printf("\n");
    return dato;
};

void ListaSimple :: imprimir(Nodo* lista){
    while(lista != NULL){
        cout << lista->getDato() << " -> ";
        lista = lista->getSiguiente();
    }
    cout << "NULL" << endl;
};   

    
std::function<int(int)> sumarDigitosLista = [](int num) -> int {
    if (num < 10) {
        return num;
    } else {
        int ultimo_digito = num % 10;
        int resto = num / 10;
        return sumarDigitosLista(ultimo_digito + sumarDigitosLista(resto));
    }
};






