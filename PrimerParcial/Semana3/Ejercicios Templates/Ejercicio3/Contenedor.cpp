#include <iostream>
template <class T1, class T2>
class Contenedor{
    public:
    T1 dato1;
    T2 dato2;
    Contenedor(T1 d1, T2 d2): dato1(d1), dato2(d2){}
};