#ifndef IMAGENES_H
#define IMAGENES_H

#include <string>

// Obtiene la respuesta JSON de una URL
std::string obtenerRespuestaJson(const std::string& url);

// Extrae la URL de la imagen del JSON
std::string extraerUrlImagen(const std::string& json);

// Descarga la imagen desde una URL
void descargarImagen(const std::string& urlImagen, const std::string& nombreArchivoSalida);

// Convierte una imagen a formato BMP
void convertirABmp(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida);

// Muestra una imagen en una ventana gráfica
void mostrarImagenConGraficos(const std::string& nombreArchivoImagen, const std::string& titulo);

void dibujarImagenBMP(int x, int y, const char* archivo);
#endif // IMAGENES_H
