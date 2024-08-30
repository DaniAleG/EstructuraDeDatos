#include "BPlusTree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

ArbolBPlus::ArbolBPlus(int grado) : raiz(new Nodo(true)), grado(grado) {}

Nodo* ArbolBPlus::obtenerRaiz() const {
    return raiz;
}

void ArbolBPlus::dividirHijo(Nodo* padre, int indice, Nodo* hijo) {
    Nodo* nuevoHijo = new Nodo(hijo->esHoja);
    int indiceMedio = grado / 2;

    nuevoHijo->claves.assign(hijo->claves.begin() + indiceMedio + (hijo->esHoja ? 0 : 1), hijo->claves.end());
    hijo->claves.resize(indiceMedio + (hijo->esHoja ? 0 : 1));

    if (!hijo->esHoja) {
        nuevoHijo->hijos.assign(hijo->hijos.begin() + indiceMedio + 1, hijo->hijos.end());
        hijo->hijos.resize(indiceMedio + 1);
    } else {
        nuevoHijo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoHijo;
    }

    padre->hijos.insert(padre->hijos.begin() + indice + 1, nuevoHijo);

    padre->claves.insert(padre->claves.begin() + indice, hijo->claves[indiceMedio]);

    if (!hijo->esHoja) {
        hijo->claves.resize(indiceMedio);
    }
}

void ArbolBPlus::insertarNoLleno(Nodo* nodo, int clave) {
    int i = nodo->claves.size() - 1;

    if (nodo->esHoja) {
        nodo->insertar(clave);
    } else {
        while (i >= 0 && clave < nodo->claves[i]) {
            i--;
        }
        i++;

        if (i < nodo->hijos.size() && nodo->hijos[i]->claves.size() == grado - 1) {
            dividirHijo(nodo, i, nodo->hijos[i]);
            if (clave > nodo->claves[i]) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], clave);
    }
}

