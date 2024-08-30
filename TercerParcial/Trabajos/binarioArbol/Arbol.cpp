#include "Arbol.h"
#include <graphics.h>
#include <conio.h>
#include <stack>
#include <sstream>
#include <cmath>
#include <stdexcept>

Arbol::Arbol() {}

Arbol::~Arbol() {
    // Destructor vacío, la destrucción se maneja en destruirArbol
}

void Arbol::destruirArbol(Nodo* nodo) {
    if (nodo) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

Nodo* Arbol::construirArbol(const std::string* tokens, int numeroTokens) {
    std::stack<Nodo*> pila;
    for (int i = 0; i < numeroTokens; ++i) {
        const std::string& token = tokens[i];
        Nodo* nodo = new Nodo(token);
        if (token == "+" || token == "-" || token == "*" || token == "/" || 
            token == "sin" || token == "cos" || token == "sqrt" || token == "^" || token == "tan") {
            if (token == "sin" || token == "cos" || token == "sqrt" || token == "tan") {
                nodo->derecho = pila.top(); pila.pop(); // Operaciones unarias
            } else {
                nodo->derecho = pila.top(); pila.pop();
                nodo->izquierdo = pila.top(); pila.pop();
            }
        }
        pila.push(nodo);
    }
    return pila.top();
}

double Arbol::evaluarArbol(Nodo* raiz) {
    if (raiz == nullptr) throw std::invalid_argument("El árbol está vacío");

    // Evaluar el nodo hoja
    if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
        return std::stod(raiz->valor);
    }

    // Evaluar subárboles
    double valorIzquierdo = 0;
    double valorDerecho = evaluarArbol(raiz->derecho);

    if (raiz->izquierdo != nullptr) {
        valorIzquierdo = evaluarArbol(raiz->izquierdo);
    }

    // Aplicar la operación del nodo
    if (raiz->valor == "+") return valorIzquierdo + valorDerecho;
    if (raiz->valor == "-") return valorIzquierdo - valorDerecho;
    if (raiz->valor == "*") return valorIzquierdo * valorDerecho;
    if (raiz->valor == "/") {
        if (valorDerecho == 0) throw std::domain_error("División por cero");
        return valorIzquierdo / valorDerecho;
    }
    if (raiz->valor == "sin") return std::sin(valorDerecho);
    if (raiz->valor == "cos") return std::cos(valorDerecho);
    if (raiz->valor == "sqrt") {
        if (valorDerecho < 0) throw std::domain_error("Raíz cuadrada de número negativo");
        return std::sqrt(valorDerecho);
    }
    if (raiz->valor == "^") return std::pow(valorIzquierdo, valorDerecho);
    if (raiz->valor == "tan") return std::tan(valorDerecho);

    throw std::invalid_argument("Operador inválido");
}

int Arbol::calcularAltura(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    int alturaIzquierda = calcularAltura(raiz->izquierdo);
    int alturaDerecha = calcularAltura(raiz->derecho);
    return std::max(alturaIzquierda, alturaDerecha) + 1;
}

void Arbol::dibujarArbol(Nodo* raiz, int x, int y, int nivel, int desplazamiento) {
    if (raiz == nullptr) return;

    int espaciado = 300 / (nivel + 1); // Aumentar el espaciado horizontal
    int radio = 20;
    int maxX = getmaxx();
    
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    setlinestyle(SOLID_LINE, 0, 3);

    circle(x, y, radio);
    setcolor(WHITE);
    outtextxy(x - 10, y - 10, const_cast<char*>(raiz->valor.c_str()));

    setcolor(BLACK);
    if (raiz->izquierdo) {
        int izquierdaX = x - espaciado;
        int izquierdaY = y + 50;
        if (izquierdaX - radio < 0) izquierdaX = radio + 10;
        line(x, y, izquierdaX, izquierdaY);
        dibujarArbol(raiz->izquierdo, izquierdaX, izquierdaY, nivel + 1, espaciado);
    }
    if (raiz->derecho) {
        int derechaX = x + espaciado;
        int derechaY = y + 50;
        if (derechaX + radio > maxX) derechaX = maxX - radio - 10;
        line(x, y, derechaX, derechaY);
        dibujarArbol(raiz->derecho, derechaX, derechaY, nivel + 1, espaciado);
    }
}


void Arbol::configurarGraficos() {
    int ancho = getmaxwidth();
    int alto = getmaxheight();
    initwindow(ancho, alto, "Visualización del Árbol Binario");

    setbkcolor(CYAN);
    cleardevice();
}

void Arbol::dibujarArbolRPN(const std::string& expresion) {
    configurarGraficos();

    int anchoPantalla = getmaxwidth();
    int altoPantalla = getmaxheight();
    
    int numeroTokens = 0;
    std::string tokens[100]; // Ajusta el tamaño según sea necesario
    std::istringstream iss(expresion);
    std::string token;
    while (iss >> token) {
        tokens[numeroTokens++] = token;
    }

    Nodo* raiz = construirArbol(tokens, numeroTokens);

    cleardevice();
    
    int alturaArbol = calcularAltura(raiz);
    int maxDesplazamiento = std::min(anchoPantalla / 2, altoPantalla / (alturaArbol + 1));

    dibujarArbol(raiz, anchoPantalla / 2, 50, 0, maxDesplazamiento);

    try {
        double resultado = evaluarArbol(raiz);
        std::ostringstream flujoResultado;
        flujoResultado << "Resultado: " << resultado;
        outtextxy(10, 10, const_cast<char*>(flujoResultado.str().c_str()));
    } catch (const std::exception& e) {
        outtextxy(10, 10, const_cast<char*>(e.what()));
    }

    getch();
    closegraph();
    destruirArbol(raiz);
}
