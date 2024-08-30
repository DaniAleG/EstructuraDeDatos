#ifndef HANOI_H
#define HANOI_H

#include <vector>
#include <string>

// Función para obtener el nombre del color basado en el índice del color
std::string obtenerNombreColor(int colorIndex);

// Función recursiva para resolver las Torres de Hanoi
void torresHanoi(int n, int numTorres, char deVarilla, char aVarilla, char auxVarilla, std::vector<std::pair<char, char>>& pasos);

// Función para guardar los pasos en un archivo
void guardarPasosEnArchivo(const std::vector<std::pair<char, char>>& pasos, const std::string& nombreArchivo);

// Función para dibujar un disco
void dibujarDisco(int x, int y, int ancho, int alto, int color);

// Función para dibujar el estado de las Torres de Hanoi
void dibujarEstadoHanoi(const std::vector<std::vector<int>>& varillas, int n, int numTorres, const std::string& mensajePaso, const std::string& mensajeDisco);

// Función para animar los pasos de las Torres de Hanoi
void animarPasosHanoi(const std::vector<std::pair<char, char>>& pasos, int n, int numTorres, std::vector<std::vector<int>>& varillas);

#endif // HANOI_H
