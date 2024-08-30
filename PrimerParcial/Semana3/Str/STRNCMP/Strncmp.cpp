#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char cadenita1[] = "cesar";
    char cadenita2[] = "cesarin";
    int resultado1 = strncmp(cadenita1,cadenita2,7);
    int resultado2 = strncmp(cadenita1,cadenita2,5);
    std :: cout << "Al comparar los 7 primeros caracteres de la cadena1 y la cadena2, el resultado es: " << resultado1 << std :: endl;
    std :: cout << "Al comparar los 5 primeros caracteres de la cadena1 y la cadena2, el resultado es: " << resultado2 << std :: endl;
}