void ArbolBPlus::insertar(int clave) {
    if (raiz->claves.size() == grado - 1) {
        Nodo* nuevaRaiz = new Nodo(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividirHijo(nuevaRaiz, 0, raiz);
        raiz = nuevaRaiz;
    }
    insertarNoLleno(raiz, clave);
}

void ArbolBPlus::eliminar(int clave) {
    if (!raiz) return;

    eliminarDeNodo(raiz, clave);

    if (raiz->claves.size() == 0 && !raiz->esHoja) {
        Nodo* temp = raiz;
        raiz = raiz->hijos[0];
        delete temp;
    }
}

void ArbolBPlus::eliminarDeNodo(Nodo* nodo, int clave) {
    int idx = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();

    if (nodo->esHoja) {
        if (idx < nodo->claves.size() && nodo->claves[idx] == clave) {
            nodo->claves.erase(nodo->claves.begin() + idx);
        }
    } else {
        if (idx < nodo->claves.size() && nodo->claves[idx] == clave) {
            if (nodo->hijos[idx]->claves.size() >= (grado + 1) / 2) {
                int clavePred = obtenerPredecesor(nodo->hijos[idx]);
                nodo->claves[idx] = clavePred;
                eliminarDeNodo(nodo->hijos[idx], clavePred);
            } else if (nodo->hijos[idx + 1]->claves.size() >= (grado + 1) / 2) {
                int claveSuce = obtenerSucesor(nodo->hijos[idx + 1]);
                nodo->claves[idx] = claveSuce;
                eliminarDeNodo(nodo->hijos[idx + 1], claveSuce);
            } else {
                fusionarNodos(nodo, idx);
                eliminarDeNodo(nodo->hijos[idx], clave);
            }
        } else {
            if (idx < nodo->hijos.size()) {
                if (nodo->hijos[idx]->claves.size() < (grado + 1) / 2) {
                    if (idx > 0 && nodo->hijos[idx - 1]->claves.size() >= (grado + 1) / 2) {
                        prestarDelAnterior(nodo, idx);
                    } else if (idx < nodo->hijos.size() - 1 && nodo->hijos[idx + 1]->claves.size() >= (grado + 1) / 2) {
                        prestarDelSiguiente(nodo, idx);
                    } else {
                        if (idx < nodo->hijos.size() - 1) {
                            fusionarNodos(nodo, idx);
                        } else {
                            fusionarNodos(nodo, idx - 1);
                        }
                    }
                }
                eliminarDeNodo(nodo->hijos[idx], clave);
            }
        }
    }
}

int ArbolBPlus::obtenerPredecesor(Nodo* nodo) {
    while (!nodo->esHoja) {
        nodo = nodo->hijos[nodo->hijos.size() - 1];
    }
    return nodo->claves[nodo->claves.size() - 1];
}

int ArbolBPlus::obtenerSucesor(Nodo* nodo) {
    while (!nodo->esHoja) {
        nodo = nodo->hijos[0];
    }
    return nodo->claves[0];
}

void ArbolBPlus::fusionarNodos(Nodo* padre, int idx) {
    Nodo* hijo = padre->hijos[idx];
    Nodo* hermano = padre->hijos[idx + 1];

    if (!hijo->esHoja) {
        hijo->claves.push_back(padre->claves[idx]);
        hijo->claves.insert(hijo->claves.end(), hermano->claves.begin(), hermano->claves.end());
        hijo->hijos.insert(hijo->hijos.end(), hermano->hijos.begin(), hermano->hijos.end());
    } else {
        hijo->claves.insert(hijo->claves.end(), hermano->claves.begin(), hermano->claves.end());
        hijo->siguiente = hermano->siguiente;
    }

    padre->claves.erase(padre->claves.begin() + idx);
    padre->hijos.erase(padre->hijos.begin() + idx + 1);

    delete hermano;
}

void ArbolBPlus::prestarDelAnterior(Nodo* padre, int idx) {
    Nodo* hijo = padre->hijos[idx];
    Nodo* hermano = padre->hijos[idx - 1];

    if (!hijo->esHoja) {
        hijo->hijos.insert(hijo->hijos.begin(), hermano->hijos.back());
        hermano->hijos.pop_back();

        hijo->claves.insert(hijo->claves.begin(), padre->claves[idx - 1]);
        padre->claves[idx - 1] = hermano->claves.back();
        hermano->claves.pop_back();
    } else {
        hijo->claves.insert(hijo->claves.begin(), hermano->claves.back());
        padre->claves[idx - 1] = hermano->claves.back();
        hermano->claves.pop_back();
    }
}

void ArbolBPlus::prestarDelSiguiente(Nodo* padre, int idx) {
    Nodo* hijo = padre->hijos[idx];
    Nodo* hermano = padre->hijos[idx + 1];

    if (!hijo->esHoja) {
        hijo->hijos.push_back(hermano->hijos.front());
        hermano->hijos.erase(hermano->hijos.begin());

        hijo->claves.push_back(padre->claves[idx]);
        padre->claves[idx] = hermano->claves.front();
        hermano->claves.erase(hermano->claves.begin());
    } else {
        hijo->claves.push_back(hermano->claves.front());
        padre->claves[idx] = hermano->claves.front();
        hermano->claves.erase(hermano->claves.begin());
    }
}

void ArbolBPlus::mostrar() {
    if (!raiz) return;

    std::queue<Nodo*> q;
    q.push(raiz);

    int nivel = 0;
    while (!q.empty()) {
        int conteoNodos = q.size();
        std::cout << "Nivel " << nivel << ": ";
        nivel++;

        while (conteoNodos > 0) {
            Nodo* nodo = q.front();
            q.pop();

            std::cout << "|";
            for (int clave : nodo->claves) {
                std::cout << " " << std::setw(4) << clave << " ";
            }
            std::cout << "|  ";

            if (!nodo->esHoja) {
                for (Nodo* hijo : nodo->hijos) {
                    q.push(hijo);
                }
            }

            conteoNodos--;
        }
        std::cout << "\n";
    }

    std::cout << "Enlaces entre hojas:\n";
    Nodo* actual = raiz;
    while (actual && !actual->esHoja) {
        actual = actual->hijos[0];
    }
    while (actual) {
        std::cout << "[";
        for (int clave : actual->claves) {
            std::cout << " " << clave << " ";
        }
        std::cout << "]";
        if (actual->siguiente) {
            std::cout << " -> ";
        }
        actual = actual->siguiente;
    }
    std::cout << "\n";
}

bool ArbolBPlus::buscar(int clave) const {
    Nodo* actual = raiz;
    
    while (actual) {
        int i = 0;
        while (i < actual->claves.size() && clave > actual->claves[i]) {
            i++;
        }

        if (i < actual->claves.size() && clave == actual->claves[i]) {
            return true;
        }

        if (actual->esHoja) {
            return false;
        } else {
            actual = actual->hijos[i];
        }
    }

    return false;
}

void ArbolBPlus::inOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    if (nodo->esHoja) {
        for (int clave : nodo->claves) {
            std::cout << clave << " ";
        }
        return;
    }

    for (size_t i = 0; i < nodo->claves.size(); ++i) {
        inOrden(nodo->hijos[i]);
        std::cout << nodo->claves[i] << " ";
    }

    inOrden(nodo->hijos[nodo->claves.size()]);
}

void ArbolBPlus::recorridoInOrden() {
    inOrden(raiz);
    std::cout << std::endl;
}

void ArbolBPlus::preOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    for (int clave : nodo->claves) {
        std::cout << clave << " ";
    }

    for (Nodo* hijo : nodo->hijos) {
        preOrden(hijo);
    }
}

void ArbolBPlus::recorridoPreOrden() {
    preOrden(raiz);
    std::cout << std::endl;
}

void ArbolBPlus::postOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    for (Nodo* hijo : nodo->hijos) {
        postOrden(hijo);
    }

    for (int clave : nodo->claves) {
        std::cout << clave << " ";
    }
}

void ArbolBPlus::recorridoPostOrden() {
    postOrden(raiz);
    std::cout << std::endl;
}

