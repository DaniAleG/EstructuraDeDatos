#include "Buscador.h"
#include <unordered_map>
template <typename Nodo>
void Buscador<Nodo>::buscarSecuencial(Nodo* cabeza, const std::string& valor, const std::string& atributo) {
    if (!cabeza) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* actual = cabeza;
    bool encontrado = false;
    bool esCircular = false;
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        if (temp->getSiguiente() == cabeza) {
            esCircular = true;
            break;
        }
        temp = temp->getSiguiente();
    }

    do {
        if ((atributo == "cedula" && actual->getNumCedula() == valor) ||
            (atributo == "nombre" && actual->getPrimerNombre() == valor) ||
            (atributo == "apellido" && actual->getApellido() == valor)) {
            std::cout << "Usuario encontrado: " << actual->getNumCedula() << " " << actual->getPrimerNombre() << " " << actual->getApellido() << std::endl;
            encontrado = true;
        }
        actual = actual->getSiguiente();
    } while (actual != nullptr && (!esCircular || actual != cabeza));

    if (!encontrado) {
        std::cout << "Usuario no encontrado." << std::endl;
    }
}
template <typename Nodo>
void Buscador<Nodo>::buscarBinario(Nodo* cabeza, const std::string& valor, const std::string& atributo) {
    if (!cabeza) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    bool encontrado = false;
    bool esCircular = false;

    // Verificar si la lista es circular
    Nodo* temp = cabeza;
    while (temp->getSiguiente() != nullptr && temp->getSiguiente() != cabeza) {
        temp = temp->getSiguiente();
    }
    if (temp->getSiguiente() == cabeza) {
        esCircular = true;
    }

    // Contar el número de nodos en la lista
    int length = 0;
    temp = cabeza;
    do {
        ++length;
        temp = temp->getSiguiente();
    } while (temp != nullptr && (!esCircular || temp != cabeza));

    int inicio = 0;
    int fin = length - 1;

    // Función interna para avanzar un número dado de pasos en la lista
    auto avanzar = [](Nodo* nodo, int pasos) -> Nodo* {
        while (pasos-- > 0 && nodo != nullptr) {
            nodo = nodo->getSiguiente();
        }
        return nodo;
    };

    // Función interna para comparar el valor de un atributo del nodo con el valor buscado
    auto comparar = [](Nodo* nodo, const std::string& valor, const std::string& atributo) -> int {
        if (atributo == "cedula") {
            return nodo->getNumCedula() == valor ? 0 : (nodo->getNumCedula() < valor ? -1 : 1);
        } else if (atributo == "nombre") {
            return nodo->getPrimerNombre().compare(valor);
        } else if (atributo == "apellido") {
            return nodo->getApellido().compare(valor);
        }
        return 1; // Asumimos que los atributos válidos siempre serán "cedula", "nombre" o "apellido"
    };

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        Nodo* nodoMedio = avanzar(cabeza, medio);
        int comp = comparar(nodoMedio, valor, atributo);

        std::cout << "Comparando con: " << nodoMedio->getNumCedula() << " " << nodoMedio->getPrimerNombre() << " " << nodoMedio->getApellido() << std::endl;

        if (comp == 0) {
            std::cout << "Usuario encontrado: " << nodoMedio->getNumCedula() << " " << nodoMedio->getPrimerNombre() << " " << nodoMedio->getApellido() << std::endl;
            encontrado = true;
            break;
        } else if (comp < 0) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    if (!encontrado) {
        std::cout << "Usuario no encontrado." << std::endl;
    }
}


int generarKey(std::string opcion) {
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
