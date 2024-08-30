#include "Empleado.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Empleado::Empleado() {
    idEmpleado = "";
    sueldo = 0;
    persona = new Persona();
    primero = nullptr;
    ultimo = nullptr;
}

Empleado::Empleado(string nombre, double sueldo, Persona* personita) {
    //this->idEmpleado = crearIdEmpleado();
    this->sueldo = sueldo;
    this->persona = personita;
    primero = nullptr;
    ultimo = nullptr;
}

void Empleado::setIdEmpleado(string id) {
    this->idEmpleado = id;
}

string Empleado::getIdEmpleado() {
    return this->idEmpleado;
}

void Empleado::setSueldo(double sueldo) {
    this->sueldo = sueldo;
}

double Empleado::getSueldo() {
    return this->sueldo;
}

Persona* Empleado::getPersona() {
    return this->persona;
}

void Empleado::setPersona(Persona* persona) {
    this->persona = persona;
}

std::string Empleado::validarSueldo(const char* msj) {
    std::string dato;
    char c;
    bool punto = false;
    int digitosDespuesDelPunto = 0;

    printf("%s", msj);

    while (true) {
        c = getch();
        if (c == 13) { // Enter key
            if (!dato.empty() && dato != ".") {
                break;
            }
        } else if (c == 8) { // Backspace key
            if (!dato.empty()) {
                if (dato.back() == '.') {
                    punto = false;
                    digitosDespuesDelPunto = 0;
                } else if (punto) {
                    digitosDespuesDelPunto--;
                }
                dato.pop_back();
                printf("\b \b");
            }
        } else if ((c >= '0' && c <= '9') || (c == '.' && !punto)) {
            if (c == '.') {
                punto = true;
            } else if (punto) {
                if (digitosDespuesDelPunto < 2) {
                    digitosDespuesDelPunto++;
                } else {
                    continue;
                }
            }
            dato += c;
            printf("%c", c);
        }
    }

    printf("\n");
    return dato;
}
bool Empleado::buscarEmpleado(const string& cedula) {
    ifstream archivo("empleado.txt");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        if (linea.find(cedula) != string::npos) {
            encontrado = true;
            break;
        }
    }
    archivo.close();
    if (encontrado) {
        return true;
    } else {
        return false;
    }
}


void Empleado::ingresarInicio(string dato) {
    Nodo* nuevo = new Nodo();
    nuevo->setDato(dato);
    if (this->primero == nullptr) {
        this->primero = nuevo;
        this->ultimo = nuevo;
    } else {
        nuevo->setSiguiente(this->primero);
        this->primero = nuevo;
    }
    cout << "Elemento " << dato << " insertado correctamente" << endl;
}

void Empleado::mostrarLista() {
    Nodo* actual = primero;
    while (actual != nullptr) {
        cout << actual->getDato() << " ";
        actual = actual->getSiguiente();
    }
    cout << endl;
}

Nodo* Empleado::getPrimero() {
    return primero;
}

Nodo* Empleado::getUltimo() {
    return ultimo;
}

void Empleado::setPrimero(Nodo* primero) {
    this->primero = primero;
}

void Empleado::setUltimo(Nodo* ultimo) {
    this->ultimo = ultimo;
}

Empleado::~Empleado() {
    Nodo* actual = primero;
    while (actual) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

int Empleado::obtenerContador() {
    // Aquí se debería implementar la lógica para obtener el contador actual del archivo o base de datos.
    // Por ejemplo:
    ifstream archivo("contador.txt");
    int contador = 0;
    if (archivo.is_open()) {
        archivo >> contador;
        archivo.close();
    }
    return contador;
}

void Empleado::guardarContador(int contador) {
    // Aquí se debería implementar la lógica para guardar el contador actualizado en el archivo o base de datos.
    // Por ejemplo:
    ofstream archivo("contador.txt");
    if (archivo.is_open()) {
        archivo << contador;
        archivo.close();
    }
}

string Empleado::formatearId(int numero) {
    stringstream ss;
    ss << setw(3) << setfill('0') << numero;
    return ss.str();
}

string Empleado::crearIdEmpleado() {
    string inicio = "ESPE-";
    int contador = obtenerContador();
    string id = inicio + formatearId(contador + 1);  // Generar el ID antes de incrementar el contador
    
    // Incrementar el contador y guardarlo
    guardarContador(contador + 1);

    return id;
}
void Empleado :: crearArchivoEmpleado(const string& nombre){
    // Crear un objeto de ofstream para escribir en el archivo
    std::ofstream archivoSalida(nombre);
    // Verificar si el archivo se abrió correctamente
    if (archivoSalida.is_open()) {
        archivoSalida.close();
        
    } else {
        cerr << "Error al abrir el archivo " << nombre << endl;
    }
}

bool Empleado :: buscarArchivo(const string& nombre){
    ifstream archivo(nombre);
    if (archivo.good()) {
        cout << "Archivo encontrado" << endl;
        return true;
        
    } else {
        cout << "Archivo no encontrado" << endl;
        return false;
    }
}
void Empleado::guardarDatos(string id, double sueldo, string cedula) {
    ofstream archivo("empleados.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Cedula: " << cedula << endl;
        archivo << "ID de empleado: " << id << endl;
        archivo << "Sueldo: " << sueldo << endl;
        archivo << "--------------------------------" << endl;
        archivo.close();
        cout << "Datos guardados correctamente en el archivo datos.txt" << endl;
    } else {
        cout << "Error al abrir el archivo datos.txt" << endl;
    }
}
void Empleado::mostrarContenido(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cerr << "No se han registrado empleados " << std::endl;
    }
}
