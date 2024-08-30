#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
#include "IClave.h"
#include "Nodo.h"
using namespace std;

class Persona : public IClave {
    private:
        Nodo* primero;
        Nodo* ultimo;
    public:
        Persona();
        ~Persona();
        void setPrimero(Nodo*);
        Nodo* getPrimero();
        void setUltimo(Nodo*);
        Nodo* getUltimo();
        void ingresarInicio(string);
        string crearCorreo(string);
        string* nombre(string*, string*, string*);
        string validarLetras(const char*);
        string validarNombre2(const char*);
        string validarNumeros(const char* msj);
        void guardarDatos(string*&, string*&, string*&, string,string,string*&);
        string anadirNumeroCorreo(string, string, int);
        string* transformarMinusculas(string*);
        void mostrarContenido(const string&);
        bool validarCedula(std::string cedula);
        bool datoRepetido(string) override;
        string* transformarMayusculas(string*);
        string* contrasenia(string* nombre1,string* nombre2,string* apellido);
        string cifradoCesar(string* contrasenia) override;
        string anadirNumeroClave(string clave, int contador);
        void limpiarArchivo(const string&);
};
#endif // PERSONA_H