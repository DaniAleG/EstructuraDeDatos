#include <iostream>
#include "Tetris.cpp"


using namespace std;

int main() {
    ListaSimple<string> lista;
    string nombre1, nombre2, nombre3;
    nombre1 = lista.ingresarLetras("Ingrese su nombre: ");
    lista.agregar(nombre1);
    nombre2 = lista.ingresarLetras("Ingrese su nombre: ");
    lista.agregar(nombre2);
    nombre3 = lista.ingresarLetras("Ingrese su nombre: ");
    lista.agregar(nombre3);
    system("cls");
    Tetris juego;
    juego.iniciar(lista);
    return 0;
}