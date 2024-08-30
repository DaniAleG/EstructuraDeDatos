#include <iostream>
#include "Recuperacion.cpp"
// Función principal
int main() {
    ListaSimple objeto;
    Nodo *lista1 = nullptr;
    Nodo *lista2 = nullptr;
    int dato = 0, opcion = 1;

    while (opcion != 2) {
        std::string datoStr = validar("Ingrese un dato: ");
        dato = std::stoi(datoStr); // Convertir el string a entero

        objeto.insertar(lista1, dato);

        // Obtener el dígito único sumado y reducirlo a un dígito
        int digitoUnico = sumarDigitosLista(dato);
        objeto.insertar(lista2, digitoUnico);

        std::string opcionStr = validar("Desea continuar? \n1.Si\n2.No\nIngrese una opcion: ");
        opcion = std::stoi(opcionStr);
        while (opcion < 1 || opcion > 2) {
            std::cout << "Opcion incorrecta, ingrese una opcion valida: ";
            opcionStr = validar("Ingrese una opcion: ");
            opcion = std::stoi(opcionStr);
        }
    }

    std::cout << "Lista 1:" << std::endl;
    objeto.imprimir(lista1);
    
    std::cout << "Lista 2:" << std::endl;
    objeto.imprimir(lista2);

    return 0;
}
