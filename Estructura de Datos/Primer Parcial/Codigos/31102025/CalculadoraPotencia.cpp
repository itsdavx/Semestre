#include <iostream>

using namespace std;

int calculosuma(int n, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    else
    {
        return n * calculosuma(n, exp - 1);
    }
}

int main()
{
    int n = 10;
    int base = 2;

    cout << calculosuma(n, base) << endl;

    return 0;
}