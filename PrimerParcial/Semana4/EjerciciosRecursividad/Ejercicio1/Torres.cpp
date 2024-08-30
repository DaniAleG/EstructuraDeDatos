#include <iostream>
#include <functional>
#include "Torres.h"
using namespace std;
template <typename T>
Torres<T>::Torres() {
    // La lambda usa un puntero a la instancia de Torres para llamarse a sí misma
    torresHanoi = [this](T num, char origen, char destino, char auxiliar) {
        auto lambda = [this](T n, char from, char to, char aux) -> void {
            if (n == 1) {
                std::cout << "Mover disco 1 desde " << from << " hasta " << to << std::endl;
                return;
            }
            torresHanoi(n - 1, from, aux, to);
            std::cout << "Mover disco " << n << " desde " << from << " hasta " << to << std::endl;
            torresHanoi(n - 1, aux, to, from);
        };
        lambda(num, origen, destino, auxiliar);
    };
}
template <typename T>
Torres<T>::~Torres() {
    // Destructor por defecto
}