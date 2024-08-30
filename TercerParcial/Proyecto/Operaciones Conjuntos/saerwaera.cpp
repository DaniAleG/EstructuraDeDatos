#include <iostream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
using namespace std;

// Definición de la clase ListaSimple
template <typename T>
class ListaSimple {
private:


public:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d, Nodo* s = nullptr) : dato(d), siguiente(s) {}
    };

    Nodo* cabeza;
    ListaSimple() : cabeza(nullptr) {}

    ~ListaSimple() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& dato) {
        if (buscar(dato) == nullptr) {
            cabeza = new Nodo(dato, cabeza);
        }
    }

    void mostrar() const {
        Nodo* actual = cabeza;
        cout << "{ ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << "}" << endl;
    }

    Nodo* buscar(const T& dato) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == dato) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool contains(const T& elemento) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == elemento) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    ListaSimple<T> unionList(const ListaSimple<T>& otra) const {
        ListaSimple<T> resultado;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            resultado.insertar(actual->dato);
            actual = actual->siguiente;
        }
        actual = otra.cabeza;
        while (actual != nullptr) {
            resultado.insertar(actual->dato);
            actual = actual->siguiente;
        }
        return resultado;
    }

    ListaSimple<T> interseccion(const ListaSimple<T>& otra) const {
        ListaSimple<T> resultado;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (otra.contains(actual->dato)) {
                resultado.insertar(actual->dato);
            }
            actual = actual->siguiente;
        }
        return resultado;
    }

    ListaSimple<T> diferencia(const ListaSimple<T>& otra, bool isDifferenceAB) const {
        ListaSimple<T> resultado;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (isDifferenceAB && !otra.contains(actual->dato)) {
                resultado.insertar(actual->dato);
            }
            if (!isDifferenceAB && otra.contains(actual->dato)) {
                resultado.insertar(actual->dato);
            }
            actual = actual->siguiente;
        }
        return resultado;
    }

    ListaSimple<T> diferenciaSimetrica(const ListaSimple<T>& otra) const {
        ListaSimple<T> resultado;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (!otra.contains(actual->dato)) {
                resultado.insertar(actual->dato);
            }
            actual = actual->siguiente;
        }
        actual = otra.cabeza;
        while (actual != nullptr) {
            if (!contains(actual->dato)) {
                resultado.insertar(actual->dato);
            }
            actual = actual->siguiente;
        }
        return resultado;
    }

    ListaSimple<T> complemento(const ListaSimple<T>& otra, bool complementoAB) const {
        return diferencia(otra, complementoAB);
    }
};

void gotoxyMain(int x, int y);
void printMenuMain(const char* menu[], int size, int currentSelection);
void operarConjuntosMenu(int conjuntoType);

template <typename T>
void ingresarConjunto(ListaSimple<T>& conjunto);
template <typename T>
void mostrarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B);
template <typename T>
void mostrarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B);
template <typename T>
void mostrarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B);
template <typename T>
void mostrarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B);
template <typename T>
void mostrarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B);

int main() {
    system("cls");

    const char* menu[] = {
        "Ingresar datos",
        "Salir"
    };
    int size = sizeof(menu) / sizeof(menu[0]);
    int currentSelection = 0;
    int key;

    do {
        system("cls");
        cout << "\t\t.:MENU PRINCIPAL:." << endl;
        printMenuMain(menu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: // Flecha abajo
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: // Enter
                if (currentSelection == 1) {
                    cout << "Saliendo del programa..." << endl;
                    return 0;
                } else {
                    operarConjuntosMenu(1); // Ir a la parte de ingresar cadenas de texto
                }
                break;
        }
    } while (true);

    return 0;
}

