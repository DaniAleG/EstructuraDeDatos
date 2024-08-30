#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char cadena1[] = "cesar";
    char cadena2[] = "gonzalez";
    char cadena3[] = "cesar";
    int resultado1 = strcmp(cadena1,cadena2);
    int resultado2 = strcmp(cadena2,cadena3);
    int resultado3 = strcmp(cadena1,cadena3);
    std :: cout << "Comparando la cadena 1 "<< cadena1 << " y la cadena 2 " << cadena2<< " obtenemos: "  << resultado1 << std :: endl;
    std :: cout << "Comparando la cadena 2 "<< cadena2 << " y la cadena 3 " << cadena3<< " obtenemos: "  << resultado2 << std :: endl;
    std :: cout << "Comparando la cadena 1 "<< cadena1 << " y la cadena 3 " << cadena3<< " obtenemos: "  << resultado3 << std :: endl;
}