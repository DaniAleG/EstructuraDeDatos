#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Puntos{
    private:
        T x;
        T y;
    public: 
        Puntos(T x=0, T y=0): x(x), y(y){}
        void setX(T x){
            x = x;
        }
        void setY(T y){
            y = y;
        }
        T getX() const{
            return x;
        }
        T getY() const{
            return y;
        }
        T distancia(const Puntos& puntito)const{
            T dx = x-puntito.x;
            T dy = y-puntito.y;
            return std :: sqrt(dx*dx+dy*dy);
        }
};