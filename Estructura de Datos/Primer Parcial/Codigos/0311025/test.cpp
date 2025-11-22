#include <iostream>

using namespace std;

void insertar(int &num)
{
    if (num == 0)
    {
        cout << "El numero es nulo" << endl;
    }
    else
    {
        cout << "El numero es: " << num << endl;
    }
}

int main()
{
    int num;
    insertar(num);
    return 0;
}