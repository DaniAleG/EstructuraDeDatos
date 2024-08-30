#include <iostream>
#include <stdlib.h>
#include "Ingresar.h"
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <cctype>

using namespace std;

Ingresar::Ingresar() {
    primero = nullptr;
    ultimo = nullptr;
}

Ingresar::~Ingresar() {
    Nodo* actual = primero;
    while (actual) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}
void Ingresar :: ingresarInicio(string dato){
    Nodo* nuevo = new Nodo();
    if(this->primero == NULL){
        this->primero = nuevo;
        this->ultimo = nuevo;
    }else{
        nuevo->setSiguiente(this->primero);
        this->primero->setAnterior(nuevo);
        this->primero = nuevo;
    }
    cout << "Elemento " << dato << " insertado correctamente" << endl;
}

string Ingresar :: crearCorreo(string nombre){
    Nodo* nuevo = new Nodo();
    
    int contador = 0;
    if(this->primero == NULL){
        this->primero = nuevo;
        this->ultimo = nuevo;
        this->primero->setSiguiente(this->primero);
        this->primero->setAnterior(this->ultimo);
    }else{
        nuevo->setSiguiente(this->primero);
        nuevo->setAnterior(this->ultimo);
        this->primero->setAnterior(nuevo);
        this->ultimo->setSiguiente(nuevo);
        this->primero = nuevo;
    }
    string correo = nombre + "@espe.edu.ec";

    string correoValidado = anadirNumero(correo,nombre,contador);
    nuevo->setDato(correoValidado);
    return correoValidado;
}
string Ingresar::anadirNumero(string correo, string inicio, int contador) {
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


string Ingresar :: transformarMinusculas(string cadena) {
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = tolower(cadena[i]);
    }
    return cadena;
}

string Ingresar :: nombre(string nombre1, string nombre2, string apellido){
    string cadena;
    cadena += tolower(nombre1[0]);
    cadena += tolower(nombre2[0]);
    cadena += transformarMinusculas(apellido);
    return cadena;
}

string Ingresar :: validar(const char* msj) {
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
}



void Ingresar::guardarDatos(string nombre1, string nombre2, string apellido) {
    ofstream archivo("datos.txt", ios::app);
    if (archivo.is_open()) {
        string correo = crearCorreo(nombre(nombre1, nombre2, apellido));
        archivo << "Nombre: " << nombre1 << " " << nombre2 << " " << apellido << endl;
        archivo << "Correo: " << correo << endl;
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
}
void Ingresar ::  mostrarContenido(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}