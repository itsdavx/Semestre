#include <iostream>
using namespace std;

class Factorial
{
public:
    int calcularFactorial(int n, int resulado = 1)
    {
        if (n == 0)
        {
            return resulado;
        }
        else
        {
            return calcularFactorial(n - 1, n * resulado);
        }
    }
};

int main()
{
    Factorial factorial;
    int numero;
    cout << "Ingrese un numero para calcular su factorial: ";
    cin >> numero;
    cout << "El factorial de " << numero << " es: " << factorial.calcularFactorial(numero) << endl;
    return 0;
}