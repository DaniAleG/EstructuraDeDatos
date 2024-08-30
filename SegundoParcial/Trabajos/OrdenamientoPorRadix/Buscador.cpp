#include "Buscador.h"
#include <unordered_map>


int generarKey(string opcion) {
    int hash = 0;
    bool letras = false;
    bool numeros = false;

    for (char c : opcion) {
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            letras = true;
            hash += c;
        } else if (c >= '0' && c <= '9') {
            numeros = true;
            hash += c - '0';
        }
    }

    if (letras && numeros) {
        hash = (hash * 31 + letras) ^ numeros;
    } else if (letras) {
        hash = hash % 127;
        if (hash >= 100){
            hash = hash % 100;
        }
    } else if (numeros) {
        hash = hash % 1000000007;
    }

    return hash;
}
template <typename Nodo>
void Buscador<Nodo>::buscarTablasHash(Nodo* cabeza, const std::string& valor, const std::string& atributo) {
    if (!cabeza) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    std::unordered_multimap<int, Nodo*> indice;
    Nodo* actual = cabeza;

    // Variable para detectar si la lista es circular
    bool esCircular = false;
    if (cabeza->getSiguiente() != nullptr) {
        Nodo* temp = cabeza->getSiguiente();
        while (temp != nullptr && temp != cabeza) {
            temp = temp->getSiguiente();
        }
        esCircular = (temp == cabeza);
    }

    do {
        int keyCedula = generarKey(actual->getNumCedula());
        int keyNombre = generarKey(actual->getPrimerNombre());
        int keyApellido = generarKey(actual->getApellido());

        if (atributo == "cedula") {
            indice.insert({keyCedula, actual});
        } else if (atributo == "nombre") {
            indice.insert({keyNombre, actual});
        } else if (atributo == "apellido") {
            indice.insert({keyApellido, actual});
        }

        actual = actual->getSiguiente();
    } while (actual != nullptr && (!esCircular || actual != cabeza));

    int key = generarKey(valor);
    auto range = indice.equal_range(key);

    bool encontrado = false;
    for (auto it = range.first; it != range.second; ++it) {
        Nodo* nodo = it->second;
        std::cout << "Usuario encontrado: " << nodo->getNumCedula() << " " << nodo->getPrimerNombre() << " " << nodo->getApellido() << std::endl;
        encontrado = true;
    }

    if (!encontrado) {
        std::cout << "Usuario no encontrado." << std::endl;
    }
}

template class Buscador<NodoSimple<std::string>>;
template class Buscador<NodoDoble<std::string>>;
template class Buscador<NodoCircular<std::string>>;
