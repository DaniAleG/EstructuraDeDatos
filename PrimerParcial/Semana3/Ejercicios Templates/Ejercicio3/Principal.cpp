#include <iostream>
#include "Contenedor.cpp"
int main(){
    Contenedor<int,double>datos1(3,4.5);
    Contenedor<std :: string, int>datos2("cesar",19);
    std :: cout << "Los primeros datos son: " << datos1.dato1 << ", " << datos1.dato2 << std :: endl;
    std :: cout << "Los segundos datos son: " << datos2.dato1 << ", " << datos2.dato2 << std :: endl;
}