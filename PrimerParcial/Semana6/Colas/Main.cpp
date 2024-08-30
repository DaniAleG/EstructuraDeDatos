#include <iostream>
#include "Cola.h"

int main() {
    Cola<int> cola;

    cola.encolar(1);
    cola.encolar(2);
    cola.encolar(3);

    std::cout << "Frente de la cola: " << cola.obtenerFrente() << std::endl;
    cola.desencolar();

    std::cout << "Frente de la cola: " << cola.obtenerFrente() << std::endl;
    cola.desencolar();

    std::cout << "Frente de la cola: " << cola.obtenerFrente() << std::endl;
    cola.desencolar();

    if (cola.estaVacia()) {
        std::cout << "La cola esta vacia" << std::endl;
    }

    return 0;
}
