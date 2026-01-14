#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
int main() {
    int n;
    cout << "Ingrese un numero para calcular su Fibonacci: ";
    cin >> n;
    int resultado = fibonacci(n);
    cout << "El Fibonacci de " << n << " es: " << resultado << endl;
    return 0;
}