#include <iostream>
#include "ListaDoble.h"
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "../TipoOrdenamiento.h"
#include "../Buscador.h"
#include "../EliminarCaracter.h"
using namespace std;

void gotoxyDoble(int x, int y);
void printMenuDoble(const char* menu[], int size, int currentSelection);
void menuOrdenarCaracteresDoble(ListaDoble<string>& lista, TipoOrdenamiento tipoOrdenamiento);
void menuBuscarDoble(int tipoBusqueda);
void menuBusquedaDoble();

void mainDoble(TipoOrdenamiento tipoOrdenamiento) {
    system("cls");
    ListaDoble<string> lista;
    string numCedula, primerNombre, apellido, linea;

    const char* menu[] = {
        "Ingresar datos",
        "Buscar datos",
        "Eliminar datos",
        "Mostrar datos",
        "Ordenar por apellido",
        "Ordenar por nombre",
        "Ordenar por cedula",
        "Ordenar caracteres",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;
    
    do {
        system("cls");
        cout << "\t\t.:MENU DE REGISTRO DE USUARIO (Lista doble):." << endl;
        printMenuDoble(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                switch (currentSelection) {
                    case 0: { 
                        do {
                            numCedula = lista.ingresarCedula("Ingrese el numero de cedula");
                            if (!lista.esNumeroCedulaValido(numCedula)) {
                                cout << "\n>> El numero de cedula ingresado no corresponde a una cedula ecuatoriana.\n" << endl;
                                continue;
                            }

                            long int cedulaLong;
                            try {
                                cedulaLong = stol(numCedula);
                            } catch (const exception &e) {
                                cout << "\nEl numero de cedula no es valido. Intentalo de nuevo.\n" << endl;
                                continue;
                            }

                            if (!lista.validarCedula(cedulaLong)) {
                                cout << "\nEl numero de cedula no es valido. Intentalo de nuevo.\n" << endl;
                                continue;
                            }
                            if (lista.cedulaRepetida(numCedula)) {
                                cout << "\nEl numero de cedula ya existe. No se puede insertar.\n" << endl;
                                continue;
                            }
                            break;
                        } while (true);

                        primerNombre = lista.ingresarLetras("Ingrese el nombre");
                        apellido = lista.ingresarLetras("Ingrese el apellido");

                        lista.insertar(numCedula, primerNombre, apellido);
                        cout << "Datos ingresados correctamente." << endl;
                        break;
                    }
                    case 1: { 
                        menuBusquedaDoble();
                        break;
                    }
                    case 2: { 
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            numCedula = lista.ingresarCedula("Ingrese el numero de cedula a eliminar");
                            if (!lista.esNumeroCedulaValido(numCedula)) {
                                cout << "\nEl numero de cedula debe contener solo digitos y tener exactamente 10 digitos.\n" << endl;
                            } else {
                                lista.eliminar(numCedula);
                            }
                        }
                        break;
                    }
                    case 3: { 
                        lista.mostrar();
                        break;
                    }
                    case 4: {
                        lista.resetLista();
                        lista.cargarDesdeArchivo();
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenar([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getApellido() < b->getApellido();
                                });
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarConBurbuja([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getApellido() < b->getApellido();
                                });
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarConQuickSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getApellido() < b->getApellido();
                                });
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarConShellSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getApellido() < b->getApellido();
                                });
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarConDistribucion([](NodoDoble<string>* a) {
                                    return a->getApellido();
                                });
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarConRadix([](NodoDoble<string>* a) {
                                    return a->getApellido();
                                });
                            }
                            cout << "Lista ordenada por apellidos." << endl;
                        }
                        break;
                    }
                    case 5: { 
                        lista.resetLista();
                        lista.cargarDesdeArchivo();
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenar([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getPrimerNombre() < b->getPrimerNombre();
                                });
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarConBurbuja([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getPrimerNombre() < b->getPrimerNombre();
                                });
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarConQuickSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getPrimerNombre() < b->getPrimerNombre();
                                });
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarConShellSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getPrimerNombre() < b->getPrimerNombre();
                                });
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarConDistribucion([](NodoDoble<string>* a) {
                                    return a->getPrimerNombre();
                                });
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarConRadix([](NodoDoble<string>* nodo) {
                                    return nodo->getPrimerNombre();
                                });
                            }
                            cout << "Lista ordenada por nombres." << endl;
                        }
                        break;
                    }
                    case 6: { 
                        lista.resetLista();
                        lista.cargarDesdeArchivo();
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenar([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getNumCedula() < b->getNumCedula();
                                });
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarConBurbuja([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getNumCedula() < b->getNumCedula();
                                });
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarConQuickSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getNumCedula() < b->getNumCedula();
                                });
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarConShellSort([](NodoDoble<string>* a, NodoDoble<string>* b) {
                                    return a->getNumCedula() < b->getNumCedula();
                                });
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarConDistribucion([](NodoDoble<string>* a) {
                                    return a->getNumCedula();
                                });
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarConRadix([](NodoDoble<string>* nodo) {
                                    return nodo->getNumCedula();
                                });
                            }
                            cout << "Lista ordenada por cedulas." << endl;
                        }
                        break;
                    }
                    case 7: { 
                        menuOrdenarCaracteresDoble(lista, tipoOrdenamiento);
                        break;
                    }
                    case 8: 
                        cout << "Saliendo del programa..." << endl;
                        return; 
                    default:
                        cout << "Opcion invalida. Intentalo nuevamente." << endl;
                        break;
                }
                if (currentSelection != 8) {
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}

