#include <iostream>
#include "Torres.cpp"

using namespace std;

int main() {
    int n;
    cout << "Las clavijas son A B C \n";
    cout << "Ingrese el numero de discos: ";
    cin >> n;

    Torres<int> torres;
    torres.torresHanoi(n, 'A', 'C', 'B');

    return 0;
}
