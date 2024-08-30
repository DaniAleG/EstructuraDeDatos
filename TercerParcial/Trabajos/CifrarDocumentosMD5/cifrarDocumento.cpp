/*Universidad de las Fuerzas Armadas ESPE
                CIFRADO MD5
Nombre: Camila Barrionuevo
        César González
        Daniel Guevara
        NRC:16426
Fecha de modificacion: 24/08/2024 */
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>  // Para _getch()
#include <cstdlib>  // Para system("cls")

#define MENU_OPTIONS_COUNT 3

typedef void* (*CreateMD5Func)();
typedef void (*DestroyMD5Func)(void*);
typedef void (*MD5UpdateFunc)(void*, const unsigned char*, size_t);
typedef char* (*MD5FinalizeFunc)(void*);

void hashString(const std::string& input, std::string& hashOutput, CreateMD5Func createMD5, MD5UpdateFunc update, MD5FinalizeFunc finalize, DestroyMD5Func destroyMD5) {
    void* md5Instance = createMD5();
    if (!md5Instance) {
        std::cerr << "No se pudo crear la instancia de MD5" << std::endl;
        return;
    }

    update(md5Instance, reinterpret_cast<const unsigned char*>(input.c_str()), input.size());

    char* hashCStr = finalize(md5Instance);
    if (!hashCStr) {
        std::cerr << "Error al finalizar el cálculo del hash" << std::endl;
        destroyMD5(md5Instance);
        return;
    }
    hashOutput = hashCStr;

    delete[] hashCStr;
    destroyMD5(md5Instance);
}

void processText(const std::string& text, const std::string& outputFile, CreateMD5Func createMD5, MD5UpdateFunc update, MD5FinalizeFunc finalize, DestroyMD5Func destroyMD5) {
    std::string hash;
    hashString(text, hash, createMD5, update, finalize, destroyMD5);

    std::ifstream inFile(outputFile);
    bool fileExists = inFile.good();
    inFile.close();

    std::ofstream outFile(outputFile, std::ios::app); // Abre en modo append
    if (!outFile) {
        std::cerr << "No se pudo abrir el archivo de salida" << std::endl;
        return;
    }

    if (fileExists) {
        // Verificar si el hash de la palabra ya está en el archivo
        std::ifstream checkFile(outputFile);
        std::string line;
        bool found = false;
        while (std::getline(checkFile, line)) {
            if (line == hash) {
                found = true;
                break;
            }
        }
        checkFile.close();

        if (!found) {
            outFile << hash << "\n";
        }
    } else {
        outFile << hash << "\n";
    }
    
    outFile.close();

    std::cout << "Cifrado completado. Hash guardado en " << outputFile << std::endl;
    // Abrir el archivo de salida
    system(("start " + outputFile).c_str());
}

void processFile(const std::string& inputFile, const std::string& outputFile, CreateMD5Func createMD5, MD5UpdateFunc update, MD5FinalizeFunc finalize, DestroyMD5Func destroyMD5) {
    std::ifstream inFile(inputFile, std::ios::binary | std::ios::ate);
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo de entrada" << std::endl;
        return;
    }

    size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    unsigned char* buffer = new unsigned char[fileSize];
    inFile.read(reinterpret_cast<char*>(buffer), fileSize);
    inFile.close();

    std::string fileHash;
    hashString(inputFile, fileHash, createMD5, update, finalize, destroyMD5);

    void* md5Instance = createMD5();
    if (!md5Instance) {
        std::cerr << "No se pudo crear la instancia de MD5" << std::endl;
        delete[] buffer;
        return;
    }

    update(md5Instance, buffer, fileSize);

    char* hashCStr = finalize(md5Instance);
    if (!hashCStr) {
        std::cerr << "Error al finalizar el cálculo del hash" << std::endl;
        delete[] buffer;
        delete[] hashCStr;
        destroyMD5(md5Instance);
        return;
    }
    std::string contentHash(hashCStr);

    delete[] buffer;
    delete[] hashCStr;
    destroyMD5(md5Instance);

    std::ofstream outFile(outputFile, std::ios::app); // Abre en modo append
    if (!outFile) {
        std::cerr << "No se pudo abrir el archivo de salida" << std::endl;
        return;
    }

    std::ifstream checkFile(outputFile);
    bool fileExists = checkFile.good();
    checkFile.close();

    if (fileExists) {
        std::ifstream existingFile(outputFile);
        std::string line;
        bool found = false;
        while (std::getline(existingFile, line)) {
            if (line.find("Hash del nombre del archivo:") != std::string::npos &&
                line.find(fileHash) != std::string::npos) {
                found = true;
                break;
            }
        }
        existingFile.close();

        if (!found) {
            outFile << "Hash del nombre del archivo: " << fileHash << "\n";
        }
    } else {
        outFile << "Hash del nombre del archivo: " << fileHash << "\n";
    }

    outFile << "Hash del contenido del archivo: " << contentHash << "\n";
    outFile.close();

    std::cout << "Cifrado completado. Hash guardado en " << outputFile << std::endl;

    // Abrir el archivo de salida
    system(("start " + outputFile).c_str());
}

