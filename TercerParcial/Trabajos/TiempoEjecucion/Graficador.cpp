#include "Graficador.h"

double medirTiempoEjecucion(function<void()> func, int repeticiones) {
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < repeticiones; ++i) {
        func();
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duracion = end - start;
    
    return duracion.count() / repeticiones;
}

int scaleX(int n, int max_n) {
    return 80 + n * (getmaxx() - 160) / max_n;
}

int scaleY(double value, double max_value) {
    return getmaxy() - 80 - (value * (getmaxy() - 160) / max_value);
}

void dibujarEjes(const string& complejidad, double tiempoEjecucion) {
    setcolor(WHITE);
    line(80, getmaxy() - 80, getmaxx() - 80, getmaxy() - 80);
    line(80, getmaxy() - 80, 80, 80);

    setcolor(CYAN);

    outtextxy(getmaxx() - 60, getmaxy() - 65, "n");
    outtextxy(30, 30, "Tiempo");

    setcolor(WHITE);

    for (int i = 0; i <= 100; i += 15) {
        int x = scaleX(i, 100);
        line(x, getmaxy() - 80, x, getmaxy() - 75);
        char label[10];
        sprintf(label, "%d", i);
        outtextxy(x - 10, getmaxy() - 65, label);
    }

    for (int i = 0; i <= 500; i += 15) {
        int y = scaleY(i, 500);
        line(75, y, 80, y);
        char label[10];
        sprintf(label, "%d", i);
        outtextxy(10, y - 5, label);
    }

    setcolor(YELLOW);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    int anchoVentana = getmaxx();
    int alturaVentana = getmaxy();

    char bigO[50];
    sprintf(bigO, "Complejidad: %s", complejidad.c_str());
    int anchoTextoBigO = textwidth(bigO);
    int alturaTextoBigO = textheight(bigO);
    outtextxy((anchoVentana - anchoTextoBigO) / 2, 50, bigO);

    char tiempo[50];
    sprintf(tiempo, "Tiempo de ejecucion: %.6f segundos", tiempoEjecucion);
    int anchoTextoTiempo = textwidth(tiempo);
    int alturaTextoTiempo = textheight(tiempo);
    outtextxy((anchoVentana - anchoTextoTiempo) / 2, 50 + alturaTextoBigO + 10, tiempo);
}

