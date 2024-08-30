#include "ListaSimple.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using byte = unsigned char;

using namespace std;

template <typename T>
ListaSimple<T>::ListaSimple() : cabeza(nullptr) {}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    Nodo<T>* actual = cabeza;
    Nodo<T>* siguiente;
    while (actual != nullptr) {
        siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

template <typename T>
void ListaSimple<T>::agregar(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}
template <typename T>
T ListaSimple<T>::ingresarLetras(const char* msj) {
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
        } else if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
            dato += c;
            printf("%c", c);
        }

    }
    printf("\n");
    return dato;
}
template <typename T>
void ListaSimple<T>::eliminar(const T& valor) {
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;
    while (actual != nullptr && actual->getValor() != valor) {
        anterior = actual;
        actual = actual->getSiguiente();
    }
    if (actual != nullptr) {
        if (anterior != nullptr) {
            anterior->setSiguiente(actual->getSiguiente());
        } else {
            cabeza = actual->getSiguiente();
        }
        delete actual;
    }
}

template <typename T>
void ListaSimple<T>::imprimir() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->getValor() << " ";
        actual = actual->getSiguiente();
    }
    std::cout << std::endl;
}

template <typename T>
bool ListaSimple<T>::contiene(const T& valor) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getValor() == valor) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

template <typename T>
Nodo<T>* ListaSimple<T>::getPrimero() const {
    return cabeza;
}
