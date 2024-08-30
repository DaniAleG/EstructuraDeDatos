#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ingresar.cpp"
using namespace std;

int main (){
    Ingresar *objeto = new Ingresar();
    int opcion=1;
    string nombre1,nombre2,apellido, inicio,correo;
    string txt = "datos.txt";
    do{
        cout << "MENU\n1.-Registrarse\n2.-Mostrar\n3.-Salir\nIngrese una opcion:" ;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            nombre1 = objeto->validar("Ingrese su primer nombre: ");
            objeto->ingresarInicio(nombre1);
            nombre2 = objeto->validar("Ingrese su segundo nombre: ");
            objeto->ingresarInicio(nombre2);
            apellido = objeto->validar("Ingrese su apellido: ");
            objeto->ingresarInicio(apellido);
            inicio = objeto->nombre(nombre1,nombre2,apellido);
            correo = objeto -> crearCorreo(inicio); 
            objeto -> guardarDatos(nombre1,nombre2,apellido);
            break;
        case 2: 
            objeto ->mostrarContenido(txt);
            break;
        case 3:
            cout << "adio" << endl;
            break;
        default:
            break;
            
        }
    }while(opcion!=3);
}