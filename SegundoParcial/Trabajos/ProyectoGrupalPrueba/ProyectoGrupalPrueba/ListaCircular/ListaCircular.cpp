#include "ListaCircular.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <conio.h>

using namespace std;

template <typename T>
ListaCircular<T>::ListaCircular() {
    primero = nullptr;
    ultimo = nullptr;
    cargarDesdeArchivo();
}

template <typename T>
ListaCircular<T>::~ListaCircular() {
    if (primero != nullptr) {
        NodoCircular<T>* actual = primero;
        NodoCircular<T>* siguiente;
        do {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != primero);
    }
}
template <typename T>
NodoCircular<T>* ListaCircular<T>::getPrimero() {
    return primero;
}
template <typename T>
void ListaCircular<T>::insertar(T numcedula, T primerNombre, T apellido) {
    if (cedulaRepetida(numcedula)) {
        cout << "El numero de cedula ya existe. No se puede insertar." << endl;
        return;
    }

    primerNombre = convertirMayusculas(primerNombre);
    apellido = convertirMayusculas(apellido);

    NodoCircular<T>* nuevo = new NodoCircular<T>(numcedula, primerNombre, apellido);

    if (listaVacia()) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(nuevo);
    } else {
        nuevo->setSiguiente(primero);
        ultimo->setSiguiente(nuevo);
        primero = nuevo;
    }

    guardarEnArchivo();
}

template <typename T>
bool ListaCircular<T>::cedulaRepetida(T numcedula) {
    if (listaVacia()) return false;

    NodoCircular<T>* aux = primero;
    do {
        if (aux->getNumCedula() == numcedula) {
            return true;
        }
        aux = aux->getSiguiente();
    } while (aux != primero);

    return false;
}

template <typename T>
bool ListaCircular<T>::listaVacia() {
    return primero == nullptr;
}

