#include <functional>
#include <iostream>
using namespace std;

// Estructura genérica que define un alias de tipo 't' para el tipo 'T'.
template<typename T>
struct t2t
{
    typedef T t;
};

// Estructura genérica fixpoint parametrizada por tres tipos: R (retorno), V1 y V2 (parámetros).
template<typename R, typename V1, typename V2>
struct fixpoint
{
    // Alias de tipos para simplificar la notación de funciones.
    typedef std::function<R (V1, V2)> func_t;           // Función que toma V1 y V2 y retorna R.
    typedef std::function<func_t (func_t)> tfunc_t;     // Función que toma una func_t y retorna otra func_t.
    typedef std::function<func_t (tfunc_t)> yfunc_t;    // Función que toma una tfunc_t y retorna una func_t.

    // Clase interna que define una función recursiva.
    class loopfunc_t {
    public:
        // Operador de llamada que permite que loopfunc_t se comporte como una función.
        func_t operator()(loopfunc_t v) const {
            return func(v);
        }

        // Constructor que inicializa el miembro func con una función.
        template<typename L>
        loopfunc_t(const L &l) : func(l) {}

        // Alias de tipos para los parámetros.
        typedef V1 Parameter1_t;
        typedef V2 Parameter2_t;

    private:
        std::function<func_t (loopfunc_t)> func;  // Función que toma una loopfunc_t y retorna una func_t.
    };

    // Función estática que implementa el combinador Y para definir funciones recursivas.
    static yfunc_t fix;
};

// Implementación de la función estática fix.
template<typename R, typename V1, typename V2>
typename fixpoint<R, V1, V2>::yfunc_t fixpoint<R, V1, V2>::fix = [](tfunc_t f) -> func_t {
    // Retorna una función recursiva.
    return [f](fixpoint<R, V1, V2>::loopfunc_t x){ return f(x(x)); }
    // Aplicación parcial para permitir la recursión.
    ([f](fixpoint<R, V1, V2>::loopfunc_t x) -> fixpoint<R, V1, V2>::func_t {
        auto &ff = f;
        // Definición de la función recursiva.
        return [ff, x](typename t2t<decltype(x)>::t::Parameter1_t v1,
                    typename t2t<decltype(x)>::t::Parameter2_t v2) {
            return ff(x(x))(v1, v2);
        };
    });
};

int main(int argc, char* argv[])
{
    // Función lambda que retorna el cuadrado de un número.
    auto term = [](int a) -> int {
        return a * a;
    };

    // Función lambda que incrementa un número.
    auto next = [](int a) -> int {
        return ++a;
    };

    // Definición de la función sum usando fixpoint para implementar recursión.
    auto sum = fixpoint<int, int, int>::fix(
    [term, next](std::function<int (int, int)> sum1) -> std::function<int (int, int)> {
        auto &term1 = term;
        auto &next1 = next;
        // Función recursiva que suma los cuadrados de los números en el rango [a, b].
        return [term1, next1, sum1](int a, int b) mutable -> int {
            if (a > b)
                return 0;
            else
                return term1(a) + sum1(next1(a), b);
        };
    });

    // Imprime el resultado de sumar los cuadrados de los números del 1 al 10.
    std::cout << sum(1, 10) << std::endl; // 385

    return 0;
}