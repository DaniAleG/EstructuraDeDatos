#include <iostream>
#include "Puntos.cpp"
using namespace std;

int main() {
    Puntos<int> p1(3, 4);
    Puntos<int> p2(0, 0);

    std::cout << "La distancia entre el punto 1 y el punto 2 es: " << p1.distancia(p2) << std::endl; 

    Puntos<double> p3(1.5, 2.5);
    Puntos<double> p4(4.0, 6.0);

    std::cout << "La distancia entre el punto 1 y el punto 2 es: " << p3.distancia(p4) << std::endl; 

    return 0;
}