void mostrarMenu(int opcionSeleccionada) {
    system("cls");
    std::string opcionesMenu[MENU_OPTIONS_COUNT] = {
        "Cifrar texto",
        "Cifrar archivo",
        "Salir"
    };

    std::cout << "-------------- Menu Cifrado --------------\n";
    std::cout << "Seleccione una opcion:\n";
    for (int i = 0; i < MENU_OPTIONS_COUNT; ++i) {
        if (i == opcionSeleccionada) {
            std::cout << "> " << opcionesMenu[i] << " <" << "\n";
        } else {
            std::cout << "   " << opcionesMenu[i] << "\n";
        }
    }
}

int main() {
    // Cargar la DLL
    HINSTANCE hInstLibrary = LoadLibraryW(L"md5.dll");
    if (!hInstLibrary) {
        std::cerr << "No se pudo cargar md5.dll" << std::endl;
        return 1;
    }

    // Obtener las funciones de la DLL
    CreateMD5Func createMD5 = (CreateMD5Func)GetProcAddress(hInstLibrary, "CreateMD5");
    DestroyMD5Func destroyMD5 = (DestroyMD5Func)GetProcAddress(hInstLibrary, "DestroyMD5");
    MD5UpdateFunc update = (MD5UpdateFunc)GetProcAddress(hInstLibrary, "MD5_Update");
    MD5FinalizeFunc finalize = (MD5FinalizeFunc)GetProcAddress(hInstLibrary, "MD5_Finalize");
    if (!createMD5 || !destroyMD5 || !update || !finalize) {
        std::cerr << "No se pudieron obtener las funciones de la DLL" << std::endl;
        FreeLibrary(hInstLibrary);
        return 1;
    }

    int opcionSeleccionada = 0;
    char tecla;
    bool salir = false;

    do {
        mostrarMenu(opcionSeleccionada);

        tecla = _getch();
        switch (tecla) {
        case 72: // Flecha arriba
            if (opcionSeleccionada > 0) {
                --opcionSeleccionada;
            }
            break;
        case 80: // Flecha abajo
            if (opcionSeleccionada < MENU_OPTIONS_COUNT - 1) {
                ++opcionSeleccionada;
            }
            break;
        case 13: // Enter
            system("cls");
            switch (opcionSeleccionada) {
            case 0: // Cifrar texto
                {
                    std::string text;
                    std::string outputFile;

                    std::cout << "Ingrese el texto a cifrar: ";
                    std::getline(std::cin, text);

                    std::cout << "Ingrese el nombre del archivo de salida: ";
                    std::getline(std::cin, outputFile);

                    processText(text, outputFile, createMD5, update, finalize, destroyMD5);
                }
                break;
            case 1: // Cifrar archivo
                {
                    std::string inputFile;
                    std::string outputFile;

                    std::cout << "Ingrese el nombre del archivo a cifrar: ";
                    std::getline(std::cin, inputFile);

                    std::cout << "Ingrese el nombre del archivo de salida: ";
                    std::getline(std::cin, outputFile);

                    processFile(inputFile, outputFile, createMD5, update, finalize, destroyMD5);
                }
                break;
            case 2: // Salir
                salir = true;
                std::cout << "Saliendo...\n";
                break;
            }
            if (!salir) {
                std::cout << "Presione cualquier tecla para continuar...\n";
                _getch(); // Esperar que el usuario presione una tecla
            }
            break;
        }
    } while (!salir);

    FreeLibrary(hInstLibrary);
    return 0;
}
