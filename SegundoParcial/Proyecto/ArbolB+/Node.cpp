#include "Node.h"
#include <algorithm>

Nodo::Nodo(bool hoja) : esHoja(hoja), siguiente(nullptr) {}

void Nodo::insertar(int clave) {
    auto pos = std::lower_bound(claves.begin(), claves.end(), clave);
    claves.insert(pos, clave);
}

void Nodo::eliminar(int clave) {
    auto pos = std::lower_bound(claves.begin(), claves.end(), clave);
    if (pos != claves.end() && *pos == clave) {
        claves.erase(pos);
    }
}
