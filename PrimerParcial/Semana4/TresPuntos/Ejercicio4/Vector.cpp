#include <iostream>
#include <vector>
template <typename T, typename... Args>
std :: vector<T> vectorsito(Args... args){
    return std :: vector<T>{args...};
}
int main(){
    std :: vector<int> array = vectorsito<int>(1,2,3,4,5);
    for(int i : array){
        std :: cout << i <<" "; 
    }
    std :: cout << std :: endl;
}