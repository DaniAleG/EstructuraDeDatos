#include <iostream>
using namespace std;
void impresionRecursiva(int n) {
    if (n <= 0) {
        return;
    }
    
    std::cout << n << " ";
    
    impresionRecursiva(n - 1);
}

int main() {
    int num;
    cout << "Ingrese un numero: ";
    cin >> num;
    impresionRecursiva(num);
    
    return 0;
}