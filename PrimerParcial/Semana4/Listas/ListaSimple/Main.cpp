#include <iostream>
#include "ListasSimples.cpp"
int main(){
    Nodo *lista = NULL;
    ListaSimples objeto;
    int dato = 0;
    int opcion;
    while(opcion != 5){
    cout << "\n1. Insertar elemento" << endl;
    cout << "2. Buscar elemento" << endl;
    cout << "3. Eliminar elemento" << endl;
    cout << "4. Mostrar lista" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;
    switch(opcion){
        case 1:
            cout << "Ingrese un dato: ";
            cin >> dato;
            objeto.insertar(lista,dato);
            break;
        case 2:
            objeto.buscar(lista,dato);
            break;
        case 3:
            objeto.eliminar(lista,dato);
            break;
        case 4:
            objeto.mostrar(lista);
            break;
        case 5:
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
    }
    }
}