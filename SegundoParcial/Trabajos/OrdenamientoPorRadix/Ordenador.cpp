#include "Ordenador.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>

template <typename Nodo>
void Ordenador<Nodo>::intercambiarDatos(Nodo* a, Nodo* b) {
    auto tempNumCedula = a->getNumCedula();
    auto tempPrimerNombre = a->getPrimerNombre();
    auto tempApellido = a->getApellido();

    a->setNumCedula(b->getNumCedula());
    a->setPrimerNombre(b->getPrimerNombre());
    a->setApellido(b->getApellido());

    b->setNumCedula(tempNumCedula);
    b->setPrimerNombre(tempPrimerNombre);
    b->setApellido(tempApellido);
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresEnArchivo(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresRadixSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresRadixSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresRadixSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresEnArchivoCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresRadixSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresRadixSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresRadixSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
template <typename Nodo>
template <typename GetKey>
void Ordenador<Nodo>::radixSort(Nodo*& cabeza, GetKey getKey) {
    if (!cabeza) return;

    Nodo* temp = cabeza;
    while (temp) {
        std::string str = getKey(temp);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        temp = temp->getSiguiente();
    }

    auto obtenerMaxLongitud = [](Nodo* cabeza, auto getKey) -> int {
        int maxLen = 0;
        Nodo* temp = cabeza;
        while (temp) {
            std::string palabra = getKey(temp);
            if (palabra.length() > maxLen) {
                maxLen = palabra.length();
            }
            temp = temp->getSiguiente();
        }
        return maxLen;
    };
    auto contadorOrdenamiento = [](Nodo*& cabeza, int exp, int maxLen, auto getKey, auto intercambiarDatos) {
        const int numCaracteres = 256;
        Nodo* buckets[numCaracteres] = { nullptr };
        Nodo* buckets_tail[numCaracteres] = { nullptr };
        Nodo* temp = cabeza;
        while (temp) {
            std::string palabra = getKey(temp);
            int index = maxLen - exp - 1;
            char c = (index >= 0 && index < palabra.length()) ? palabra[index] : '\0';
            if (buckets[c] == nullptr) {
                buckets[c] = temp;
                buckets_tail[c] = temp;
            } else {
                buckets_tail[c]->setSiguiente(temp);
                buckets_tail[c] = temp;
            }
            temp = temp->getSiguiente();
        }
        cabeza = nullptr;
        Nodo* tail = nullptr;
        for (int i = 0; i < numCaracteres; i++) {
            if (buckets[i] != nullptr) {
                if (cabeza == nullptr) {
                    cabeza = buckets[i];
                    tail = buckets_tail[i];
                } else {
                    tail->setSiguiente(buckets[i]);
                    tail = buckets_tail[i];
                }
            }
        }
        if (tail != nullptr) {
            tail->setSiguiente(nullptr);
        }
    };
    int maxLen = obtenerMaxLongitud(cabeza, getKey);
    for (int exp = 0; exp < maxLen; exp++) {
        contadorOrdenamiento(cabeza, exp, maxLen, getKey, [](Nodo* a, Nodo* b) { intercambiarDatos(a, b); });
    }
}
template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoRadix(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresRadixSort(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresRadixSort(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresRadixSort(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}
template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteresRadixSort(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    auto getMaximo = [](const std::string& s) -> int {
        char maximo = s[0];
        for (char c : s) {
            if (c > maximo) {
                maximo = c;
            }
        }
        return maximo;
    };


    auto contadorOrdenamiento = [](std::string& s, int exp) {
        int n = s.length();
        char* salida = new char[n];  
        int* contador = new int[256]; 
        std::memset(contador, 0, 256 * sizeof(int)); 

        for (int i = 0; i < n; i++) {
            contador[(s[i] / exp) % 256]++;
        }

        for (int i = 1; i < 256; i++) {
            contador[i] += contador[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            salida[contador[(s[i] / exp) % 256] - 1] = s[i];
            contador[(s[i] / exp) % 256]--;
        }

        for (int i = 0; i < n; i++) {
            s[i] = salida[i];
        }

        delete[] salida; 
        delete[] contador;
    };

    int m = getMaximo(str);

    for (int exp = 1; m / exp > 0; exp *= 256) {
        contadorOrdenamiento(str, exp);
    }

    return str;
}
template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoRadixCircular(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    Nodo* inicio = cabeza; 
    do {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresRadixSort(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresRadixSort(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresRadixSort(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    } while (aux != inicio);
}
template <typename Nodo>
template <typename GetKey>
void Ordenador<Nodo>::radixSortCircular(Nodo*& cabeza, GetKey getKey) {
    if (!cabeza) return;
    Nodo* temp = cabeza;
    Nodo* inicio = cabeza; 
    do {
        std::string str = getKey(temp);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        temp = temp->getSiguiente();
    } while (temp != inicio);
    auto obtenerMaxLongitud = [](Nodo* cabeza, auto getKey) -> int {
        int maxLen = 0;
        Nodo* temp = cabeza;
        Nodo* inicio = cabeza;
        do {
            std::string palabra = getKey(temp);
            if (palabra.length() > maxLen) {
                maxLen = palabra.length();
            }
            temp = temp->getSiguiente();
        } while (temp != inicio);
        return maxLen;
    };
    auto contadorOrdenamiento = [](Nodo*& cabeza, int exp, int maxLen, auto getKey, auto intercambiarDatos) {
        const int numCaracteres = 256;
        Nodo* buckets[numCaracteres] = { nullptr };
        Nodo* buckets_tail[numCaracteres] = { nullptr };

        Nodo* temp = cabeza;
        Nodo* inicio = cabeza;
        do {
            std::string palabra = getKey(temp);
            int index = maxLen - exp - 1;
            char c = (index >= 0 && index < palabra.length()) ? palabra[index] : '\0';

            if (buckets[c] == nullptr) {
                buckets[c] = temp;
                buckets_tail[c] = temp;
            } else {
                buckets_tail[c]->setSiguiente(temp);
                buckets_tail[c] = temp;
            }
            temp = temp->getSiguiente();
        } while (temp != inicio);

        cabeza = nullptr;
        Nodo* tail = nullptr;
        for (int i = 0; i < numCaracteres; i++) {
            if (buckets[i] != nullptr) {
                if (cabeza == nullptr) {
                    cabeza = buckets[i];
                    tail = buckets_tail[i];
                } else {
                    tail->setSiguiente(buckets[i]);
                    tail = buckets_tail[i];
                }
            }
        }
        if (tail != nullptr) {
            tail->setSiguiente(cabeza); 
        }
    };

    int maxLen = obtenerMaxLongitud(cabeza, getKey);

    for (int exp = 0; exp < maxLen; exp++) {
        contadorOrdenamiento(cabeza, exp, maxLen, getKey, [](Nodo* a, Nodo* b) { intercambiarDatos(a, b); });
    }
}

