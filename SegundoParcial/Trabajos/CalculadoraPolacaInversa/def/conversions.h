#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <string>

// Funciones de validación y conversión

bool esCaracterValido(char c);
bool esOperador(char c);
bool esOperadorUnario(char c);
int obtenerPrioridad(char C);
bool esFuncion(const std::string& token);
int obtenerPrioridadFuncion(const std::string& token);
bool esExpresionValida(const std::string& expresion);
std::string insertarEspacios(const std::string& expresion);
bool balanceParentesis(const std::string& expresion);
bool esInfijo(const std::string& expresion);
std::string infijoASufijo(const std::string& infijo);
std::string infijoAPrefijo(const std::string& infijo);
double gradosARadianes(double grados);
double evaluarPrefijo(const std::string& prefijo);
double evaluarSufijo(const std::string& sufijo);
double evaluarInfijo(const std::string& infijo);
bool esNumero(const std::string& token);
bool siOperador(const std::string& token);
bool esNumeroDecimalValido(const std::string& token);
bool validarCaracteres(const std::string& expresion);
double evaluarOperacion(double op1, double op2, const std::string& op);
#endif // CONVERSIONS_H
