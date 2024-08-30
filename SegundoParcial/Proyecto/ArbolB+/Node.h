#ifndef NODO_H
#define NODO_H

#include <vector>

class Nodo {
public:
    bool esHoja;
    std::vector<int> claves;
    std::vector<Nodo*> hijos;
    Nodo* siguiente;  // Siguiente nodo hoja en el árbol

    Nodo(bool hoja);

    void insertar(int clave);
    void eliminar(int clave);
};

#endif  // NODO_H
