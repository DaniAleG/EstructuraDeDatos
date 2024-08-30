#include <iostream>
#include <vector>
template <typename T>
T proceso(const std::vector<T>& vector1, const std::vector<T>& vector2){
    if(vector1.size()!=vector2.size()){
        std :: cout << "Los arrays tienen distinta dimension" << std :: endl;
    }
    T resultado = 0;
    for(size_t i = 0; i < vector1.size(); i++){
        resultado += vector1[i] * vector2[i];
    }
    return resultado;
}
int main(){
    std :: vector<int> vector1 = {1,2,3,4,5};
    std :: vector<int> vector2 = {6,7,8,9,10};
    std :: vector<float> vector3 = {2.5,3.2,1.9,6.4,5.8};
    std :: vector<float> vector4 = {8.5,1.2,2.1,6.6,7.3};
    std :: cout << "El resultado de la suma de ints es: " << proceso(vector1,vector2) << std :: endl;
    std :: cout << "El resultado de la suma de floats es: " << proceso(vector3,vector4) << std :: endl;
}