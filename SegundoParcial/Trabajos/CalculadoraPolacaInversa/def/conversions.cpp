#include "conversions.h"
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cmath>
#include <deque>
#include <stdexcept>
#include <unordered_set>
#include <regex>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

bool esCaracterValido(char c) {
    return (isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || 
            c == '(' || c == ')' || c == '%' || isspace(c) || isalpha(c) || c == '.');
}

bool esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

bool esOperadorUnario(char c) {
    return (c == '-');
}

int obtenerPrioridad(char C) {
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/' || C == '%')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}


bool esFuncion(const std::string& token) {
    static const std::unordered_set<std::string> funciones = {"sqrt", "sin", "cos", "tan"};
    return funciones.find(token) != funciones.end();
}

int obtenerPrioridadFuncion(const std::string& token) {
    if (esFuncion(token))
        return 4;
    return 0;
}

bool esExpresionValida(const std::string& expresion) {
    int n = expresion.size();
    
    if (n == 0) return false;
    if (esOperador(expresion[0]) && !esOperadorUnario(expresion[0])) return false;
    if (esOperador(expresion[n - 1])) return false;

    bool operadorAnterior = false;
    for (int i = 0; i < n; ++i) {
        char c = expresion[i];
        if (!esCaracterValido(c)) {
            return false;
        }
        if (esOperador(c)) {
            if (operadorAnterior && !esOperadorUnario(c)) {
                return false;
            }
            operadorAnterior = true;
        } else {
            operadorAnterior = false;
        }
    }
    return true;
}

std::string insertarEspacios(const std::string& expresion) {
    std::string resultado;
    bool inicio = true;
    for (char c : expresion) {
        if (esOperador(c) || c == '(' || c == ')') {
            if (c == '-' && (inicio || resultado.back() == '(' || esOperador(resultado.back()))) {
                resultado += c; 
            } else {
                resultado += ' ';
                resultado += c;
                resultado += ' ';
            }
        } else {
            resultado += c;
        }
        inicio = false;
    }
    return resultado;
}

bool balanceParentesis(const std::string& expresion) {
    std::stack<char> stk;
    for (char c : expresion) {
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            if (stk.empty() || stk.top() != '(') {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

bool esInfijo(const std::string& expresion) {
    int balance = 0;
    bool anteriorFueOperador = true;
    std::istringstream iss(expresion);
    std::string token;

    while (iss >> token) {
        if (esOperador(token[0])) {
            if (anteriorFueOperador && !esOperadorUnario(token[0])) {
                return false;
            }
            anteriorFueOperador = true;
        } else if (token == "(") {
            balance++;
            anteriorFueOperador = true;
        } else if (token == ")") {
            balance--;
            if (balance < 0) {
                return false;
            }
            anteriorFueOperador = false;
        } else {
            anteriorFueOperador = false;
        }
    }
    return balance == 0 && !anteriorFueOperador;
}

std::string infijoASufijo(const std::string& infijo) {
    std::stack<std::string> stk;
    std::deque<std::string> sufijo;
    std::istringstream iss(infijo);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || isalpha(token[0])) {
            sufijo.push_back(token);
        } else if (esFuncion(token)) {
            stk.push(token);
        } else if (token == "(") {
            stk.push(token);
        } else if (token == ")") {
            while (!stk.empty() && stk.top() != "(") {
                sufijo.push_back(stk.top());
                stk.pop();
            }
            stk.pop(); // Remove '('
            if (!stk.empty() && esFuncion(stk.top())) {
                sufijo.push_back(stk.top());
                stk.pop();
            }
        } else if (esOperador(token[0])) {
            while (!stk.empty() && stk.top() != "(" && obtenerPrioridad(token[0]) <= obtenerPrioridad(stk.top()[0])) {
                sufijo.push_back(stk.top());
                stk.pop();
            }
            stk.push(token);
        }
    }

    while (!stk.empty()) {
        sufijo.push_back(stk.top());
        stk.pop();
    }

    std::string resultado;
    for (const std::string& s : sufijo) {
        resultado += s + ' ';
    }

    if (!resultado.empty() && resultado.back() == ' ') {
        resultado.pop_back(); // Eliminar el último espacio
    }

    return resultado;
}

std::string infijoAPrefijo(const std::string& infijo) {
    std::stack<std::string> stk;
    std::deque<std::string> prefijo;
    std::istringstream iss(infijo);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || isalpha(token[0])) {
            prefijo.push_front(token);
        } else if (esFuncion(token)) {
            stk.push(token);
        } else if (token == "(") {
            stk.push(token);
        } else if (token == ")") {
            while (!stk.empty() && stk.top() != "(") {
                prefijo.push_front(stk.top());
                stk.pop();
            }
            stk.pop(); // Remove '('
            if (!stk.empty() && esFuncion(stk.top())) {
                prefijo.push_front(stk.top());
                stk.pop();
            }
        } else if (esOperador(token[0])) {
            while (!stk.empty() && stk.top() != "(" && obtenerPrioridad(token[0]) < obtenerPrioridad(stk.top()[0])) {
                prefijo.push_front(stk.top());
                stk.pop();
            }
            stk.push(token);
        }
    }

    while (!stk.empty()) {
        prefijo.push_front(stk.top());
        stk.pop();
    }

    std::string resultado;
    for (const std::string& s : prefijo) {
        resultado += s + ' ';
    }

    if (!resultado.empty() && resultado.back() == ' ') {
        resultado.pop_back(); // Eliminar el último espacio
    }

    return resultado;
}

