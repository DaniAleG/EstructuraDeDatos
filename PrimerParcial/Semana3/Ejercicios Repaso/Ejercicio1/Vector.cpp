#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
//Main, parametros no se utilizan
int main(int argc, char** argv) {
	//Inicializar un vector
	std::vector<int> data = {3,4,-1,-10,0};
	//Funcion lambda que compara si un dato es mayor a otro
	auto comp =[](int a, int b){ return a < b;};
	//Funcion para ordenar utilizando la funcion lambda como comparador
	std::sort(data.begin(),data.end(),comp);
	//Impresion datos Array
	for(int i=0;i<5;++i){
		std::cout<< "data [" << i << "]: " << data[i]<< "\n";
	}
	return 0;
}
