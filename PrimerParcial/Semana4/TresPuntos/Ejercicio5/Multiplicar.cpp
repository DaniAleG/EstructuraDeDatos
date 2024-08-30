#include <iostream>
template <typename... Args>
auto multiplicar(Args... args){
    return(args*...);
}
int main(){
    std :: cout << "Multiplicacion 1: " << multiplicar(2,3,4,1,5) << std :: endl;
    std :: cout << "Multiplicacion 2: " << multiplicar(1.2,2,3.1,5.3) << std :: endl;
}