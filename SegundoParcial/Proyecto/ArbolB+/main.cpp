#include "BPlusTree.cpp"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <graphics.h>

#define CONTEO_OPCIONES_MENU 6  // Incrementar el conteo de opciones del menú a 6

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    std::string opcionesMenu[CONTEO_OPCIONES_MENU] = {
        "Insertar",
        "Eliminar",
        "Buscar",
        "Mostrar arbol",
        "Mostrar recorridos",
        "Salir"
    };

    std::cout << "-------------- Menu Arbol --------------\n";
    std::cout << "Seleccione una opcion:\n";
    for (int i = 0; i < CONTEO_OPCIONES_MENU; ++i) {
        if (i == opcionSeleccionada) {
            std::cout << "> " << opcionesMenu[i] << " <" << "\n";
        } else {
            std::cout << "   " << opcionesMenu[i] << "\n";
        }
    }
}

void dibujarNodo(int x, int y, const std::vector<int>& claves) {
    const int ancho = 100;
    const int alto = 20;
    const int margen = 10;

    setfillstyle(SOLID_FILL, LIGHTGREEN);
    setcolor(GREEN);
    rectangle(x, y, x + ancho * claves.size(), y + alto);
    floodfill(x + 1, y + 1, GREEN);

    setcolor(BLACK);
    for (int i = 0; i < claves.size(); ++i) {
        std::string claveStr = std::to_string(claves[i]);
        outtextxy(x + i * ancho + margen, y + margen, (char*)claveStr.c_str());
    }
}

void dibujarArbol(Nodo* nodo, int x, int y, int hGap) {
    if (!nodo) return;

    dibujarNodo(x, y, nodo->claves);

    if (!nodo->esHoja) {
        int xHijo = x - (nodo->hijos.size() - 1) * hGap / 2;
        for (Nodo* hijo : nodo->hijos) {
            setcolor(BLACK);
            line(x + 20, y + 20, xHijo + 20, y + 60);
            dibujarArbol(hijo, xHijo, y + 60, hGap / 2);
            xHijo += hGap;
        }
    }
}

void mostrarArbol(ArbolBPlus& arbol) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char*>(""));

    int anchoPantalla = getmaxwidth();
    int altoPantalla = getmaxheight();
    initwindow(anchoPantalla, altoPantalla, "Visualizacion de Arbol B+");

    setbkcolor(WHITE);
    cleardevice();

    dibujarArbol(arbol.obtenerRaiz(), anchoPantalla / 2, 50, 200);

    getch();
    closegraph();
}

void mostrarRecorridos(ArbolBPlus& arbol) {
    std::cout << "Recorrido Inorden: ";
    arbol.recorridoInOrden();

    std::cout << "\nRecorrido Preorden: ";
    arbol.recorridoPreOrden();

    std::cout << "\nRecorrido Posorden: ";
    arbol.recorridoPostOrden();

    std::cout << "\nPresione cualquier tecla para continuar...\n";
    _getch();
}

int main() {
    ArbolBPlus arbol(3);  // Inicializa el árbol B+ con un grado predeterminado
    int opcionSeleccionada = 0;
    char tecla;
    bool salir = false;
    int valor;

    do {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();
        switch (tecla) {
        case 72:  // Flecha arriba
            if (opcionSeleccionada > 0) {
                --opcionSeleccionada;
            }
            break;
        case 80:  // Flecha abajo
            if (opcionSeleccionada < CONTEO_OPCIONES_MENU - 1) {
                ++opcionSeleccionada;
            }
            break;
        case 13:  // Enter
            system("cls");
            switch (opcionSeleccionada) {
            case 0:  // Insertar
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> valor;
                arbol.insertar(valor);
                std::cout << "Valor insertado: " << valor << "\n";
                break;
            case 1:  // Eliminar
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> valor;
                std::cout << "Arbol antes de eliminar el valor:\n";
                mostrarArbol(arbol);
                arbol.eliminar(valor);
                std::cout << "Valor eliminado: " << valor << "\n";
                std::cout << "Arbol despues de eliminar el valor:\n";
                mostrarArbol(arbol);
                break;
            case 2:  // Buscar
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> valor;
                if (arbol.buscar(valor)) {
                    std::cout << "El dato " << valor << " si se encuentra en el arbol.\n";
                } else {
                    std::cout << "El dato " << valor << " no se encuentra en el arbol.\n";
                }
                break;
            case 3:  // Mostrar árbol
                mostrarArbol(arbol);
                break;
            case 4:  // Mostrar recorridos
                mostrarRecorridos(arbol);
                break;
            case 5:  // Salir
                salir = true;
                std::cout << "Saliendo...\n";
                break;
            }
            if (!salir) {
                std::cout << "Presione cualquier tecla para continuar...\n";
                _getch();
                system("cls");
            }
            break;
        }

    } while (!salir);

    return 0;
}