void gotoxyDoble(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenuDoble(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; ++i) {
        if (i == currentSelection) {
            cout << "> " << menu[i] << " <" << endl;
        } else {
            cout << "  " << menu[i] << endl;
        }
    }
}

void menuOrdenarCaracteresDoble(ListaDoble<string>& lista, TipoOrdenamiento tipoOrdenamiento) {
    const char* menu[] = {
        "Ordenar caracteres de cedula",
        "Ordenar caracteres de nombre",
        "Ordenar caracteres de apellido",
        "Mostrar caracteres ordenados",
        "Eliminar caracter de atributo",
        "Volver"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU ORDENAR CARACTERES:." << endl;
        printMenuDoble(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: 
                switch (currentSelection) {
                    case 0: { 
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenarCaracteresEnAtributo("cedula");
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarCaracteresBurbuja("cedula");
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarCaracteresQuickSort("cedula");
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarCaracteresShellSort("cedula");
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarCaracteresDistribucion("cedula");
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarCaracteresRadix("cedula");
                            }
                            cout << "Caracteres de las cedulas ordenados y guardados en usuariosCaracteres.txt." << endl;
                        }
                        break;
                    }
                    case 1: { 
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenarCaracteresEnAtributo("nombre");
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarCaracteresBurbuja("nombre");
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarCaracteresQuickSort("nombre");
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarCaracteresShellSort("nombre");
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarCaracteresDistribucion("nombre");
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarCaracteresRadix("nombre");
                            }
                            cout << "Caracteres de los nombres ordenados y guardados en usuariosCaracteres.txt." << endl;
                        }
                        break;
                    }
                    case 2: { 
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoOrdenamiento == INTERCAMBIO) {
                                lista.ordenarCaracteresEnAtributo("apellido");
                            } else if (tipoOrdenamiento == BURBUJA) {
                                lista.ordenarCaracteresBurbuja("apellido");
                            } else if (tipoOrdenamiento == QUICKSORT) {
                                lista.ordenarCaracteresQuickSort("apellido");
                            } else if (tipoOrdenamiento == SHELLSORT) {
                                lista.ordenarCaracteresShellSort("apellido");
                            } else if (tipoOrdenamiento == DISTRIBUCION) {
                                lista.ordenarCaracteresDistribucion("apellido");
                            } else if (tipoOrdenamiento == RADIX) {
                                lista.ordenarCaracteresRadix("apellido");
                            }   
                            cout << "Caracteres de los apellidos ordenados y guardados en usuariosCaracteres.txt." << endl;
                        }
                        break;
                    }
                    case 3: { 
                        lista.mostrarCaracteresOrdenados();
                        break;
                    }
                    case 4: {
                        if (lista.listaVacia()) {
                            cout << "Lista vacía. No se ha registrado ningún usuario." << endl;
                        } else {
                            EliminarCaracter<NodoDoble<string>> eliminador;
                            char caracter;
                            string atributo;

                            cout << "Ingrese el carácter a eliminar: ";
                            cin >> caracter;
                            
                            cout << "Ingrese el atributo a modificar (apellido, nombre, cedula): ";
                            cin >> atributo;

                            NodoDoble<string>* cabeza = lista.getPrimero();
                            eliminador.eliminarCaracterListaRecursiva(cabeza, caracter, atributo);
                        }
                        break;
                    }

                    case 5:
                        return;
                    default:
                        cout << "Opcion invalida. Intentalo nuevamente." << endl;
                        break;
                }
                if (currentSelection != 5) {
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}
void menuBuscarDoble(int tipoBusqueda) {
    ListaDoble<string> lista;
    const char* menu[] = {
        "Buscar por cedula",
        "Buscar por nombre",
        "Buscar por apellido",
        "Volver"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU DE BUSQUEDA:." << endl;
        printMenuDoble(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13:
                switch (currentSelection) {
                    case 0: {
                         if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if(tipoBusqueda == SECUENCIAL){
                                string numCedula = lista.ingresarCedula("Ingrese el numero de cedula a buscar");
                                Buscador<NodoDoble<string>>::buscarSecuencial(lista.getPrimero(), numCedula, "cedula");
                            } else if (tipoBusqueda == BINARIA) {
                                string numCedula = lista.ingresarCedula("Ingrese el numero de cedula a buscar");
                                Buscador<NodoDoble<string>>::buscarBinario(lista.getPrimero(), numCedula, "cedula");
                            } else if (tipoBusqueda == HASH) {
                                 string numCedula = lista.ingresarCedula("Ingrese el numero de cedula a buscar");
                                Buscador<NodoDoble<string>>::buscarTablasHash(lista.getPrimero(), numCedula, "cedula");
                            }
                        }
                        break;
                    }
                    case 1: {
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoBusqueda == SECUENCIAL) {
                                string primerNombre = lista.ingresarLetras("Ingrese el nombre a buscar");
                                primerNombre = lista.convertirMayusculas(primerNombre);
                                Buscador<NodoDoble<string>>::buscarSecuencial(lista.getPrimero(), primerNombre, "nombre");
                            } else if (tipoBusqueda == BINARIA) {
                                string primerNombre = lista.ingresarLetras("Ingrese el nombre a buscar");
                                primerNombre = lista.convertirMayusculas(primerNombre);
                                Buscador<NodoDoble<string>>::buscarBinario(lista.getPrimero(), primerNombre, "nombre");
                            } else if (tipoBusqueda == HASH) {
                                string primerNombre = lista.ingresarLetras("Ingrese el nombre a buscar");
                                primerNombre = lista.convertirMayusculas(primerNombre);
                                Buscador<NodoDoble<string>>::buscarTablasHash(lista.getPrimero(), primerNombre, "nombre"); 
                            }
                        }   
                        break;
                    }
                    case 2: {
                        if (lista.listaVacia()) {
                            cout << "Lista vacia. No se ha registrado ningun usuario." << endl;
                        } else {
                            if (tipoBusqueda == SECUENCIAL) {
                                string apellido = lista.ingresarLetras("Ingrese el apellido a buscar");
                                apellido = lista.convertirMayusculas(apellido);
                                Buscador<NodoDoble<string>>::buscarSecuencial(lista.getPrimero(), apellido, "apellido");
                            } else if (tipoBusqueda == BINARIA) {
                                string apellido = lista.ingresarLetras("Ingrese el apellido a buscar");
                                apellido = lista.convertirMayusculas(apellido);
                                Buscador<NodoDoble<string>>::buscarBinario(lista.getPrimero(), apellido, "apellido");
                            } else if (tipoBusqueda == HASH) {
                                string apellido = lista.ingresarLetras("Ingrese el apellido a buscar");
                                apellido = lista.convertirMayusculas(apellido);
                                Buscador<NodoDoble<string>>::buscarTablasHash(lista.getPrimero(), apellido, "apellido"); 
                            }
                        }
                        break;
                    }
                    case 3:
                        return;
                }
                if (currentSelection != 3) {
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}
void menuBusquedaDoble(){
    const char* menu[] = {
        "Busqueda secuencial",
        "Busqueda binaria",
        "Busqueda hash",
        "Volver"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU DE BUSQUEDA:." << endl;
        printMenuDoble(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: 
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: 
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13:
                if(currentSelection == 3){
                    return;
                } else {
                    menuBuscarDoble(currentSelection);
                }
                break;
        }
    } while (true);
}