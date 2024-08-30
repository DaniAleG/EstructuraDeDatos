/*
    UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
    Problema: Ejemplos tipos datos abstractos - Persona
    Autor: César González
    Fecha de Creación: 07/05/2024       Fecha de Modificación: 07/05/2024
    */

#include <iostream>
using namespace std;

typedef struct Persona{
    string nombre;
    int edad;
    string genero;
};
Persona ingresarPersona();
void mostrarPersona(Persona persona);

int main(){
    Persona p;
    p = ingresarPersona();
    mostrarPersona(p);
};
Persona ingresarPersona(){
    Persona persona;
    std::cout << "Ingrese el nombre de la persona: ";
    std::cin >> persona.nombre;
    std::cout << "Ingrese la edad de la persona: ";
    std::cin >> persona.edad;
    while (persona.edad <= 0){
        std::cout << "Edad no valida, ingrese nuevamente: ";
        cin >> persona.edad;
    };
    std::cout << "Ingrese el genero de la persona: ";
    std::cin >> persona.genero;
    return persona;
};
void mostrarPersona(Persona persona){
    cout << "El nombre de la persona es: " << persona.nombre << "\n";
    cout << "La edad de la persona es: " << persona.edad << "\n";
    cout << "El genero de la persona es: " << persona.genero << "\n";
};