void gotoxyMain(int x, int y) {
    // Dependiente de Windows, considerar alternativa portable
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenuMain(const char* menu[], int size, int currentSelection) {
    for (int i = 0; i < size; ++i) {
        if (i == currentSelection) {
            cout << "> " << menu[i] << " <" << endl;
        } else {
            cout << "  " << menu[i] << endl;
        }
    }
}

class Dibujar {
public:
    template <typename T>
    void dibujarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
        ListaSimple<T> unionAB = A.unionList(B);
        initwindow(800, 600, "Union");
        setcolor(WHITE);
        
        // Establecer la posición del texto y dibujar el título
        outtextxy(350, 100, "A union B");
        
        circle(400, 300, 150); // Un solo círculo para la unión
        mostrarDatos(unionAB, 400, 300);
        getch();
        closegraph();
    }
    template <typename T>
    void dibujarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
        ListaSimple<T> interseccionAB = A.interseccion(B);
        ListaSimple<T> soloA = A.diferencia(B, true);
        ListaSimple<T> soloB = B.diferencia(A, true);
        
        initwindow(800, 600, "Interseccion");
        setcolor(WHITE);
        
        // Dibujar los círculos
        circle(350, 300, 100); // Conjunto A
        circle(450, 300, 100); // Conjunto B
        
        // Dibujar los títulos
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 200, "Conjunto A");
        outtextxy(500, 200, "Conjunto B");
        
        // Llenar la intersección
        setfillstyle(SOLID_FILL, LIGHTGREEN);
        floodfill(400, 300, WHITE); // Intersección
        
        // Mostrar los datos
        mostrarDatos(interseccionAB, 400, 300); // Datos de la intersección
        mostrarDatos(soloA, 300, 300); // Datos exclusivos de A
        mostrarDatos(soloB, 500, 300); // Datos exclusivos de B
        
        getch();
        closegraph();
    }

    template <typename T>
    void dibujarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B) {
        ListaSimple<T> diferenciaAB = A.diferencia(B, true);
        ListaSimple<T> diferenciaBA = B.diferencia(A, false);
        initwindow(800, 600, "Diferencia");
        setcolor(WHITE);
        
        // Dibujar título para A - B
        outtextxy(200, 200, "Conjunto A-B");
        // Dibujar círculo para A - B
        circle(250, 300, 100); // Conjunto A - B
        setfillstyle(SOLID_FILL, LIGHTRED);
        floodfill(250, 300, WHITE); // Diferencia A - B
        mostrarDatos(diferenciaAB, 250, 300); // Mostrar datos A - B
        
        // Dibujar título para B - A
        outtextxy(500, 200, "Conjunto B-A");
        // Dibujar círculo para B - A
        circle(550, 300, 100); // Conjunto B - A
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(550, 300, WHITE); // Diferencia B - A
        mostrarDatos(diferenciaBA, 550, 300); // Mostrar datos B - A
        
        getch();
        closegraph();
    }

    template <typename T>
    void dibujarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B) {
        ListaSimple<T> diferenciaSimetrica = A.diferenciaSimetrica(B);
        initwindow(800, 600, "Diferencia Simetrica");
        setcolor(WHITE);
        
        // Dibujar título para A Δ B
        outtextxy(370, 200, const_cast<char*>("A Δ B"));
        
        // Dibujar círculo para la diferencia simétrica
        circle(400, 300, 100); // Conjunto A Δ B
        
        // Llenar el área del círculo con color YELLOW
        setfillstyle(SOLID_FILL, YELLOW);
        floodfill(400, 300, WHITE); // Diferencia simétrica A Δ B
        
        // Mostrar los datos de la diferencia simétrica en el centro del círculo
        mostrarDatos(diferenciaSimetrica, 400, 300);
        
        getch();
        closegraph();
    }

    template <typename T>
    void dibujarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B) {
        ListaSimple<T> complementoA = A.complemento(B, true);
        ListaSimple<T> complementoB = B.complemento(A, true);
        
        initwindow(800, 600, "Complemento");
        setcolor(WHITE);
        
        // Dibujar título para el complemento de A
        outtextxy(200, 200, const_cast<char*>("Complemento de A"));
        // Dibujar círculo para el complemento de A
        circle(250, 300, 100); // Conjunto A
        setfillstyle(SOLID_FILL, MAGENTA);
        floodfill(250, 300, WHITE); // Complemento de A
        mostrarDatos(complementoA, 250, 300); // Mostrar datos del complemento de A
        
        // Dibujar título para el complemento de B
        outtextxy(500, 200, const_cast<char*>("Complemento de B"));
        // Dibujar círculo para el complemento de B
        circle(550, 300, 100); // Conjunto B
        setfillstyle(SOLID_FILL, CYAN);
        floodfill(550, 300, WHITE); // Complemento de B
        mostrarDatos(complementoB, 550, 300); // Mostrar datos del complemento de B
        
        getch();
        closegraph();
    }

