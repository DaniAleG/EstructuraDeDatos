#include <iostream>
#include <functional>

using namespace std;

//Uso de plantillas
template<typename T, typename... Args>

struct fixpoint
{
    typedef function<T(Args...)> effective_type;
    typedef function<T(const effective_type&, Args...)> function_type;

    function_type f_nonr;
    //Sobrecarga de operador()
    T operator()(Args... args) const
    {
        return f_nonr(*this, args...);
    }

    fixpoint(const function_type& p_f)
        : f_nonr(p_f)
    {
    }
};


int main()
{
    //Funcion lambda que realiza la serie de fibonacci utilizando recursividad
    auto fib_nonr = [](const function<int(int)>& f, int n) -> int
    {
        return n < 2 ? n : f(n-1) + f(n-2);
    };
    //Instancia de fixpoint
    auto fib = fixpoint<int,int>(fib_nonr);

    for (int i = 0; i < 20; ++i)
    {
        cout << fib(i) << '\n';
    }
}
