#include "Arbol.cpp"
#include <iostream>
int main() {
    Arbol arbol;

    // Expresión en notación polaca inversa
    std::string expresion;
    std::cout << "Introduce la expresion en notacion polaca inversa: ";
    std::getline(std::cin, expresion);
    arbol.dibujarArbolRPN(expresion);

    return 0;
}