private:
    template <typename T>
    void mostrarDatos(const ListaSimple<T>& conjunto, int x, int y) {
        setcolor(WHITE);
        int offset = 20;
        typename ListaSimple<T>::Nodo* actual = conjunto.cabeza;
        while (actual != nullptr) {
            outtextxy(x - 10, y + offset, const_cast<char*>(to_string(actual->dato).c_str()));
            offset += 20;
            actual = actual->siguiente;
        }
    }

    void mostrarDatos(const ListaSimple<string>& conjunto, int x, int y) {
        setcolor(WHITE);
        int offset = 20;
        ListaSimple<string>::Nodo* actual = conjunto.cabeza;
        while (actual != nullptr) {
            outtextxy(x - 10, y + offset, const_cast<char*>(actual->dato.c_str()));
            offset += 20;
            actual = actual->siguiente;
        }
    }
};
void operarConjuntosMenu(int conjuntoType) {
    Dibujar dibujar;
    const char* operMenu[] = {
        "Union",
        "Interseccion",
        "Diferencia",
        "Diferencia Simetrica",
        "Complemento",
        "Regresar"
    };
    int size = sizeof(operMenu) / sizeof(operMenu[0]);
    int currentSelection = 0;
    int key;

    ListaSimple<string> A_str, B_str;

    cout << "Conjunto A (cadenas de texto)" << endl;
    ingresarConjunto(A_str);
    cout << "Conjunto B (cadenas de texto)" << endl;
    ingresarConjunto(B_str);

    do {
        system("cls");
        cout << "\t\t.:MENU DE OPERACIONES:." << endl;
        printMenuMain(operMenu, size, currentSelection);

        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (currentSelection > 0) {
                    currentSelection--;
                }
                break;
            case 80: // Flecha abajo
                if (currentSelection < size - 1) {
                    currentSelection++;
                }
                break;
            case 13: // Enter
                if (currentSelection == 5) {
                    return; // Regresar al menu principal
                } else {
                    switch (currentSelection) {
                        case 0: mostrarUnion(A_str, B_str); dibujar.dibujarUnion(A_str, B_str); break;
                        case 1: mostrarInterseccion(A_str, B_str); dibujar.dibujarInterseccion(A_str, B_str); break;
                        case 2: mostrarDiferencia(A_str, B_str); dibujar.dibujarDiferencia(A_str, B_str); break;
                        case 3: mostrarDiferenciaSimetrica(A_str, B_str); dibujar.dibujarDiferenciaSimetrica(A_str, B_str); break;
                        case 4: mostrarComplemento(A_str, B_str); dibujar.dibujarComplemento(A_str, B_str); break;
                    }
                    cout << "Presione cualquier tecla para continuar..." << endl;
                    _getch();
                }
                break;
        }
    } while (true);
}

template <typename T>
void ingresarConjunto(ListaSimple<T>& conjunto) {
    const char* opciones[] = {"Si", "No"};
    int size = sizeof(opciones) / sizeof(opciones[0]);
    int currentSelection = 0;
    int key;

    do {
        // Ingreso de un elemento
        T elemento;
        cout << "Ingrese un elemento: ";
        cin >> elemento;
        cin.ignore();

        // Verificar si el elemento ya está en el conjunto
        if (conjunto.buscar(elemento) != nullptr) {
            cout << "El elemento " << elemento << " ya está en el conjunto. Intente de nuevo." << endl;
            _getch();
        } else {
            conjunto.insertar(elemento);
        }

        // Menú para continuar agregando elementos
        do {
            system("cls");
            cout << "¿Desea agregar otro elemento?" << endl;
            printMenuMain(opciones, size, currentSelection);

            key = _getch();

            switch (key) {
                case 72: // Flecha arriba
                    if (currentSelection > 0) {
                        currentSelection--;
                    }
                    break;
                case 80: // Flecha abajo
                    if (currentSelection < size - 1) {
                        currentSelection++;
                    }
                    break;
                case 13: // Enter
                    if (currentSelection == 1) { // "No"
                        return; // Salir del bucle
                    }
                    break;
            }
        } while (key != 13); // Esperar a que se presione Enter para continuar
    } while (true);
}

template <typename T>
void mostrarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> unionAB = A.unionList(B);
    cout << "Union: ";
    unionAB.mostrar();
}

template <typename T>
void mostrarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> interseccionAB = A.interseccion(B);
    cout << "Interseccion: ";
    interseccionAB.mostrar();
}

template <typename T>
void mostrarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaAB = A.diferencia(B, true);
    ListaSimple<T> diferenciaBA = B.diferencia(A, false);
    cout << "Diferencia A - B: ";
    diferenciaAB.mostrar();
    cout << "Diferencia B - A: ";
    diferenciaBA.mostrar();
}

template <typename T>
void mostrarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaSimetrica = A.diferenciaSimetrica(B);
    cout << "Diferencia Simetrica: ";
    diferenciaSimetrica.mostrar();
}

template <typename T>
void mostrarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> complementoAB = A.complemento(B, true);
    ListaSimple<T> complementoBA = B.complemento(A, true);
    cout << "Complemento A - B: ";
    complementoAB.mostrar();
    cout << "Complemento B - A: ";
    complementoBA.mostrar();
}