void graficarO1() {
    setcolor(LIGHTGREEN);
    int prevX = scaleX(0, 100);
    int prevY = scaleY(1, 1);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n, 100);
        int currY = scaleY(1, 1);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarOlogN() {
    setcolor(LIGHTBLUE);
    int prevX = scaleX(1, 100);
    int prevY = scaleY(log2(1), log2(100));
    for (int n = 2; n <= 100; ++n) {
        int currX = scaleX(n, 100);
        int currY = scaleY(log2(n), log2(100));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarON() {
    setcolor(LIGHTCYAN);
    int prevX = scaleX(0, 100);
    int prevY = scaleY(0, 100);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n, 100);
        int currY = scaleY(n, 100);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarONlogN() {
    setcolor(LIGHTMAGENTA);
    int prevX = scaleX(1, 100);
    int prevY = scaleY(1 * log2(1), 100 * log2(100));
    for (int n = 2; n <= 100; ++n) {
        int currX = scaleX(n, 100);
        int currY = scaleY(n * log2(n), 100 * log2(100));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarOnSquared() {
    setcolor(LIGHTRED);
    int prevX = scaleX(0, 100);
    int prevY = scaleY(0, 10000);
    for (int n = 1; n <= 100; ++n) {
        int currX = scaleX(n, 100);
        int currY = scaleY(n * n, 10000);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarO2n() {
    setcolor(YELLOW);
    int prevX = scaleX(0, 15);
    int prevY = scaleY(0, pow(2, 15));
    for (int n = 1; n <= 15; ++n) {
        int currX = scaleX(n, 15);
        int currY = scaleY(pow(2, n), pow(2, 15));
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

void graficarONfactorial() {
    setcolor(LIGHTGRAY);
    int prevX = scaleX(0, 10);
    int prevY = scaleY(1, 3628800);
    
    function<int(int)> factorial = [&](int num) -> int {
        if (num == 0 || num == 1) return 1;
        return num * factorial(num - 1);
    };
    
    for (int n = 1; n <= 10; ++n) {
        int currX = scaleX(n, 10);
        int currY = scaleY(factorial(n), 3628800);
        line(prevX, prevY, currX, currY);
        prevX = currX;
        prevY = currY;
    }
}

double ejecutarFuncionSimulada(const string& complejidad) {
    auto func = [=]() {
        if (complejidad == "O(1)") {
            int x = 10;
        } else if (complejidad == "O(log n)") {
            int n = 1000;
            while (n > 1) {
                n /= 2;
            }
        } else if (complejidad == "O(n)") {
            for (int i = 0; i < 1000; ++i) {
                
            }
        } else if (complejidad == "O(n log n)") {
            for (int i = 0; i < 1000; ++i) {
                int n = 1000;
                while (n > 1) {
                    n /= 2;
                }
            }
        } else if (complejidad == "O(n^2)") {
            for (int i = 0; i < 1000; ++i) {
                for (int j = 0; j < 1000; ++j) {
                    
                }
            }
        } else if (complejidad == "O(2^n)") {
            function<void(int)> exp = [&](int n) {
                if (n == 0) return;
                exp(n - 1);
                exp(n - 1);
            };
            exp(10);
        } else if (complejidad == "O(n!)") {
            function<int(int)> fact = [&](int n) -> int {
                if (n == 0) return 1;
                return n * fact(n - 1);
            };
            fact(10);
        }
    };

    return medirTiempoEjecucion(func);
}

string identificarComplejidad(const string& codigo) {
    string codigoNormalizado = codigo;
    replace(codigoNormalizado.begin(), codigoNormalizado.end(), '\n', ' ');
    replace(codigoNormalizado.begin(), codigoNormalizado.end(), '\r', ' ');

    regex forLoopRegex("for\\s*\\(\\s*int\\s+.*?\\s*;\\s*.*?\\s*;\\s*.*?\\)");
    regex whileLoopRegex("while\\s*\\(.*?\\s*\\)");
    regex nestedForLoopRegex("for\\s*\\(\\s*int\\s+.*?\\s*;\\s*.*?\\s*;\\s*.*?\\)\\s*\\{[^{}]*\\s*for\\s*\\(\\s*int\\s+.*?\\s*;\\s*.*?\\s*;\\s*.*?\\)");
    regex whileLogNRegex("while\\s*\\(.*?\\s*>\\s*1\\)");
    regex pow2nRegex("pow\\s*\\(\\s*2\\s*,\\s*n\\s*\\)");
    regex factorialRegex("factorial");
    regex recursionExpRegex("return\\s*\\(.*?\\s*\\+\\s*.*?\\)|\\b\\w+\\s*\\(.*?\\)\\s*\\+\\s*\\w+\\s*\\(.*?\\)");
    regex recursionFactorialRegex("return\\s*\\(.*?\\)\\s*\\+\\s*\\(.*?\\)");
    regex lambdaRegex("\\[.*?\\]\\s*\\(.*?\\)\\s*\\{");
    regex constantTimeRegex("\\b\\d+\\s*([+*/-]\\s*\\d+)*\\b");

    if (regex_search(codigoNormalizado, nestedForLoopRegex)) {
        return "O(n^2)";
    }
    if (regex_search(codigoNormalizado, pow2nRegex) || regex_search(codigoNormalizado, recursionExpRegex)) {
        return "O(2^n)";
    }
    if (regex_search(codigoNormalizado, factorialRegex)) {
        return "O(n!)";
    }
    if (regex_search(codigoNormalizado, forLoopRegex) && regex_search(codigoNormalizado, whileLogNRegex)) {
        return "O(n log n)";
    }
    if (regex_search(codigoNormalizado, forLoopRegex)) {
        return "O(n)";
    }
    if (regex_search(codigoNormalizado, whileLogNRegex)) {
        return "O(log n)";
    }
    if (regex_search(codigoNormalizado, constantTimeRegex)) {
        return "O(1)";
    }
    if (regex_search(codigoNormalizado, recursionFactorialRegex)) {
        return "O(n!)";
    }
    if (regex_search(codigoNormalizado, lambdaRegex)) {
        if (regex_search(codigoNormalizado, forLoopRegex) && regex_search(codigoNormalizado, whileLogNRegex)) {
            return "O(n log n) en lambda";
        } else if (regex_search(codigoNormalizado, forLoopRegex)) {
            return "O(n) en lambda";
        } else if (regex_search(codigoNormalizado, whileLogNRegex)) {
            return "O(log n) en lambda";
        }
    }

    return "Desconocida";
}

void procesarArchivo(const string& archivo) {
    ifstream file(archivo);
    if (!file) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    stringstream contenido;
    contenido << file.rdbuf();

    string codigo = contenido.str();
    file.close();

    string complejidad = identificarComplejidad(codigo);

    cout << "Complejidad identificada: " << complejidad << endl;

    unordered_map<string, function<void()>> graficarFunciones = {
        {"O(1)", graficarO1},
        {"O(log n)", graficarOlogN},
        {"O(n)", graficarON},
        {"O(n log n)", graficarONlogN},
        {"O(n^2)", graficarOnSquared},
        {"O(2^n)", graficarO2n},
        {"O(n!)", graficarONfactorial}
    };

    if (graficarFunciones.find(complejidad) != graficarFunciones.end()) {
        RECT escritorio;
        GetWindowRect(GetDesktopWindow(), &escritorio);
        int pantallaAncho = escritorio.right - escritorio.left;
        int pantallaAlto = escritorio.bottom - escritorio.top;

        initwindow(pantallaAncho, pantallaAlto, "Grafica de Complejidad");

        double tiempoEjecucion = ejecutarFuncionSimulada(complejidad);

        dibujarEjes(complejidad, tiempoEjecucion);
        graficarFunciones[complejidad]();

        getch();
        closegraph();
    } else {
        cout << "No se encontro una funcion reconocida en el archivo." << endl;
    }
}