/*Universidad de las Fuerzas Armadas ESPE
            TRADUCTOR
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include <graphics.h>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <conio.h>
#include "Imagenes.cpp"

using namespace std;

#pragma comment(lib, "wininet.lib")

// Función para traducir una palabra
std::string traducirPalabra(const std::string& palabra, const std::string& langpair) {
    std::string apiUrl = "api.mymemory.translated.net";
    std::string consulta = "/get?q=" + palabra + "&langpair=" + langpair;

    HINTERNET hInternet = InternetOpenW(L"Cliente de Traduccion", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "InternetOpen fallo: " << GetLastError() << std::endl;
        return "";
    }

    HINTERNET hConnect = InternetConnectA(hInternet, apiUrl.c_str(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (hConnect == NULL) {
        std::cerr << "InternetConnect fallo: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    HINTERNET hRequest = HttpOpenRequestA(hConnect, "GET", consulta.c_str(), NULL, NULL, NULL, 0, 0);
    if (hRequest == NULL) {
        std::cerr << "HttpOpenRequest fallo: " << GetLastError() << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "";
    }

    BOOL enviado = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!enviado) {
        std::cerr << "HttpSendRequest fallo: " << GetLastError() << std::endl;
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "";
    }

    std::string respuesta;
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        respuesta.append(buffer);
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    std::string claveTextoTraducido = "\"translatedText\":\"";
    size_t startPos = respuesta.find(claveTextoTraducido);
    if (startPos == std::string::npos) {
        std::cerr << "No se encontro la clave 'translatedText' en la respuesta." << std::endl;
        return "";
    }

    startPos += claveTextoTraducido.length();
    size_t endPos = respuesta.find("\"", startPos);
    if (endPos == std::string::npos) {
        std::cerr << "No se encontro el final de la cadena de traduccino." << std::endl;
        return "";
    }

    return respuesta.substr(startPos, endPos - startPos);
}

// Función para dibujar un botón
void dibujarBoton(int x1, int y1, int x2, int y2, const char* texto) {
    setcolor(WHITE);
    rectangle(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill((x1 + x2) / 2, (y1 + y2) / 2, WHITE);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    outtextxy((x1 + x2) / 2 - textwidth(const_cast<char*>(texto)) / 2, (y1 + y2) / 2 - textheight(const_cast<char*>(texto)) / 2, const_cast<char*>(texto));
}

// Función para verificar si el clic está dentro de un botón
bool clicEnBoton(int x1, int y1, int x2, int y2) {
    int x = mousex();
    int y = mousey();
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

// Función para mostrar el menú y detectar la opción seleccionada por clic
int mostrarMenu() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char*>("C:\\Turboc3\\BGI"));

    if (graphresult() != grOk) {
        std::cerr << "Error al inicializar el modo grafico." << std::endl;
        return -1;
    }

    setbkcolor(BLACK);

    // Definir los botones
    const int anchoBoton = 200;
    const int altoBoton = 50;
    const int espacio = 20;

    int x1 = (getmaxx() - anchoBoton) / 2;
    int y1 = (getmaxy() - 3 * (altoBoton + espacio)) / 2;
    int x2 = x1 + anchoBoton;
    int y2 = y1 + altoBoton;

    // Dibujar los botones
    dibujarBoton(x1, y1, x2, y2, "Espanol a Ingles");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Ingles a Espanol");
    y1 += altoBoton + espacio;
    y2 += altoBoton + espacio;
    dibujarBoton(x1, y1, x2, y2, "Salir");

    // Mostrar el menú
    int seleccion = -1;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN) == 1) { // Si se hace clic con el botón izquierdo del ratón
            if (clicEnBoton(x1, y1 - 2 * (altoBoton + espacio), x2, y1 - 2 * (altoBoton + espacio) + altoBoton)) {
                seleccion = 0; // Opción "Español a Inglés"
                break;
            } else if (clicEnBoton(x1, y1 - (altoBoton + espacio), x2, y1 - (altoBoton + espacio) + altoBoton)) {
                seleccion = 1; // Opción "Inglés a Español"
                break;
            } else if (clicEnBoton(x1, y1, x2, y1 + altoBoton)) {
                seleccion = 2; // Opción "Salir"
                break;
            }
        }
    }

    closegraph();
    return seleccion;
}

int main() {
    std::string palabra;
    int eleccion;
    std::string langpair;
    std::string apiKey = "AtWaXDORGIBIwlBOLgF1o88d_5Cq9hrNsKA9atcAJTI";
    std::string palabraClaveParaUnsplash;

    while (true) {
        eleccion = mostrarMenu();

        if (eleccion == 2) {
            break;  // Salir del bucle
        }

        if (eleccion == 0) {
            langpair = "es|en";
            std::cout << "Ingrese una palabra en espanol: ";
            std::cin >> palabra;
            // Traducir la palabra al inglés para buscar en Unsplash
            palabraClaveParaUnsplash = traducirPalabra(palabra, langpair);
            if (palabraClaveParaUnsplash.empty()) {
                std::cerr << "Error en la traducción al ingles." << std::endl;
                continue;
            }
        } else if (eleccion == 1) {
            langpair = "en|es";
            std::cout << "Ingrese una palabra en ingles: ";
            std::cin >> palabra;
            palabraClaveParaUnsplash = palabra;
        }

        

        // Traducir la palabra ingresada
        std::string palabraTraducida = traducirPalabra(palabra, langpair);
        if (!palabraTraducida.empty()) {
            std::cout << "Palabra ingresada: " << palabra << "\nTraduccion: " << palabraTraducida << std::endl;

            // Comando para reproducir la traducción
            std::string comando;
            if (eleccion == 0) {
                comando = "espeak -v en-us \"" + palabraTraducida + "\"";
            } else {
                comando = "espeak -v es \"" + palabraTraducida + "\"";
            }
            system(comando.c_str());

            // Buscar y mostrar la imagen
            std::string searchUrl = "https://api.unsplash.com/photos/random?query=" + palabraClaveParaUnsplash + "&client_id=" + apiKey;
            std::string jsonResponse = obtenerRespuestaJson(searchUrl);

            std::string imageUrl = extraerUrlImagen(jsonResponse);
            if (imageUrl.empty()) {
                std::cerr << "No se encontro la URL de la imagen en la respuesta JSON." << std::endl;
                continue;
            }

            std::string downloadedImageFileName = "downloaded_image.jpg";
            descargarImagen(imageUrl, downloadedImageFileName);

            std::string bmpImageFileName = "downloaded_image.bmp";
            convertirABmp(downloadedImageFileName, bmpImageFileName);

            std::cout << "Imagen descargada y guardada como " << bmpImageFileName << std::endl;

            // Mostrar la imagen con la palabra en inglés y español
            mostrarImagenConGraficos(bmpImageFileName, eleccion == 1 ? palabra : palabraTraducida, eleccion == 1  ? palabraTraducida : palabra);
        } else {
            std::cerr << "Error en la traduccion." << std::endl;
        }
    }

    std::cout << "Programa terminado." << std::endl;
    return 0;
}
