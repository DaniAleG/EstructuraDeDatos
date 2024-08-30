#include "ListaSimple.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <cctype>

using namespace std;

template <typename T>
ListaSimple<T>::ListaSimple() {
    primero = nullptr;
    cargarDesdeArchivo();
}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    while (primero != nullptr) {
        NodoSimple<T>* aux = primero;
        primero = primero->getSiguiente();
        delete aux;
    }
}
template <typename T>
NodoSimple<T>* ListaSimple<T>::getPrimero() {
    return primero;
}

template <typename T>
void ListaSimple<T>::insertar(T numcedula, T primerNombre, T apellido) {
    if (cedulaRepetida(numcedula)) {
        cout << "el numero de cedula ya existe. No se puede insertar." << endl;
        return;
    }

    primerNombre = convertirMayusculas(primerNombre);
    apellido = convertirMayusculas(apellido);

    NodoSimple<T>* nuevo = new NodoSimple<T>(numcedula, primerNombre, apellido);
    nuevo->setSiguiente(primero);
    primero = nuevo;
    guardarEnArchivo();
}

template <typename T>
bool ListaSimple<T>::cedulaRepetida(T numcedula) {
    NodoSimple<T>* aux = primero;
    while (aux != nullptr) {
        if (aux->getNumCedula() == numcedula) {
            return true;
        }
        aux = aux->getSiguiente();
    }
    return false;
}

template <typename T>
bool ListaSimple<T>::listaVacia() {
    return primero == nullptr;
}

