#include "Dibujar.h"
#include "ListaSimple.h"
#include <string>

template <typename T>
void Dibujar::dibujarUnion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> unionAB = A.unionList(B);
    initwindow(800, 600, "Union");
    setcolor(WHITE);
    outtextxy(350, 100, const_cast<char*>("A union B"));
    circle(400, 300, 150);
    mostrarDatos(unionAB, 400, 300);
    getch();
    closegraph();
}

template <typename T>
void Dibujar::dibujarInterseccion(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> interseccionAB = A.interseccion(B);
    ListaSimple<T> soloA = A.diferencia(B, true);
    ListaSimple<T> soloB = B.diferencia(A, true);
    initwindow(800, 600, "Interseccion");
    setcolor(WHITE);
    circle(350, 300, 100);
    circle(450, 300, 100);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(250, 200, const_cast<char*>("Conjunto A"));
    outtextxy(500, 200, const_cast<char*>("Conjunto B"));
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    floodfill(400, 300, WHITE);
    mostrarDatos(interseccionAB, 400, 300);
    mostrarDatos(soloA, 300, 300);
    mostrarDatos(soloB, 500, 300);
    getch();
    closegraph();
}

template <typename T>
void Dibujar::dibujarDiferencia(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaAB = A.diferencia(B, true);
    ListaSimple<T> diferenciaBA = A.diferencia(B, false);
    initwindow(800, 600, "Diferencia");
    setcolor(WHITE);
    outtextxy(200, 200, const_cast<char*>("Conjunto A-B"));
    circle(250, 300, 100);
    setfillstyle(SOLID_FILL, LIGHTRED);
    floodfill(250, 300, WHITE);
    mostrarDatos(diferenciaAB, 250, 300);
    outtextxy(500, 200, const_cast<char*>("Conjunto B-A"));
    circle(550, 300, 100);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    floodfill(550, 300, WHITE);
    mostrarDatos(diferenciaBA, 550, 300);
    getch();
    closegraph();
}

template <typename T>
void Dibujar::dibujarDiferenciaSimetrica(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> diferenciaSimetrica = A.diferenciaSimetrica(B);
    initwindow(800, 600, "Diferencia Simetrica");
    setcolor(WHITE);
    outtextxy(370, 200, const_cast<char*>("A Δ B"));
    circle(400, 300, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(400, 300, WHITE);
    mostrarDatos(diferenciaSimetrica, 400, 300);
    getch();
    closegraph();
}

template <typename T>
void Dibujar::dibujarComplemento(const ListaSimple<T>& A, const ListaSimple<T>& B) {
    ListaSimple<T> complementoA = A.complemento(B, true);
    ListaSimple<T> complementoB = B.complemento(A, true);
    initwindow(800, 600, "Complemento");
    setcolor(WHITE);
    outtextxy(200, 200, const_cast<char*>("Complemento de A"));
    circle(250, 300, 100);
    setfillstyle(SOLID_FILL, MAGENTA);
    floodfill(250, 300, WHITE);
    mostrarDatos(complementoA, 250, 300);
    outtextxy(500, 200, const_cast<char*>("Complemento de B"));
    circle(550, 300, 100);
    setfillstyle(SOLID_FILL, CYAN);
    floodfill(550, 300, WHITE);
    mostrarDatos(complementoB, 550, 300);
    getch();
    closegraph();
}

template <typename T>
void Dibujar::mostrarDatos(const ListaSimple<T>& conjunto, int x, int y) {
    setcolor(WHITE);
    int offset = 20;
    typename ListaSimple<T>::Nodo* actual = conjunto.cabeza;
    while (actual != nullptr) {
        outtextxy(x - 10, y + offset, const_cast<char*>(std::to_string(actual->dato).c_str()));
        offset += 20;
        actual = actual->siguiente;
    }
}

void Dibujar::mostrarDatos(const ListaSimple<std::string>& conjunto, int x, int y) {
    setcolor(WHITE);
    int offset = 20;
    Nodo<std::string>* actual = conjunto.cabeza;
    while (actual != nullptr) {
        outtextxy(x - 10, y + offset, const_cast<char*>(actual->dato.c_str()));
        offset += 20;
        actual = actual->siguiente;
    }
}