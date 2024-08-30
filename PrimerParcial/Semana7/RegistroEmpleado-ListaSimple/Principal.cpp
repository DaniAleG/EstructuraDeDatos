#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Persona.cpp"
#include "Empleado.cpp"
#include "Nodo.cpp"
using namespace std;

int main() {
    Persona* objeto = new Persona();
    Empleado* empleado = new Empleado();    
    int opcion = 1, opcion1=1;
    string *nombre1, *nombre2, *apellido, *inicio, correo, cedula, cedulaemp, *clave, cifrado;
    bool vced1, vced2=false, vced3;
    string txt = "datos.txt";
    string txt1 = "empleados.txt";
    string txt2 = "contador.txt";
    double sueldo = 0;  
    empleado->crearArchivoEmpleado(txt1);
    int cont = empleado->obtenerContador();

    do {
        cout << "MENU\n1.-Registrar Persona\n2.-Registrar Empleado\n3.- Mostrar\n4.-Limpiar\n5.-Salir\n";
        opcion = stoi(objeto->validarNumeros("Ingrese una opcion: "));

        switch (opcion) {
            case 1:
                cedula = objeto->validarNumeros("Ingrese su cedula: ");
                while (cedula.length() != 10) {
                    cout << "La cedula debe tener 10 digitos" << endl;
                    cedula = objeto->validarNumeros("Ingrese su cedula: ");
                }
                vced1 = objeto->validarCedula(cedula);
                vced2 = objeto->datoRepetido(cedula);

                while (vced1 == false || vced2 == true) {
                    if (vced1 == false) {
                        cout << "Cedula no existe" << endl;
                        cedula = objeto->validarNumeros("Ingrese su cedula: ");
                        while (cedula.length() != 10) {
                            cout << "La cedula debe tener 10 digitos" << endl;
                            cedula = objeto->validarNumeros("Ingrese su cedula: ");
                        }
                        vced1 = objeto->validarCedula(cedula);
                    }
                    if (vced2 == true) {
                        cout << "Cedula ya ha sido ingresada" << endl;
                        cedula = objeto->validarNumeros("Ingrese su cedula: ");
                        while (cedula.length() != 10) {
                            cout << "La cedula debe tener 10 digitos" << endl;
                            cedula = objeto->validarNumeros("Ingrese su cedula: ");
                        }
                        vced1 = objeto->validarCedula(cedula);
                        vced2 = objeto->datoRepetido(cedula);
                    }
                }

                objeto->ingresarInicio(cedula);
                nombre1 = new string(objeto->validarLetras("Ingrese su primer nombre: "));
                objeto->ingresarInicio(*nombre1);
                nombre2 = new string(objeto->validarNombre2("Ingrese su segundo nombre, si no tiene presione enter: "));
                objeto->ingresarInicio(*nombre2);
                apellido = new string(objeto->validarLetras("Ingrese su apellido: "));
                objeto->ingresarInicio(*apellido);
                clave = objeto->contrasenia(nombre1, nombre2, apellido);
                cifrado = objeto->cifradoCesar(clave);
                inicio = objeto->nombre(nombre1, nombre2, apellido);
                correo = objeto->crearCorreo(*inicio);
                objeto->guardarDatos(nombre1, nombre2, apellido, cedula, cifrado, clave);
                cont ++;
                break;

            case 2:
                    
                    if(cont == 0){
                        cout << "No hay personas registrados" << endl;
                        break;
                    }
                    
                    cedulaemp = objeto->validarNumeros("Ingrese la cedula del empleado: ");
                    while (cedulaemp.length() != 10) {
                        cout << "La cedula debe tener 10 digitos" << endl;
                        cedulaemp = objeto->validarNumeros("Ingrese la cedula del empleado: ");
                    }
                    vced1 = objeto->validarCedula(cedulaemp);
                    while (vced1 == false) {
                        cout << "Cedula no existe" << endl;
                        cedulaemp = objeto->validarNumeros("Ingrese la cedula del empleado: ");
                        while (cedulaemp.length() != 10) {
                            cout << "La cedula debe tener 10 digitos" << endl;
                            cedulaemp = objeto->validarNumeros("Ingrese la cedula del empleado: ");
                        }
                        vced1 = objeto->validarCedula(cedulaemp);
                    }
                    if(vced2==false){
                        vced2 = objeto->datoRepetido(cedulaemp);

                        if (vced2 == true){
                            vced3 = empleado->buscarEmpleado(cedulaemp);
                        }
                        if(vced3 == false){
                            sueldo = stod(empleado->validarSueldo("Ingrese el sueldo del empleado: "));
                            empleado->setSueldo(sueldo);
                            empleado->ingresarInicio(cedulaemp + " " + to_string(sueldo));
                            empleado->guardarDatos(empleado->crearIdEmpleado(), sueldo, cedulaemp);
                            cout << "Empleado registrado correctamente" << endl;
                        }else{
                            cout << "Persona no esta registrada" << endl;
                            break;
                        }
                    
                    
            
                }
                break;           
                
            case 3:
                if(cont == 0){
                    cout << "No hay personas registrados" << endl;
                    break;
                }
                do {
                cout << "MENU MOSTRAR\n1.-Mostrar Personas\n2.-Mostrar Empleados\n3.-Salir\n";
                cout << "Ingrese una opcion: ";
                opcion1 = stoi(empleado->validarNumeros(""));
                switch (opcion1) {
                        case 1:
                            objeto->mostrarContenido(txt);
                            break;
                        case 2:
                            if(empleado->obtenerContador() == 0){
                                cout << "No hay empleados registrados" << endl;
                                break;
                            }
                            empleado->mostrarContenido(txt1);
                            break;
                        case 3:
                            cout << "Adio" << endl;
                            break;
                        default:
                            cout << "Opcion no valida, ingrese nuevamente: " << endl;
                            break;
                    }
                } while (opcion1 != 3);
                break;
            case 4:
                objeto->limpiarArchivo(txt);
                objeto->limpiarArchivo(txt1);
                objeto->limpiarArchivo(txt2);
                cout << "Archivo limpio" << endl;
                break;
            case 5:
                cout << "Adio" << endl;
                break;

            default:
                cout << "Opcion no valida, ingrese nuevamente: " << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}