double gradosARadianes(double grados) {
    return grados * M_PI / 180.0;
}

double evaluarPrefijo(const std::string& prefijo) {
    std::stack<double> stk;
    std::istringstream iss(prefijo);
    std::string token;
    std::deque<std::string> tokens;

    // Tokenizar la expresión y almacenarla en una deque
    while (iss >> token) {
        tokens.push_front(token);
    }

    for (const std::string& token : tokens) {
        if (std::isdigit(token[0])) {
            stk.push(std::stod(token));
        } else if (token == "cos" || token == "sin" || token == "tan" || token == "sqrt") {
            if (stk.size() < 1) throw std::runtime_error("Error: No hay suficientes operandos.");
            double arg = stk.top();
            stk.pop();
            if (!esNumero(std::to_string(arg))) throw std::runtime_error("Error: Operando no valido.");
            if (token == "cos") stk.push(std::cos(gradosARadianes(arg)));
            else if (token == "sin") stk.push(std::sin(gradosARadianes(arg)));
            else if (token == "tan") stk.push(std::tan(gradosARadianes(arg)));
            else if (token == "sqrt") stk.push(std::sqrt(arg));
        } else {
            if (stk.size() < 2) throw std::runtime_error("Error: No hay suficientes operandos.");
            double op1 = stk.top();
            stk.pop();
            double op2 = stk.top();
            stk.pop();

            if (token == "+") stk.push(op1 + op2);
            else if (token == "-") stk.push(op1 - op2);
            else if (token == "*") stk.push(op1 * op2);
            else if (token == "/") {
                if (op2 == 0) throw std::runtime_error("Error: Division por cero.");
                stk.push(op1 / op2);
            }
            else if (token == "%") {
                if (op2 == 0) throw std::runtime_error("Error: Division por cero.");
                stk.push(std::fmod(op1, op2));
            }
            else throw std::runtime_error("Error: Operador desconocido.");
        }
    }

    if (stk.size() != 1) throw std::runtime_error("Error: La pila final no tiene un unico valor.");
    return stk.top();
}

double evaluarSufijo(const std::string& sufijo) {
    std::stack<double> stk;
    std::istringstream iss(sufijo);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stk.push(std::stod(token));
        } else if (token == "cos" || token == "sin" || token == "tan" || token == "sqrt") {
            if (stk.size() < 1) throw std::runtime_error("Error: No hay suficientes operandos.");
            double arg = stk.top();
            stk.pop();
            if (!esNumero(std::to_string(arg))) throw std::runtime_error("Error: Operando no valido.");
            if (token == "cos") stk.push(std::cos(gradosARadianes(arg)));
            else if (token == "sin") stk.push(std::sin(gradosARadianes(arg)));
            else if (token == "tan") stk.push(std::tan(gradosARadianes(arg)));
            else if (token == "sqrt") stk.push(std::sqrt(arg));
        } else {
            if (stk.size() < 2) throw std::runtime_error("Error: No hay suficientes operandos.");
            double op1 = stk.top();
            stk.pop();
            double op2 = stk.top();
            stk.pop();

            if (token == "+") stk.push(op2 + op1);
            else if (token == "-") stk.push(op2 - op1);
            else if (token == "*") stk.push(op2 * op1);
            else if (token == "/") {
                if (op1 == 0) throw std::runtime_error("Error: Division por cero.");
                stk.push(op2 / op1);
            }
            else if (token == "%") {
                if (op1 == 0) throw std::runtime_error("Error: Division por cero.");
                stk.push(std::fmod(op2, op1));
            }
            else throw std::runtime_error("Error: Operador desconocido.");
        }
    }

    if (stk.size()!= 1) throw std::runtime_error("Error: La pila final no tiene un unico valor.");
    return stk.top();
}

