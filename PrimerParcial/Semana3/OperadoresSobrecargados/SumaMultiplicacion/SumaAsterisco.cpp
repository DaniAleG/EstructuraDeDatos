#include <iostream>

class SumaMultiplicacion {
private:
    int valor;

public:
    // Constructor
    SumaMultiplicacion(int val) : valor(val) {}

    // Sobrecarga del operador *
    SumaMultiplicacion operator*(const SumaMultiplicacion& otro) const {
        return SumaMultiplicacion(valor + otro.valor);
    }

    // Método para obtener el valor
    int obtenerValor() const {
        return valor;
    }
};

int main() {
    // Crear dos objetos de la clase SumaMultiplicacion
    SumaMultiplicacion numero1(5);
    SumaMultiplicacion numero2(3);

    // Realizar la suma utilizando el operador *
    SumaMultiplicacion resultado = numero1 * numero2;

    // Mostrar el resultado
    std::cout << "El resultado de la suma es: " << resultado.obtenerValor() << std::endl;

    return 0;
}
