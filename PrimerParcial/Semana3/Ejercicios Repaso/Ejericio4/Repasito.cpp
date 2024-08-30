#include <iostream>
#include <cmath>
#include <memory>

// Clase template Vector
template <typename T>
class Vector {
private:
    std::unique_ptr<T[]> data;
    size_t size;

public:
    // Constructor
    Vector(size_t n) : size(n), data(std::make_unique<T[]>(n)) {}

    // Constructor por copia
    Vector(const Vector& other) : size(other.size), data(std::make_unique<T[]>(other.size)) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Operador de asignación
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        size = other.size;
        data = std::make_unique<T[]>(size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // Operador de suma
    Vector operator+(const Vector& other) const {
        if (size != other.size) throw std::invalid_argument("El tamaño del vector no coincide");
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Operador de multiplicación por un escalar
    Vector operator*(T scalar) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // Acceso a los elementos
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // Función recursiva para calcular la norma (magnitud) del vector
    T norm(size_t index) const {
        if (index == 0) return data[0] * data[0];
        return data[index] * data[index] + norm(index - 1);
    }

    T norm() const {
        return std::sqrt(norm(size - 1));
    }

    // Método para imprimir el vector
    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Función principal
int main() {
    // Crear dos vectores
    Vector<double> v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector<double> v2(3);
    v2[0] = 4.0;
    v2[1] = 5.0;
    v2[2] = 6.0;

    // Sumar los vectores
    auto sum = v1 + v2;

    // Multiplicar por un escalar
    auto scaled = v1 * 2.0;

    // Calcular la norma usando una lambda
    auto lambdaNorm = [](const Vector<double>& vec) {
        return vec.norm();
    };

    // Imprimir los resultados
    std::cout << "v1: ";
    v1.print();
    std::cout << "v2: ";
    v2.print();
    std::cout << "v1 + v2: ";
    sum.print();
    std::cout << "v1 * 2.0: ";
    scaled.print();
    std::cout << "Norma de v1: " << lambdaNorm(v1) << std::endl;

    return 0;
}