double evaluarOperacion(double op1, double op2, const std::string& op) {
    if (op == "+") return op1 + op2;
    if (op == "-") return op1 - op2;
    if (op == "*") return op1 * op2;
    if (op == "/") {
        if (op2 == 0) throw std::runtime_error("Error: Division por cero.");
        return op1 / op2;
    }
    if (op == "%") {
        if (op2 == 0) throw std::runtime_error("Error: Division por cero.");
        return std::fmod(op1, op2);
    }
    throw std::runtime_error("Error: Operador desconocido.");
}
double evaluarInfijo(const std::string& infija) {
    std::stack<double> valores;
    std::stack<std::string> operadores;
    std::istringstream iss(infija);
    std::string token;

    auto precedencia = [](const std::string& op) -> int {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;
        if (op == "cos" || op == "sin" || op == "tan" || op == "sqrt") return 3;
        return 0;
    };

    auto aplicarOperador = [&]() {
        if (operadores.empty()) throw std::runtime_error("Error: No hay operador.");
        std::string op = operadores.top();
        operadores.pop();

        if (op == "cos" || op == "sin" || op == "tan" || op == "sqrt") {
            if (valores.size() < 1) throw std::runtime_error("Error: No hay suficientes operandos.");
            double arg = valores.top();
            valores.pop();
            if (op == "cos") valores.push(std::cos(gradosARadianes(arg)));
            else if (op == "sin") valores.push(std::sin(gradosARadianes(arg)));
            else if (op == "tan") valores.push(std::tan(gradosARadianes(arg)));
            else if (op == "sqrt") valores.push(std::sqrt(arg));
        } else {
            if (valores.size() < 2) throw std::runtime_error("Error: No hay suficientes operandos.");
            double op2 = valores.top();
            valores.pop();
            double op1 = valores.top();
            valores.pop();
            valores.push(evaluarOperacion(op1, op2, op));
        }
    };

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            valores.push(std::stod(token));
        } else if (token == "(") {
            operadores.push(token);
        } else if (token == ")") {
            while (!operadores.empty() && operadores.top() != "(") {
                aplicarOperador();
            }
            if (operadores.empty()) throw std::runtime_error("Error: Paréntesis desbalanceados.");
            operadores.pop();
        } else {
            while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(token)) {
                aplicarOperador();
            }
            operadores.push(token);
        }
    }

    while (!operadores.empty()) {
        aplicarOperador();
    }

    if (valores.size() != 1) throw std::runtime_error("Error: La pila final no tiene un único valor.");
    return valores.top();
}

bool esNumero(const std::string& token) {
    if (token.empty()) return false;
    std::istringstream iss(token);
    double d;
    char c;
    return (iss >> d) && !(iss >> c);
}

bool siOperador(const std::string& token) {
    static const std::unordered_set<std::string> operadores = {"+", "-", "*", "/", "^", "%"};
    return operadores.find(token) != operadores.end();
}

bool esNumeroDecimalValido(const std::string& token) {
    if (token.empty()) return false;
    bool puntoEncontrado = false;
    for (char c : token) {
        if (c == '.') {
            if (puntoEncontrado) return false; // Solo se permite un punto decimal
            puntoEncontrado = true;
        } else if (!isdigit(c)) {
            return false; // Solo se permiten dígitos
        }
    }
    return true;
}

bool validarCaracteres(const std::string& expresion) {
    std::istringstream iss(expresion);
    std::string token;
    
    while (iss >> token) {
        if (!(esNumero(token) || esFuncion(token) || siOperador(token) || token == "(" || token == ")")) {
            return false; 
        }
    }
    
    return true; 
}