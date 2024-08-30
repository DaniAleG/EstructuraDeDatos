#include <iostream>

template<typename T>
void imprimir(T dato) {
    std::cout << dato << std::endl;
}
template<typename T, typename... Args>
void imprimir(T dato, Args... args) {
    std::cout <<dato << " ";
    imprimir(args...);
}
int main(){
    imprimir(1,2.5,"Cesar", 'a');
    return 0;
}