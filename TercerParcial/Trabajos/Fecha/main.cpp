#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

// Estructura para manejar un feriado
struct Feriado {
    int dia;
    int mes;
    string nombre;
    bool esNoRecuperable; // Indica si el feriado no es recuperable
};

// Funcion para verificar si un anio es bisiesto
bool esAnioBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

// Funcion para obtener el numero de dias en un mes
int obtenerDiasDelMes(int mes, int anio) {
    // Dias por mes
    const int diasPorMes[] = {31, (esAnioBisiesto(anio) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return diasPorMes[mes - 1];
}

// Funcion para validar el dia del mes teniendo en cuenta el anio bisiesto
bool esDiaValido(int dia, int mes, int anio) {
    if (mes < 1 || mes > 12) {
        return false; // Mes invalido
    }

    if (dia < 1 || dia > obtenerDiasDelMes(mes, anio)) {
        return false; // Dia fuera del rango del mes
    }

    return true;
}

// Funcion para agregar un mes a una fecha dada
tm agregarMes(tm fecha, int meses) {
    fecha.tm_mon += meses;
    mktime(&fecha);  // Normaliza la fecha
    return fecha;
}

// Funcion para ajustar los dias no trasladables
bool esFeriadoNoTrasladable(const tm& fecha) {
    // No trasladables: 1 de enero, 25 de diciembre y Carnaval
    return (fecha.tm_mday == 1 && fecha.tm_mon == 0) || 
           (fecha.tm_mday == 25 && fecha.tm_mon == 11) || 
           (fecha.tm_mday == 13 && fecha.tm_mon == 1); // Carnaval
}

// Funcion para ajustar la fecha de pago segun los feriados y reglas
tm ajustarFeriado(tm fecha, const vector<Feriado>& feriados) {
    // Lambda para ajustar el fin de semana
    auto ajustarFinDeSemana = [](tm& fecha) {
        switch (fecha.tm_wday) {
            case 0: // Domingo
                fecha.tm_mday += 1; // Trasladar al lunes posterior
                break;
            case 6: // Sabado
                fecha.tm_mday -= 1; // Trasladar al viernes anterior
                break;
            default:
                break;
        }
        mktime(&fecha);
    };

    // Comprobar si la fecha cae en un feriado no trasladable
    if (esFeriadoNoTrasladable(fecha)) {
        return fecha;
    }

    // Comprobar si la fecha cae en un feriado
    for (auto& feriado : feriados) {
        if (feriado.dia == fecha.tm_mday && feriado.mes == fecha.tm_mon + 1) {
            if (feriado.esNoRecuperable) {
                // Ajustar segun el dia de la semana para feriados no recuperables
                switch (fecha.tm_wday) {
                    case 1: // Martes
                        fecha.tm_mday -= 1; // Trasladar al lunes previo
                        break;
                    case 3: // Miercoles
                    case 4: // Jueves
                        fecha.tm_mday += (5 - fecha.tm_wday); // Trasladar al viernes inmediato
                        break;
                    case 0: // Domingo
                        fecha.tm_mday += 1; // Trasladar al lunes posterior
                        break;
                    case 6: // Sabado
                        fecha.tm_mday -= 1; // Trasladar al viernes anterior
                        break;
                    default:
                        break;
                }
                mktime(&fecha);
                // Ajustar fines de semana
                ajustarFinDeSemana(fecha);
            }
        }
    }

    // Ajustar fines de semana (sabado y domingo)
    ajustarFinDeSemana(fecha);

    return fecha;
}

// Funcion recursiva para calcular y mostrar los pagos
void calcularPagosRecursivo(tm fechaPago, double montoPrestamo, double tasaInteresAnual, int numeroPagos, const vector<Feriado>& feriados, double& totalPagos, int contador = 1) {
    if (contador > numeroPagos) return; // Caso base: hemos calculado todos los pagos

    double pagoMensual = montoPrestamo * (tasaInteresAnual / 12) / (1 - pow(1 + tasaInteresAnual / 12, -numeroPagos));
    tm fechaAjustada = ajustarFeriado(fechaPago, feriados);

    cout << put_time(&fechaAjustada, "%d/%m/%Y") << " | $" << fixed << setprecision(2) << pagoMensual << endl;

    totalPagos += pagoMensual; // Acumulamos el total de pagos

    // Calcular la fecha del siguiente pago
    tm siguienteFechaPago = agregarMes(fechaAjustada, 1);

    // Llamada recursiva para el siguiente mes
    calcularPagosRecursivo(siguienteFechaPago, montoPrestamo, tasaInteresAnual, numeroPagos, feriados, totalPagos, contador + 1);
}

// Funcion para imprimir la boleta de prestamos
void imprimirBoleta(tm fechaInicial, double montoPrestamo, double tasaInteresAnual, int numeroPagos, const vector<Feriado>& feriados) {
    cout << fixed << setprecision(2);
    cout << "Fecha inicial del prestamo: " << put_time(&fechaInicial, "%d/%m/%Y") << endl;
    cout << "Monto del prestamo: $" << montoPrestamo << endl;
    cout << "Tasa de interes anual: " << tasaInteresAnual * 100 << "%" << endl;
    cout << "Numero de pagos: " << numeroPagos << endl;
    cout << "Pago mensual: $" << montoPrestamo * (tasaInteresAnual / 12) / (1 - pow(1 + tasaInteresAnual / 12, -numeroPagos)) << endl;
    cout << endl;

    cout << "Boleta de pagos:" << endl;
    cout << "Fecha de Pago   | Pago Mensual" << endl;
    cout << "----------------|-------------" << endl;

    double totalPagos = 0.0;

    // Calcular y mostrar los pagos usando recursion
    calcularPagosRecursivo(fechaInicial, montoPrestamo, tasaInteresAnual, numeroPagos, feriados, totalPagos);

    cout << "----------------|-------------" << endl;
    cout << "Total de Pagos | $" << fixed << setprecision(2) << totalPagos << endl;
}

int main() {
    int anio, mes, dia, numeroPagos;
    double montoPrestamo, tasaInteresAnual;

    // Definir los feriados (incluyendo algunos ejemplos y locales)
    vector<Feriado> feriados = {
        {13, 2, "Carnaval", false}, // No trasladable
        {1, 1, "Anio Nuevo", false}, // No trasladable
        {25, 12, "Navidad", false}, // No trasladable
        {24, 5, "Batalla de Pichincha", true}, // No recuperable, se une al fin de semana
        {10, 8, "Primer Grito de Independencia", true}, // No recuperable, se traslada al viernes anterior
        {9, 10, "Independencia de Guayaquil", true}, // No recuperable, se pasa al viernes anterior
        {2, 11, "Dia de los Difuntos", true}, // No recuperable, se traslada al viernes anterior
        {3, 11, "Independencia de Cuenca", true} // No recuperable, se traslada al lunes siguiente
    };

    // Entrada de datos
    while (true) {
        cout << "Ingrese la fecha inicial del prestamo (anio mes dia): ";
        cin >> anio >> mes >> dia;
        
        // Validar fecha inicial
        if (esDiaValido(dia, mes, anio)) {
            break; // Fecha valida, salir del bucle
        } else {
            cerr << "Fecha invalida. Por favor, ingrese una fecha valida (dia, mes y anio)." << endl;
        }
    }

    cout << "Ingrese el monto del prestamo: ";
    cin >> montoPrestamo;
    cout << "Ingrese la tasa de interes anual (en porcentaje): ";
    cin >> tasaInteresAnual;
    tasaInteresAnual /= 100; // Convertir a decimal
    cout << "Ingrese el numero de meses de pagos: ";
    cin >> numeroPagos;

    // Crear la fecha inicial
    tm fecha = {};
    fecha.tm_year = anio - 1900;
    fecha.tm_mon = mes - 1;
    fecha.tm_mday = dia;
    fecha.tm_hour = 0;
    fecha.tm_min = 0;
    fecha.tm_sec = 0;
    fecha.tm_isdst = -1; // Informacion de horario de verano desconocida
    mktime(&fecha); // Normalizar la fecha
    tm fechaInicial = fecha;

    // Imprimir la boleta de prestamos
    imprimirBoleta(fechaInicial, montoPrestamo, tasaInteresAnual, numeroPagos, feriados);

    return 0;
}
