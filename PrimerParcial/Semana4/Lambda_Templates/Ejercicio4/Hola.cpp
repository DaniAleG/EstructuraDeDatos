#include <iostream>
#include <cstdlib>
#include <cstdio>

typedef int entero;

int main() {
    int t;
    int* ptr = new entero[10];
    std::cout << "Ingrese el tamaño " << std::endl;
    std::cin >> t;

    // Lambda para ingreso de datos
    auto ingreso = [](int* p, int t) {
        for (int i = 0; i < t; ++i) {
            std::cin >> p[i];
        }
    };

    // Lambda para impresión de datos
    auto impresion = [](int* p, int t) {
        std::cout << "{ ";
        for (int i = 0; i < t; ++i) {
            std::cout << p[i] << " ";
        }
        std::cout << "}" << std::endl;
    };

    // Lambda para procesar datos
    auto proceso = [](int* p, int t) {
        int e;
        std::cout << "\nIngrese el escalar: ";
        std::cin >> e;
        for (int i = 0; i < t; ++i) {
            p[i] *= e;
        }
    };

    ingreso(ptr, t);
    impresion(ptr, t);
    proceso(ptr, t);
    impresion(ptr, t);

    delete[] ptr;
    return 0;
}