template <typename T>
void ListaSimple<T>::buscar(T numcedula) {
    NodoSimple<T>* aux = primero;
    while (aux != nullptr) {
        if (aux->getNumCedula() == numcedula) {
            cout << "el numero de cedula " << numcedula << " corresponde a " << aux->getPrimerNombre() << " " << aux->getApellido() << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "el numero de cedula " << numcedula << " no se encuentra en la lista" << endl;
}

template <typename T>
void ListaSimple<T>::eliminar(T numcedula) {
    NodoSimple<T>* actual = primero;
    NodoSimple<T>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getNumCedula() == numcedula) {
            if (anterior == nullptr) {
                primero = actual->getSiguiente();
            } else {
                anterior->setSiguiente(actual->getSiguiente());
            }
            delete actual;
            cout << "el usuario con el numero de cedula " << numcedula << " ha sido eliminado" << endl;
            guardarEnArchivo();
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    cout << "el numero de cedula " << numcedula << " no se encuentra en la lista" << endl;
}

template <typename T>
void ListaSimple<T>::mostrar() {
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
void ListaSimple<T>::guardarEnArchivo() {
    std::string rutaArchivo = "usuarios.txt";
    std::ofstream archivo(rutaArchivo);
    NodoSimple<T>* aux = primero;
    while (aux != nullptr) {
        archivo << aux->getNumCedula() << "|" << aux->getPrimerNombre() << "|" << aux->getApellido() << std::endl;
        aux = aux->getSiguiente();
    }
    archivo.close();
}

template <typename T>
void ListaSimple<T>::cargarDesdeArchivo() {
    std::string rutaArchivo = "usuarios.txt";
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return;

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream iss(linea);
        T numcedula, primerNombre, apellido;
        getline(iss, numcedula, '|');
        getline(iss, primerNombre, '|');
        getline(iss, apellido, '|');

        NodoSimple<T>* nuevo = new NodoSimple<T>(numcedula, primerNombre, apellido);
        nuevo->setSiguiente(primero);
        primero = nuevo;
    }
    archivo.close();
}


template <typename T>
bool ListaSimple<T>::validarCedula(long int cedula) {
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
bool ListaSimple<T>::esNumeroCedulaValido(const T &numcedula) {
    if (numcedula.length() != 10) return false;
    for (char c : numcedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

template <typename T>
T ListaSimple<T>::ingresarOpcion(const std::string &msj, int minOpcion, int maxOpcion) {
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
T ListaSimple<T>::ingresarCedula(const std::string &msj) {
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
T ListaSimple<T>::ingresarNumeros(const std::string &msj) {
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
T ListaSimple<T>::ingresarLetras(const std::string &msj, bool opcional) {
    T dato = "";
    cout << msj << ": ";
    char c;
    while ((c = getch()) != 13 || (!opcional && dato.empty())) {
        if (isalpha(c)) {
            dato += c;
            cout << c;
        } else if (c == 8) {
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        } else if (c == 13 && !dato.empty()) {
            break;
        }
    }
    cout << endl;
    return dato;
}

template <typename T>
T ListaSimple<T>::convertirMayusculas(T str) {
    if (str.empty()) return str;
    *str.begin() = toupper(*str.begin());
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        *it = tolower(*it);
    }
    return str;
}
template <typename T>
void ListaSimple<T>::mostrarCaracteresOrdenados() {
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
void ListaSimple<T>::resetLista() {
    while (primero != nullptr) {
        NodoSimple<T>* aux = primero;
        primero = primero->getSiguiente();
        delete aux;
    }
}
/*----------METODO DE ORDENAMIENTO POR INTERCAMBIO----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenar(Compare comp) {
    Ordenador<NodoSimple<T>>::ordenarPorSeleccion(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaSimple<T>::ordenarCaracteresEnAtributo(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributo(primero, atributo);
    guardarCaracteresOrdenadosEnArchivo(atributo);
}

template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosEnArchivo(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresEnArchivo(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO BURBUJA----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenarConBurbuja(Compare comp) {
    Ordenador<NodoSimple<T>>::burbuja(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaSimple<T>::ordenarCaracteresBurbuja(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributoBurbuja(primero, atributo);
    guardarCaracteresOrdenadosBurbuja(atributo);
}

template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosBurbuja(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresBurbuja(primero, "usuariosCaracteres.txt", atributo);
}

/*----------METODO DE ORDENAMIENTO POR QUICKSORT----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenarConQuickSort(Compare comp) {
    Ordenador<NodoSimple<T>>::quickSort(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaSimple<T>::ordenarCaracteresQuickSort(const std::string& atributo) {
	Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributoQuickSort(primero, atributo);
	guardarCaracteresOrdenadosQuickSort(atributo);
}
template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosQuickSort(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresQuickSort(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO POR SHELLSORT----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenarConShellSort(Compare comp) {
    Ordenador<NodoSimple<T>>::shellSort(primero, comp);
    guardarEnArchivo();
}

template <typename T>
void ListaSimple<T>::ordenarCaracteresShellSort(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributoShellSort(primero, atributo);
    guardarCaracteresOrdenadosQuickSort(atributo);
}

template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosShellsort(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresShellsort(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO POR DISTRIBUCION----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenarConDistribucion(Compare comp) {
    Ordenador<NodoSimple<T>>::distribucion(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaSimple<T>::ordenarCaracteresDistribucion(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributoDistribucion(primero, atributo);
    guardarCaracteresOrdenadosDistribucion(atributo);
}
template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosDistribucion(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresDistribucion(primero, "usuariosCaracteres.txt", atributo);
}
/*----------METODO DE ORDENAMIENTO POR RADIX----------*/
template <typename T>
template <typename Compare>
void ListaSimple<T>::ordenarConRadix(Compare comp) {
    Ordenador<NodoSimple<T>>::radixSort(primero, comp);
    guardarEnArchivo();
}
template <typename T>
void ListaSimple<T>::ordenarCaracteresRadix(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::ordenarCaracteresEnAtributoRadix(primero, atributo);
    guardarCaracteresOrdenadosRadixSort(atributo);
}
template <typename T>
void ListaSimple<T>::guardarCaracteresOrdenadosRadixSort(const std::string& atributo) {
    Ordenador<NodoSimple<T>>::guardarCaracteresRadixSort(primero, "usuariosCaracteres.txt", atributo);
}