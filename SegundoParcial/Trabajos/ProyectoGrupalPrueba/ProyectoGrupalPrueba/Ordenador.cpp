#include "Ordenador.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
/*----------METODOS----------*/
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
/*----------METODO DE ORDENAMIENTO POR INTERCAMBIO----------*/
template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::ordenarPorSeleccion(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;
    Nodo* i = cabeza;
    while (i) {
        Nodo* min = i;
        Nodo* j = i->getSiguiente();
        while (j) {
            if (comp(j, min)) {
                min = j;
            }
            j = j->getSiguiente();
        }
        if (min != i) {
            intercambiarDatos(i, min);
        }
        i = i->getSiguiente();
    }
}

template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::ordenarPorSeleccionCircular(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;

    Nodo* i = cabeza;
    do {
        Nodo* min = i;
        Nodo* j = i->getSiguiente();
        do {
            if (comp(j, min)) {
                min = j;
            }
            j = j->getSiguiente();
        } while (j != cabeza);

        if (min != i) {
            intercambiarDatos(i, min);
        }
        i = i->getSiguiente();
    } while (i != cabeza);
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributo(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteres(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteres(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteres(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoCircular(Nodo*& cabeza, const std::string& atributo) {
    if (!cabeza) return;
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteres(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteres(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteres(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
}

template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteres(std::string str) {
    int n = str.length();
    char* charArray = new char[n + 1];
    for (int i = 0; i < n; ++i) {
        charArray[i] = tolower(str[i]);
    }
    charArray[n] = '\0';  
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (*(charArray + j) < *(charArray + minIndex)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            char temp = *(charArray + i);
            *(charArray + i) = *(charArray + minIndex);
            *(charArray + minIndex) = temp;
        }
    }
    for (int i = 0; i < n; ++i) {
        str[i] = *(charArray + i);
    }

    delete[] charArray;

    return str;
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresEnArchivo(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteres(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteres(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteres(aux->getApellido()) << std::endl;
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
            archivo << ordenarCaracteres(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteres(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteres(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
/*----------METODO DE ORDENAMIENTO BURBUJA----------*/
template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::burbuja(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;

    bool swapped;
    Nodo* ptr1;
    Nodo* lptr = nullptr;

    // Hacemos un bucle hasta que no haya más intercambios.
    do {
        swapped = false;
        ptr1 = cabeza;

        while (ptr1->getSiguiente() != lptr) {
            if (comp(ptr1->getSiguiente(), ptr1)) {
                intercambiarDatos(ptr1, ptr1->getSiguiente());
                swapped = true;
            }
            ptr1 = ptr1->getSiguiente();
        }
        lptr = ptr1;
    } while (swapped);
}

template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::burbujaCircular(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;

    bool swapped;
    Nodo* ptr1;
    Nodo* lptr = nullptr;

    // Hacemos un bucle hasta que no haya más intercambios.
    do {
        swapped = false;
        ptr1 = cabeza;

        // Iteramos a través de la lista circular.
        do {
            Nodo* next = ptr1->getSiguiente();
            if (comp(next, ptr1)) {
                intercambiarDatos(ptr1, next);
                swapped = true;
            }
            ptr1 = next;
        } while (ptr1->getSiguiente() != lptr && ptr1 != cabeza);

        lptr = ptr1;
    } while (swapped && lptr != cabeza);
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoBurbuja(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresBurbuja(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresBurbuja(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresBurbuja(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}

template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteresBurbuja(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    char* char_ptr = &(*str.begin());
    int n = str.length();
    bool swapped;

    // Implementación del método de burbuja.
    do {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (*(char_ptr + i) > *(char_ptr + i + 1)) {
                std::swap(*(char_ptr + i), *(char_ptr + i + 1));
                swapped = true;
            }
        }
    } while (swapped);

    return str;
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresBurbujaCircular(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            std::string cedulaOrdenada = ordenarCaracteresBurbuja(aux->getNumCedula());
            aux->setNumCedula(cedulaOrdenada);
        } else if (atributo == "nombre") {
            std::string nombreOrdenado = ordenarCaracteresBurbuja(aux->getPrimerNombre());
            aux->setPrimerNombre(nombreOrdenado);
        } else if (atributo == "apellido") {
            std::string apellidoOrdenado = ordenarCaracteresBurbuja(aux->getApellido());
            aux->setApellido(apellidoOrdenado);
        }
        aux = aux->getSiguiente();
        if (aux == cabeza) break; 
    }
}
template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresBurbuja(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresBurbuja(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresBurbuja(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresBurbuja(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresBurbujaCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresBurbuja(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresBurbuja(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresBurbuja(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
/*----------METODO DE ORDENAMIENTO QUICKSORT----------*/
template <typename Nodo>
template <typename Compare>
Nodo* Ordenador<Nodo>::particionar(Nodo* inicio, Nodo* fin, Compare comp) {
    Nodo* pivot = fin;
    Nodo* i = inicio;

    for (Nodo* j = inicio; j != fin; j = j->getSiguiente()) {
        if (comp(j, pivot)) {
            intercambiarDatos(i, j);
            i = i->getSiguiente();
        }
    }
    intercambiarDatos(i, fin);
    return i;
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoQuickSort(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresQuickSort(aux->getNumCedula()));
        }
        else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresQuickSort(aux->getPrimerNombre()));
        }
        else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresQuickSort(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}

template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteresQuickSort(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    char* char_ptr = &(*str.begin());
    int n = str.length();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            char temp = *(char_ptr + i);
            int j = i;
            for (; j >= gap && *(char_ptr + j - gap) > temp; j -= gap) {
                *(char_ptr + j) = *(char_ptr + j - gap);
            }
            *(char_ptr + j) = temp;
        }
    }
    return str;
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresQuickSortCircular(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            std::string cedulaOrdenada = ordenarCaracteresQuickSort(aux->getNumCedula());
            aux->setNumCedula(cedulaOrdenada);
        }
        else if (atributo == "nombre") {
            std::string nombreOrdenado = ordenarCaracteresQuickSort(aux->getPrimerNombre());
            aux->setPrimerNombre(nombreOrdenado);
        }
        else if (atributo == "apellido") {
            std::string apellidoOrdenado = ordenarCaracteresQuickSort(aux->getApellido());
            aux->setApellido(apellidoOrdenado);
        }
        aux = aux->getSiguiente();
        if (aux == cabeza) break;
    }
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoQuickSortCircular(Nodo*& cabeza, const std::string& atributo) {
	Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
			aux->setNumCedula(ordenarCaracteresQuickSort(aux->getNumCedula()));
		}
        else if (atributo == "nombre") {
			aux->setPrimerNombre(ordenarCaracteresQuickSort(aux->getPrimerNombre()));
		}
        else if (atributo == "apellido") {
			aux->setApellido(ordenarCaracteresQuickSort(aux->getApellido()));
		}
		aux = aux->getSiguiente();
		if (aux == cabeza) break;
	}
}
template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::quickSort(Nodo*& cabeza, Compare comp) {
    if (!cabeza || !cabeza->getSiguiente()) return;
    Nodo* fin = cabeza;
    while (fin->getSiguiente()) fin = fin->getSiguiente();
    quickSortRec(cabeza, fin, comp);
}

template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::quickSortRec(Nodo* inicio, Nodo* fin, Compare comp) {
    if (fin != nullptr && inicio != fin && inicio != fin->getSiguiente()) {
        Nodo* pivot = particionar(inicio, fin, comp);
        if (pivot != inicio) {
            Nodo* prev = inicio;
            while (prev->getSiguiente() != pivot) {
                prev = prev->getSiguiente();
            }
            quickSortRec(inicio, prev, comp);
        }
        if (pivot != fin) {
            quickSortRec(pivot->getSiguiente(), fin, comp);
        }
    }
}

template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::quickSortCircular(Nodo*& cabeza, Compare comp) {
    Nodo* high = nullptr;
    Nodo* traverse = cabeza;
    int length = 0;

    do {
        high = traverse;
        traverse = traverse->getSiguiente();
        length++;
    } while (traverse != cabeza);

    if (!cabeza) return;

    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; ++i) {
            Nodo* current = cabeza;
            for (int j = 0; j < i; ++j) {
                current = current->getSiguiente();
            }

            Nodo* left = current;
            Nodo* right = nullptr;
            for (int j = i; j >= gap; j -= gap) {
                right = cabeza;
                for (int k = 0; k < j - gap; ++k) {
                    right = right->getSiguiente();
                }

                if (comp(left, right)) {
                    intercambiarDatos(left, right);
                }
                else {
                    break;
                }
                left = right;
            }
        }
    }
}
template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresQuickSort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresQuickSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresQuickSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresQuickSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresQuickSortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresQuickSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresQuickSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresQuickSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
/*----------METODO DE ORDENAMIENTO SHELLSORT----------*/
template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::shellSort(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;

    int n = 0;
    Nodo* temp = cabeza;
    while (temp) {
        n++;
        temp = temp->getSiguiente();
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Nodo* current = cabeza;
            for (int j = 0; j < i; ++j) {
                current = current->getSiguiente();
            }

            Nodo* temp2 = current;
            Nodo* temp3 = nullptr;
            for (int j = i; j >= gap; j -= gap) {
                temp3 = cabeza;
                for (int k = 0; k < j - gap; ++k) {
                    temp3 = temp3->getSiguiente();
                }

                if (comp(temp2, temp3)) {
                    intercambiarDatos(temp2, temp3);
                } else {
                    break;
                }
                temp2 = temp3;
            }
        }
    }
}

template <typename Nodo>
template <typename Compare>
void Ordenador<Nodo>::shellSortCircular(Nodo*& cabeza, Compare comp) {
    if (!cabeza) return;

    Nodo* ultimo = nullptr;
    Nodo* temp = cabeza;
    int n = 0;

    do {
        ultimo = temp;
        temp = temp->getSiguiente();
        n++;
    } while (temp != cabeza);

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Nodo* current = cabeza;
            for (int j = 0; j < i; ++j) {
                current = current->getSiguiente();
            }

            Nodo* temp2 = current;
            Nodo* temp3 = nullptr;
            for (int j = i; j >= gap; j -= gap) {
                temp3 = cabeza;
                for (int k = 0; k < j - gap; ++k) {
                    temp3 = temp3->getSiguiente();
                }

                if (comp(temp2, temp3)) {
                    intercambiarDatos(temp2, temp3);
                } else {
                    break;
                }
                temp2 = temp3;
            }
        }
    }
}

template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresEnAtributoShellSort(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresShellSort(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresShellSort(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresShellSort(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}
template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteresShellSort(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    char* char_ptr = &(*str.begin());
    int n = str.length();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            char temp = *(char_ptr + i);
            int j = i;
            for (; j >= gap && *(char_ptr + j - gap) > temp; j -= gap) {
                *(char_ptr + j) = *(char_ptr + j - gap);
            }
            *(char_ptr + j) = temp;
        }
    }
    
    return str;
}
template <typename Nodo>
void Ordenador<Nodo>::ordenarCaracteresShellSortCircular(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            std::string cedulaOrdenada = ordenarCaracteresShellSort(aux->getNumCedula());
            aux->setNumCedula(cedulaOrdenada);
        } else if (atributo == "nombre") {
            std::string nombreOrdenado = ordenarCaracteresShellSort(aux->getPrimerNombre());
            aux->setPrimerNombre(nombreOrdenado);
        } else if (atributo == "apellido") {
            std::string apellidoOrdenado = ordenarCaracteresShellSort(aux->getApellido());
            aux->setApellido(apellidoOrdenado);
        }
        aux = aux->getSiguiente();
        if (aux == cabeza) break;
    }
}
template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresShellsort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresShellSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresShellSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresShellSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresShellsortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresShellSort(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresShellSort(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresShellSort(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
/*----------METODO DE ORDENAMIENTO POR DISTRIBUCION----------*/
template <typename Nodo>
template <typename GetKey>
void Ordenador<Nodo>::distribucion(Nodo*& cabeza, GetKey getKey) {
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
void Ordenador<Nodo>::ordenarCaracteresEnAtributoDistribucion(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresDistribucion(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresDistribucion(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresDistribucion(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    }
}
template <typename Nodo>
std::string Ordenador<Nodo>::ordenarCaracteresDistribucion(std::string str) {
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
void Ordenador<Nodo>::ordenarCaracteresEnAtributoDistribucionCircular(Nodo*& cabeza, const std::string& atributo) {
    Nodo* aux = cabeza;
    Nodo* inicio = cabeza;
    do {
        if (atributo == "cedula") {
            aux->setNumCedula(ordenarCaracteresDistribucion(aux->getNumCedula()));
        } else if (atributo == "nombre") {
            aux->setPrimerNombre(ordenarCaracteresDistribucion(aux->getPrimerNombre()));
        } else if (atributo == "apellido") {
            aux->setApellido(ordenarCaracteresDistribucion(aux->getApellido()));
        }
        aux = aux->getSiguiente();
    } while (aux != inicio);
}
template <typename Nodo>
template <typename GetKey>
void Ordenador<Nodo>::distribucionCircular(Nodo*& cabeza, GetKey getKey) {
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
template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresDistribucion(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    while (aux) {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresDistribucion(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresDistribucion(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresDistribucion(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresDistribucionCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
    std::ofstream archivo(nombreArchivo);
    Nodo* aux = cabeza;
    do {
        if (atributo == "cedula") {
            archivo << ordenarCaracteresDistribucion(aux->getNumCedula()) << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "nombre") {
            archivo << aux->getNumCedula() << "|" << ordenarCaracteresDistribucion(aux->getPrimerNombre()) << "|" << aux->getApellido() << std::endl;
        } else if (atributo == "apellido") {
            archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << ordenarCaracteresDistribucion(aux->getApellido()) << std::endl;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    archivo.close();
}
/*----------METODO DE ORDENAMIENTO POR RADIX----------*/
template <typename Nodo>
template <typename GetKey>
void Ordenador<Nodo>::radixSort(Nodo*& cabeza, GetKey getKey) {
    if (!cabeza) return;

    // Normalizar las palabras a minúsculas
    Nodo* temp = cabeza;
    while (temp) {
        std::string str = getKey(temp);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        temp = temp->getSiguiente();
    }

    // Función auxiliar para obtener la longitud máxima de una palabra en la lista
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

    // Función auxiliar para realizar el conteo y ordenar por cada posición de carácter
    auto contadorOrdenamiento = [](Nodo*& cabeza, int exp, int maxLen, auto getKey, auto intercambiarDatos) {
        // Ajustar según el número de caracteres en el juego de caracteres
        const int numCaracteres = 256;
        Nodo* buckets[numCaracteres] = { nullptr };
        Nodo* buckets_tail[numCaracteres] = { nullptr };
    
        Nodo* temp = cabeza;
        while (temp) {
            std::string palabra = getKey(temp);
            int index = maxLen - exp - 1; // Ajustar el índice para ordenar de derecha a izquierda
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
        char* salida = new char[n];  // Usamos memoria dinámica para el arreglo de salida
        int* contador = new int[256]; // Usamos memoria dinámica para el contador
        std::memset(contador, 0, 256 * sizeof(int)); // Inicializamos el contador a 0

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

        delete[] salida;  // Liberamos la memoria dinámica
        delete[] contador; // Liberamos la memoria dinámica
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
    Nodo* inicio = cabeza; // Guardar el inicio para saber cuando parar
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

    // Normalizar las palabras a minúsculas
    Nodo* temp = cabeza;
    Nodo* inicio = cabeza; // Guardar el inicio para saber cuando parar
    do {
        std::string str = getKey(temp);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        temp = temp->getSiguiente();
    } while (temp != inicio);

    // Función auxiliar para obtener la longitud máxima de una palabra en la lista
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

    // Función auxiliar para realizar el conteo y ordenar por cada posición de carácter
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
            tail->setSiguiente(cabeza); // Mantener la lista circular
        }
    };

    int maxLen = obtenerMaxLongitud(cabeza, getKey);

    for (int exp = 0; exp < maxLen; exp++) {
        contadorOrdenamiento(cabeza, exp, maxLen, getKey, [](Nodo* a, Nodo* b) { intercambiarDatos(a, b); });
    }
}
template <typename Nodo>
void Ordenador<Nodo>::guardarCaracteresRadixSort(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
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
void Ordenador<Nodo>::guardarCaracteresRadixSortCircular(Nodo* cabeza, const std::string& nombreArchivo, const std::string& atributo) {
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