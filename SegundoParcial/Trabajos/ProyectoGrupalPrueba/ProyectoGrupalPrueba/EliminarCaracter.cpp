#include "EliminarCaracter.h"
#include "../ProyectoGrupalPrueba(2)/ListaSimple/NodoSimple.h"
#include "../ProyectoGrupalPrueba(2)/ListaDoble/NodoDoble.h"
#include "../ProyectoGrupalPrueba(2)/ListaCircular/NodoCircular.h"
template<typename Nodo>
std::string EliminarCaracter<Nodo>::eliminarCaracterCadenaLambda(const std::string& str, char c) {
    std::string resultado;
    auto eliminar = [&resultado, c](char ch) {
        if (ch != c) {
            resultado += ch;
        }
    };
    for (char ch : str) {
        eliminar(ch);
    }
    return resultado;
}

template<typename Nodo>
void EliminarCaracter<Nodo>::eliminarCaracterListaRecursiva(Nodo* actual, char caracter, const std::string& atributo) {
    if (actual != nullptr) {
        std::string valor;
        if (atributo == "apellido") {
            valor = actual->getApellido();
        } else if (atributo == "nombre") {
            valor = actual->getPrimerNombre();
        } else if (atributo == "cedula") {
            valor = actual->getNumCedula();
        }
        valor = eliminarCaracterCadenaLambda(valor, caracter);
        
        if (atributo == "apellido") {
            actual->setApellido(valor);
        } else if (atributo == "nombre") {
            actual->setPrimerNombre(valor);
        } else if (atributo == "cedula") {
            actual->setNumCedula(valor);
        }
        std::cout << "Atributo modificado: " << valor << std::endl;
        eliminarCaracterListaRecursiva(actual->getSiguiente(), caracter, atributo);
    }
}

template<typename Nodo>
void EliminarCaracter<Nodo>::eliminarCaracterListaCircular(Nodo* cabeza, char caracter, const std::string& atributo) {
    if (cabeza == nullptr) {
        return;
    }

    Nodo* actual = cabeza;
    do {
        std::string valor;
        if (atributo == "apellido") {
            valor = actual->getApellido();
        } else if (atributo == "nombre") {
            valor = actual->getPrimerNombre();
        } else if (atributo == "cedula") {
            valor = actual->getNumCedula();
        }
        valor = eliminarCaracterCadenaLambda(valor, caracter);
        
        if (atributo == "apellido") {
            actual->setApellido(valor);
        } else if (atributo == "nombre") {
            actual->setPrimerNombre(valor);
        } else if (atributo == "cedula") {
            actual->setNumCedula(valor);
        }
        std::cout << "Atributo modificado: " << valor << std::endl;

        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

template class EliminarCaracter<NodoSimple<std::string>>;
template class EliminarCaracter<NodoDoble<std::string>>;
template class EliminarCaracter<NodoCircular<std::string>>;