#include <iostream>
#include "MayorMenor.cpp"
using namespace std;
int main(){
    MayorMenor objeto;
    Nodo *lista = NULL;
    int dato = 0,opcion;
    
    while(opcion != 2){
        cout << "Ingrese un dato: ";
        cin >> dato;
        objeto.insertar(lista,dato);
        cout << "Desea continuar? \n1.Si\n2.No\nIngrese una opcion: ";
        cin >> opcion;
        while(opcion < 1 || opcion > 2){
            cout << "Opcion incorrecta, ingrese una opcion valida: ";
            cin >> opcion;
        }
    }
    objeto.imprimir(lista);
    objeto.mayor(lista);
    objeto.menor(lista);
    objeto.liberar(lista);
    return 0;
}