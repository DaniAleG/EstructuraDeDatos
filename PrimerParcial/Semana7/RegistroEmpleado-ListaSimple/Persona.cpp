#include <iostream>
#include <stdlib.h>
#include "Persona.h"
#include "Nodo.h"
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <cctype>

using namespace std;

Persona::Persona() {
    primero = nullptr;
    ultimo = nullptr;
}

Persona::~Persona() {
    Nodo* actual = primero;
    while (actual) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void Persona::setPrimero(Nodo* primero) {
    this->primero = primero;
}

Nodo* Persona::getPrimero() {
    return this->primero;
}

void Persona::setUltimo(Nodo* ultimo) {
    this->ultimo = ultimo;
}

Nodo* Persona::getUltimo() {
    return this->ultimo;
}

void Persona::ingresarInicio(string dato) {
    Nodo* nuevo = new Nodo();
    nuevo->setDato(dato);
    if (this->primero == NULL) {
        this->primero = nuevo;
        this->ultimo = nuevo;
    } else {
        nuevo->setSiguiente(this->primero);
        this->primero = nuevo;
    }
    cout << "Elemento " << dato << " insertado correctamente" << endl;
}


string Persona::crearCorreo(string nombre) {
    Nodo* nuevo = new Nodo();
    nuevo->setDato(nombre);
    nuevo->setSiguiente(NULL);

    if (this->primero == NULL) {
        this->primero = nuevo;
        this->ultimo = nuevo;
    } else {
        this->ultimo->setSiguiente(nuevo);
        this->ultimo = nuevo;
    }

    string correo = nombre + "@espe.edu.ec";
    int contador = 0;
    string correoValidado = anadirNumeroCorreo(correo, nombre, contador);
    nuevo->setDato(correoValidado);
    return correoValidado;
}
string Persona::anadirNumeroClave(string clave, int contador) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    
    // Verificar si la clave inicial ya existe en el archivo
    while (getline(archivo, linea)) {
        if (linea.find(clave) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    
    string claveOriginal = clave;
    
    if (encontrado) {
        do {
            contador++;
            clave = claveOriginal + to_string(contador); // Agregar el contador a la clave original
            encontrado = false;
            archivo.open("datos.txt");
            while (getline(archivo, linea)) {
                if (linea.find(clave) != string::npos) {
                    encontrado = true;
                    break;
                }
            }
            archivo.close();
        } while (encontrado);
    }
    
    return clave;
}
string Persona::anadirNumeroCorreo(string correo, string inicio, int contador) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(correo) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (encontrado) {
        do {
            contador++;
            correo = inicio + to_string(contador) + "@espe.edu.ec";
            encontrado = false;
            archivo.open("datos.txt");
            while (getline(archivo, linea)) {
                if (linea.find(correo) != string::npos) {
                    encontrado = true;
                    break;
                }
            }
            archivo.close();
        } while (encontrado);
    }

    return correo;
}



string* Persona::transformarMinusculas(string *cadena) {
    string* minusc = new string(*cadena);
    for (int i = 0; i < minusc->length(); i++) {
        (*minusc)[i] = tolower((*minusc)[i]);
    }
    return minusc;
}

string* Persona::nombre(string *nombre1, string *nombre2, string *apellido) {
    string* cadena = new string();
    *cadena += tolower(nombre1->front());
    if(nombre2 != nullptr && !nombre2->empty()){
    *cadena += tolower(nombre2->front());
    }else{
        *cadena += '_';
    }
    *cadena = *cadena + *transformarMinusculas(apellido);
    return cadena;
}
string Persona::validarNombre2(const char* msj){
    std::string dato;
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (c == 13) {
            if (dato.empty()) {
                break;
            }
        } else if (c == 8) {
            if (!dato.empty()) {
                dato.pop_back();
                printf("\b \b");
            }
        } else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            dato += c;
            printf("%c", c);
        }
    if (c == 13) {
        if (!dato.empty()) {
            break;
        }
    }
    }
    printf("\n");
    return dato;
};

string Persona::validarLetras(const char* msj) {
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
        } else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            dato += c;
            printf("%c", c);
        }

    }
    printf("\n");
    return dato;
}

string Persona::validarNumeros(const char* msj) {
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
        } else if (c >= '0' && c <= '9') {
            dato += c;
            printf("%c", c);
        }
    }
    
    printf("\n");
    return dato;
}

