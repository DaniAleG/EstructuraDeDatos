#ifndef ICLAVE_H
#define ICLAVE_H

#include <string>
#include <iostream>

class IClave {
public:
    virtual ~IClave() = default; // Destructor virtual para asegurar la limpieza correcta
    virtual bool datoRepetido(std::string cedula) = 0; // Método virtual puro
    virtual std::string cifradoCesar(std::string* clave) = 0; // Método virtual puro
};

#endif // ICLAVE_H