template <typename T>
void ListaCircular<T>::buscar(T numcedula) {
    if (listaVacia()) {
        cout << "Lista vacia." << endl;
        return;
    }

    NodoCircular<T>* aux = primero;
    do {
        if (aux->getNumCedula() == numcedula) {
            cout << "El numero de cedula " << numcedula << " corresponde a " << aux->getPrimerNombre() << " " << aux->getApellido() << endl;
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != primero);

    cout << "El numero de cedula " << numcedula << " no se encuentra en la lista" << endl;
}

template <typename T>
void ListaCircular<T>::eliminar(T numcedula) {
    if (listaVacia()) {
        cout << "Lista vacia." << endl;
        return;
    }

    NodoCircular<T>* actual = primero;
    NodoCircular<T>* anterior = nullptr;

    do {
        if (actual->getNumCedula() == numcedula) {
            if (anterior == nullptr) {
                primero = actual->getSiguiente();
                ultimo->setSiguiente(primero);
                if (actual == primero) {
                    primero = nullptr;
                    ultimo = nullptr;
                }
            } else {
                anterior->setSiguiente(actual->getSiguiente());
                if (actual == ultimo) {
                    ultimo = anterior;
                }
            }

            delete actual;
            cout << "El usuario con el numero de cedula " << numcedula << " ha sido eliminado" << endl;
            guardarEnArchivo();
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);

    cout << "El numero de cedula " << numcedula << " no se encuentra en la lista" << endl;
}

template <typename T>
void ListaCircular<T>::mostrar() {
    if (listaVacia()) {
        cout << "Lista vacia." << endl;
        return;
    }
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo usuarios.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

template <typename T>
void ListaCircular<T>::guardarEnArchivo() {
    ofstream archivo("usuarios.txt");
    if (listaVacia()) return;

    NodoCircular<T>* aux = primero;
    do {
        archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << endl;
        aux = aux->getSiguiente();
    } while (aux != primero);

    archivo.close();
}

template <typename T>
void ListaCircular<T>::cargarDesdeArchivo() {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        T numcedula, primerNombre, apellido;
        getline(iss, numcedula, '|');
        getline(iss, primerNombre, '|');
        getline(iss, apellido, '|');

        NodoCircular<T>* nuevo = new NodoCircular<T>(numcedula, primerNombre, apellido);
        if (listaVacia()) {
            primero = nuevo;
            ultimo = nuevo;
            nuevo->setSiguiente(nuevo);
        } else {
            nuevo->setSiguiente(primero);
            ultimo->setSiguiente(nuevo);
            primero = nuevo;
        }
    }
    archivo.close();
}

template <typename T>
bool ListaCircular<T>::validarCedula(long int cedula) {
    int i, A[10], res, mul, sumapares, sumaimpares, digito, sumatotal;
    long int cos;
    sumapares = 0;
    sumaimpares = 0;
    for (i = 9; i >= 0; i--) {
        cos = cedula / 10;
        res = cedula % 10;
        A[i] = res;
        cedula = cos;
    }
    for (i = 0; i < 9; i += 2) {
        mul = A[i] * 2;
        if (mul > 9)
            mul -= 9;
        sumapares += mul;
    }
    for (i = 1; i < 8; i += 2)
        sumaimpares += A[i];

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    digito = 10 - res;

    if (digito == 10)
        digito = 0;
    return digito == A[9];
}

template <typename T>
bool ListaCircular<T>::esNumeroCedulaValido(const T &numcedula) {
    if (numcedula.length() != 10) return false;
    for (char c : numcedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

template <typename T>
T ListaCircular<T>::ingresarOpcion(const std::string &msj, int minOpcion, int maxOpcion) {
    T dato = "";
    cout << msj << ": ";
    char c;
    while (true) {
        c = getch();
        if (isdigit(c) && dato.length() < 2) {
            dato += c;
            cout << c;
        } else if (c == 8 && !dato.empty()) {
            dato.pop_back();
            cout << "\b \b";
        } else if (c == 13 && !dato.empty()) {
            int opcion = stoi(dato);
            if (opcion >= minOpcion && opcion <= maxOpcion) {
                cout << endl;
                return dato;
            } else {
                cout << "\n>> Opcion invalida. Ingrese nuevamente." << endl;
                dato = "";
                cout << msj << ": ";
            }
        }
    }
}

template <typename T>
T ListaCircular<T>::ingresarCedula(const std::string &msj) {
    T dato = "";
    cout << msj << ": ";
    char c;
    while (true) {
        c = getch();
        if (isdigit(c) && c != ' ') {
            if (dato.length() < 10) {
                dato += c;
                cout << c;
            }
        } else if (c == 8) {
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        } else if (c == 13) {
            if (dato.length() == 10) {
                cout << endl;
                break;
            } else {
                cout << "\n>> Debe ingresar exactamente 10 numeros. Intente nuevamente." << endl;
                dato = "";
                cout << msj << ": ";
            }
        }
    }
    return dato;
}

template <typename T>
T ListaCircular<T>::ingresarNumeros(const std::string &msj) {
    T dato = "";
    cout << msj << ": ";
    char c;
    while ((c = getch()) != 13) {
        if (isdigit(c)) {
            dato += c;
            cout << c;
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        }
        else if (c == ' ') {
            
        }
    }
    cout << endl;
    return dato;
}

template <typename T>
T ListaCircular<T>::ingresarLetras(const std::string &msj) {
    T dato = "";
    cout << msj << ": ";
    char c;
    while ((c = getch()) != 13) {
        if (isalpha(c)) {
            dato += c;
            cout << c;
        } else if (c == 8) { 
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        }
    }
    cout << endl;
    return dato;
}

template <typename T>
T ListaCircular<T>::convertirMayusculas(T str) {
    if (str.empty()) return str;
    *str.begin() = toupper(*str.begin());
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        *it = tolower(*it);
    }
    return str;
}
template <typename T>
void ListaCircular<T>::mostrarCaracteresOrdenados() {
    if (listaVacia()) {
        cout << "Lista vacia." << endl;
        return;
    }
    ifstream archivo("usuariosCaracteres.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo usuariosCaracteres.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}
template <typename T>
void ListaCircular<T>::resetLista() {
    if (primero != nullptr) {
        NodoCircular<T>* actual = primero;
        NodoCircular<T>* siguiente;
        do {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != primero);
        primero = nullptr;
        ultimo = nullptr;
    }
}
/*----------METODO DE ORDENAMIENTO POR INTERCAMBIO----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenar(Compare comp) {
    if (listaVacia()) return;
    Ordenador<NodoCircular<T>>::ordenarPorSeleccionCircular(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaCircular<T>::ordenarCaracteresEnAtributo(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresEnAtributoCircular(primero, atributo);
    guardarCaracteresOrdenadosEnArchivo(atributo);
}

template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosEnArchivo(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresEnArchivoCircular(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO BURBUJA----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenarConBurbuja(Compare comp) {
    if (listaVacia()) return;
    Ordenador<NodoCircular<T>>::burbujaCircular(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaCircular<T>::ordenarCaracteresBurbuja(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresBurbujaCircular(primero, atributo);
    guardarCaracteresOrdenadosBurbuja(atributo);
}

template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosBurbuja(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresBurbujaCircular(primero, "usuariosCaracteres.txt", atributo);
}

/*----------METODO DE ORDENAMIENTO POR QUICKSORT----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenarConQuickSortCirc(Compare comp) {
    Ordenador<NodoCircular<T>>::quickSortCircular(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaCircular<T>::ordenarCaracteresQuickSortCirc(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresEnAtributoQuickSortCircular(primero, atributo);
    guardarCaracteresOrdenadosQuickSortCirc(atributo); 
}

template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosQuickSortCirc(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresQuickSortCircular(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO POR SHELLSORT----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenarConShellSort(Compare comp) {
    if (listaVacia()) return;
    Ordenador<NodoCircular<T>>::shellSortCircular(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaCircular<T>::ordenarCaracteresShellSort(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresShellSortCircular(primero, atributo);
    guardarCaracteresOrdenadosShellsort(atributo);
}
template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosShellsort(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresShellsortCircular(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO POR DISTRIBUCION----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenarConDistribucion(Compare comp) {
    Ordenador<NodoCircular<T>>::distribucionCircular(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaCircular<T>::ordenarCaracteresDistribucion(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresEnAtributoDistribucionCircular(primero, atributo);
    guardarCaracteresOrdenadosDistribucion(atributo);
}
template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosDistribucion(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresDistribucionCircular(primero, "usuariosCaracteres.txt", atributo);
}

/*----------METODO DE ORDENAMIENTO POR RADIX----------*/
template <typename T>
template <typename Compare>
void ListaCircular<T>::ordenarConRadix(Compare comp) {

    Ordenador<NodoCircular<T>>::radixSortCircular(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaCircular<T>::ordenarCaracteresRadix(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::ordenarCaracteresEnAtributoRadixCircular(primero, atributo);
    guardarCaracteresOrdenadosRadixSort(atributo);
}
template <typename T>
void ListaCircular<T>::guardarCaracteresOrdenadosRadixSort(const std::string& atributo) {
    Ordenador<NodoCircular<T>>::guardarCaracteresRadixSortCircular(primero, "usuariosCaracteres.txt", atributo);
}