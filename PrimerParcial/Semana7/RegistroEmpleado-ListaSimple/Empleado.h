#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>
#include "Persona.h"
#include "Nodo.h"
#include "IClave.h"

using namespace std;

class Empleado : public Persona {
    private:
        string idEmpleado;
        double sueldo;
        Persona* persona;
        Nodo* primero; // Puntero al primer nodo de la lista
        Nodo* ultimo;  // Puntero al último nodo de la lista

    public:
        Empleado();
        Empleado(string, double, Persona*);
        string getIdEmpleado();
        void setIdEmpleado(string);
        double getSueldo();
        void setSueldo(double);
        Persona* getPersona();
        void setPersona(Persona*);
        void mostrarEmpleado();
        ~Empleado();
        bool buscarEmpleado(const string&);
        //string crearIdEmpleado();
        void ingresarInicio(string dato);
        void mostrarLista(); // Método para mostrar la lista
        
        // Métodos para lista simple
        Nodo* getPrimero();
        Nodo* getUltimo();
        void setPrimero(Nodo* primero);
        void setUltimo(Nodo* ultimo);
    string validarSueldo(const char* msj);
        string crearIdEmpleado();
        void crearArchivoEmpleado(const string&);    
        bool buscarArchivo(const string&);
        void guardarDatos(string id, double sueldo, string cedula);
        int obtenerContador();
        void guardarContador(int contador);
        string formatearId(int contador);
        void mostrarContenido(const string&);
};

#endif // EMPLEADO_H
