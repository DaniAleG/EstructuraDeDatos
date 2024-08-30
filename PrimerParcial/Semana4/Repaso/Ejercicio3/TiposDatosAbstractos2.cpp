/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Ejemplos tipos datos abstractos - Vehiculo
    Autor: César González
    Fecha de Creación: 07/05/2024       Fecha de Modificación: 07/05/2024
    */

#include <iostream>
using namespace std;

typedef struct Vehiculo{
    string placa;
    string marca;
    int numeroAsientos;
    string color;
};

Vehiculo ingresarVehiculo();
void mostrarVehiculo(Vehiculo vehiculo);

int main(){
    Vehiculo v;
    v = ingresarVehiculo();
    mostrarVehiculo(v);
};
Vehiculo ingresarVehiculo(){
    Vehiculo vehiculo;
    cout << "Ingrese la placa del vehiculo: ";
    cin >> vehiculo.placa;
    cout << "Ingrese la marca del vehiculo: ";
    cin >> vehiculo.marca;
    cout << "Ingrese el numero de asientos del vehiculo: ";
    cin >> vehiculo.numeroAsientos;
    while(vehiculo.numeroAsientos < 2){
        cout << "Numero de asientos invalido, ingrese nuevamente: ";
        cin >> vehiculo.numeroAsientos;
    };
    cout << "Ingrese el color del vehiculo: ";
    cin >> vehiculo.color;
    return vehiculo;
};
void mostrarVehiculo(Vehiculo vehiculo){
    cout << "La placa del vehiculo es: " << vehiculo.placa << "\n";
    cout << "La placa del vehiculo es: " << vehiculo.marca << "\n";
    cout << "El numero de asientos del vehiculo es: " << vehiculo.numeroAsientos << "\n";
    cout << "El color del vehiculo es: " << vehiculo.color << "\n";
}