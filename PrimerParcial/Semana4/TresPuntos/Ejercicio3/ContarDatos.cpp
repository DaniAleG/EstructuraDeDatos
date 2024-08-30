#include <iostream>
template <typename... Args>
int contar(Args... args){
    return sizeof...(args);
}
int main(){
    std :: cout << contar(1,2.3,"Cesar",'a') << std :: endl;
    std :: cout << contar() << std :: endl;
    
}