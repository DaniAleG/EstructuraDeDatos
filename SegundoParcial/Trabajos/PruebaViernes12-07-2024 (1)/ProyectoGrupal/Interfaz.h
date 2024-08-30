#ifndef INTERFAZ_H


#define INTERFAZ_H

#include <string>
#include <iostream>

using namespace std;
template <typename Nodo>
class Interfaz {
public:
    virtual ~Interfaz() = default; // Destructor virtual para asegurar la limpieza correcta
    //funcion recursiva lambda que reciva una lista y un caracter ingresado por teclado, mismo que sea borrado y se muestre la lista sin el caracter ingresado
// este caracter solo debe ser de la cedula
    virtual void eliminarCaracter(Nodo* lista, string caracter) = 0;
};
#endif // INTERFAZ_H