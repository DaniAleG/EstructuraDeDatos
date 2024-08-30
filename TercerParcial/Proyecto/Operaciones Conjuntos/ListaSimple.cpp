#include "ListaSimple.h"

// Constructor



// Destructor
template <typename T>
ListaSimple<T>::~ListaSimple() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

// Método para insertar un dato en la lista
template <typename T>
void ListaSimple<T>::insertar(const T& dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

// Método para mostrar los datos de la lista
template <typename T>
void ListaSimple<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    std::cout << "{ ";
    while (actual != nullptr) {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    std::cout << "}"<< std::endl;
}

// Método para buscar un dato en la lista
template <typename T>
Nodo<T>* ListaSimple<T>::buscar(const T& dato) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == dato) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Método para verificar si un elemento está en la lista
template <typename T>
bool ListaSimple<T>::contains(const T& elemento) const {
    return buscar(elemento) != nullptr;
}

// Método para obtener la unión de dos listas
template <typename T>
ListaSimple<T> ListaSimple<T>::unionList(const ListaSimple<T>& otra) const {
    ListaSimple<T> resultado;
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        resultado.insertar(actual->dato);
        actual = actual->siguiente;
    }
    actual = otra.cabeza;
    while (actual != nullptr) {
        if (!resultado.contains(actual->dato)) {
            resultado.insertar(actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultado;
}

// Método para obtener la intersección de dos listas
template <typename T>
ListaSimple<T> ListaSimple<T>::interseccion(const ListaSimple<T>& otra) const {
    ListaSimple<T> resultado;
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (otra.contains(actual->dato)) {
            resultado.insertar(actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultado;
}

// Método para obtener la diferencia de dos listas
template <typename T>
ListaSimple<T> ListaSimple<T>::diferencia(const ListaSimple<T>& otra, bool isDifferenceAB) const {
    ListaSimple<T> resultado;
    Nodo<T>* actual = isDifferenceAB ? cabeza : otra.cabeza;
    const ListaSimple<T>& comparador = isDifferenceAB ? otra : *this;
    while (actual != nullptr) {
        if (!comparador.contains(actual->dato)) {
            resultado.insertar(actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultado;
}

// Método para obtener la diferencia simétrica de dos listas
template <typename T>
ListaSimple<T> ListaSimple<T>::diferenciaSimetrica(const ListaSimple<T>& otra) const {
    ListaSimple<T> resultado = diferencia(otra, true);
    ListaSimple<T> diferenciaBA = otra.diferencia(*this, true);
    Nodo<T>* actual = diferenciaBA.cabeza;
    while (actual != nullptr) {
        resultado.insertar(actual->dato);
        actual = actual->siguiente;
    }
    return resultado;
}

// Método para obtener el complemento de dos listas
template <typename T>
ListaSimple<T> ListaSimple<T>::complemento(const ListaSimple<T>& otra, bool complementoAB) const {
    return diferencia(otra, complementoAB);
}