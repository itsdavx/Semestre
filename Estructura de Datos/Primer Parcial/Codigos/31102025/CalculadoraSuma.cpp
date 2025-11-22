#include <iostream>

using namespace std;

int calculosuma(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n + calculosuma(n - 1);
    }
}

int main()
{
    int n = 10;

    calculosuma(n);

    return 0;
}