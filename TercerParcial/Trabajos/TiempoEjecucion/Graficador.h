#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <iostream>
#include <cmath>
#include <chrono>
#include <graphics.h>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <regex>
#include <windows.h>

using namespace std;

double medirTiempoEjecucion(function<void()> func, int repeticiones = 1000000);
int scaleX(int n, int max_n);
int scaleY(double value, double max_value);
void dibujarEjes(const string& complejidad, double tiempoEjecucion);
void graficarO1();
void graficarOlogN();
void graficarON();
void graficarONlogN();
void graficarOnSquared();
void graficarO2n();
void graficarONfactorial();
double ejecutarFuncionSimulada(const string& complejidad);
string identificarComplejidad(const string& codigo);
void procesarArchivo(const string& archivo);

#endif // GRAFICADOR_H