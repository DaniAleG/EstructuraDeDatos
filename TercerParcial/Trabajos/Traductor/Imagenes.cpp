#include "Imagenes.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#pragma comment(lib, "wininet.lib")

// Función para dibujar una imagen BMP centrada en la ventana gráfica
void dibujarImagenBMP(int x, int y, const char* archivo) {
    // Cargar la imagen y obtener sus dimensiones
    readimagefile(archivo, x, y, x + 750, y + 750);
}

// Función para obtener la respuesta JSON de una URL
std::string obtenerRespuestaJson(const std::string& url) {
    HINTERNET hInternet = InternetOpen(TEXT("Cliente de API"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen fallo: " << GetLastError() << std::endl;
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "InternetOpenUrlA fallo: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    std::string respuesta;
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        respuesta.append(buffer);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return respuesta;
}

// Función para extraer la URL de la imagen del JSON
std::string extraerUrlImagen(const std::string& json) {
    size_t startPos = json.find("\"regular\":\"");
    if (startPos == std::string::npos) return "";

    startPos += 11; // Longitud de "\"regular\":\""
    size_t endPos = json.find("\"", startPos);
    if (endPos == std::string::npos) return "";

    return json.substr(startPos, endPos - startPos);
}

// Función para descargar la imagen desde una URL
void descargarImagen(const std::string& urlImagen, const std::string& nombreArchivoSalida) {
    HINTERNET hInternet = InternetOpen(TEXT("Descargador de Imágenes"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen fallo: " << GetLastError() << std::endl;
        return;
    }

    HINTERNET hImagen = InternetOpenUrlA(hInternet, urlImagen.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hImagen == NULL) {
        std::cerr << "InternetOpenUrlA (imagen) fallo: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return;
    }

    std::ofstream archivoSalida(nombreArchivoSalida, std::ios::binary);
    if (!archivoSalida) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        InternetCloseHandle(hImagen);
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hImagen, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        archivoSalida.write(buffer, bytesRead);
    }

    archivoSalida.close();
    InternetCloseHandle(hImagen);
    InternetCloseHandle(hInternet);
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Función para convertir una imagen a BMP
void convertirABmp(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida) {
    int ancho, alto, canales;
    unsigned char* datosImg = stbi_load(nombreArchivoEntrada.c_str(), &ancho, &alto, &canales, 0);
    if (datosImg == nullptr) {
        std::cerr << "Error al cargar la imagen: " << stbi_failure_reason() << std::endl;
        return;
    }

    // Convertir a BMP
    stbi_write_bmp(nombreArchivoSalida.c_str(), ancho, alto, canales, datosImg);

    stbi_image_free(datosImg);
}

// Función principal para mostrar la ventana gráfica
void mostrarImagenConGraficos(const std::string& nombreArchivoImagen, const std::string& palabraIngles, const std::string& palabraEspanol) {
    // Inicializar la ventana gráfica
    int anchoVentana = getmaxwidth();
    int altoVentana = getmaxheight();
    initwindow(anchoVentana, altoVentana, "Imagenes");
    setbkcolor(WHITE);

    // Mostrar el título en inglés y español
    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, const_cast<char*>(("En Ingles: " + palabraIngles).c_str()));
    outtextxy(10, 30, const_cast<char*>(("En Espanol: " + palabraEspanol).c_str()));

    // Dimensiones de la imagen
    int anchoImg = 750; // Ancho de la imagen (debe coincidir con el tamaño en dibujarImagenBMP)
    int altoImg = 750; // Alto de la imagen (debe coincidir con el tamaño en dibujarImagenBMP)

    // Calcular las coordenadas para centrar la imagen
    int x = (anchoVentana - anchoImg) / 2;
    int y = (altoVentana - altoImg) / 2;

    // Ajustar la posición si es necesario
    // Aquí puedes modificar las coordenadas si la imagen no está centrada correctamente
    x = (anchoVentana - anchoImg) / 2;
    y = (altoVentana - altoImg) / 2;

    // Dibujar un borde negro alrededor de la ventana
    setcolor(BLACK);
    rectangle(0, 0, anchoVentana - 1, altoVentana - 1);

    // Mostrar la imagen centrada
    dibujarImagenBMP(x, y, nombreArchivoImagen.c_str());

    // Mantener la ventana abierta
    getch();
    closegraph();
}