bool Persona::datoRepetido(string dato) {
    ifstream archivo("datos.txt");
    string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(dato) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    return encontrado;
}

string Persona::cifradoCesar(string* contrasenia){
    int numero = 5;
    auto cifrado = [numero](char m)-> char{
        if (islower(m)) {
            char base = 'a';
            return ((m - base + numero) % 26) + base;
        } else if (isupper(m)) {
            char base = 'A';
            return ((m - base + numero) % 26) + base;
        } else if(isdigit(m)) {
            char base = '0';
            return ((m - base + numero) % 10) + base;
        }else if(isspace(m)){
            char base = 'A';
            return ((m - base + numero) % 1) + base;
        } else {
            return m;
        }
    };
    
    string contra = "";
    for (char c : *contrasenia) {
        contra += cifrado(c);
    }
    if(datoRepetido(contra)){
        cifradoCesar(&contra);
    }
    return contra;
}

string* Persona::contrasenia(string* nombre1, string* nombre2, string* apellido) {
    string* apellidoInv = new string();
    string* clave = new string();

    // Convertir las entradas a minúsculas
    nombre1 = transformarMinusculas(nombre1);
    apellido = transformarMinusculas(apellido);
    if (nombre2 != nullptr) {
        nombre2 = transformarMinusculas(nombre2);
    }

    // Invertir el apellido excepto el último carácter
    for (int i = apellido->length() - 2; i >= 0; i--) {
        *apellidoInv += (*apellido)[i];
    }

    // Obtener las letras necesarias
    string letra1(1, nombre1->front());
    char letrita = letra1[0];
    letrita = letrita - 32; // Convertir la primera letra de nombre1 a mayúscula
    string letra3(1, apellido->back());
    
    // Verificar si se ingresó un segundo nombre
    if (nombre2 != nullptr && !nombre2->empty()) {
        string letra2(1, nombre2->front());
        char letrita2 = letra2[0];
        letrita2 = letrita2 - 32; // Convertir la primera letra de nombre2 a mayúscula
        *clave = letra3 + letrita + letrita2 + *apellidoInv;
    } else {
        // Si no hay segundo nombre, usar un espacio en blanco
        char letra2 = ' ';
        *clave = letra3 + letrita + letra2 + *apellidoInv;
    }
    *clave = anadirNumeroClave(*clave, 0);
    return clave;
}

bool Persona::validarCedula(std::string cedula) {
    long int cedula1 = stol(cedula);
    int i, *A = new int[10], res, mul, sumapares, sumaimpares, digito, sumatotal;
    long int cos;
    sumapares = 0;
    sumaimpares = 0;
    for (i = 9; i >= 0; i--) {
        cos = cedula1 / 10;
        res = cedula1 % 10;
        *(A+i) = res;
        cedula1 = cos;
    }
    for (i = 0; i < 9; i += 2) {
        mul = *(A+i)* 2;
        if (mul > 9)
            mul -= 9;
        sumapares += mul;
    }
    for (i = 1; i < 8; i += 2)
        sumaimpares += *(A+i);

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    digito = 10 - res;

    if (digito == 10)
        digito = 0;
    if (digito == *(A+9)){
        delete[]A;
        return (true);

    }else{
        delete[] A;
        return (false);
    }
}

string* Persona::transformarMayusculas(string* cadena) {
    for (int i = 0; i < cadena->length(); i++) {
        (*cadena)[i] = toupper((*cadena)[i]);
    }
    return cadena;
}
void Persona::guardarDatos(string* &nombre1, string* &nombre2, string* &apellido, string cedula,string cifrado, string* &clave) {
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        string correo = crearCorreo(*nombre(nombre1, nombre2, apellido));
        archivo << "Cedula: " << cedula << endl;
        archivo << "Nombre1: " << *transformarMayusculas(nombre1) << endl;
        if(nombre2 == NULL){
            archivo << "Nombre2: N/A" << endl;
        }
        else{
            archivo << "Nombre2: " << *transformarMayusculas(nombre2) << endl;
        }
        archivo << "Apellido: " << *transformarMayusculas(apellido) << endl;
        archivo << "Correo: " << correo << endl;
        archivo << "Clave: " << *clave << endl;
        archivo << "Clave cifrada: " << cifrado << endl;
        archivo << "------------------------------------------" << endl;
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
}


void Persona::mostrarContenido(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cerr << "No se han registrado personas " << std::endl;
    }
}

void Persona :: limpiarArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << "";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}
