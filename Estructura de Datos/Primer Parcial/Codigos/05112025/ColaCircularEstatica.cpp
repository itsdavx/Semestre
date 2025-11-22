#include <iostream>

using namespace std;

const int MAX = 5;

struct ColaCircular
{
    int data[MAX];
    int front;
    int rear;
    int count;
};

void inicializar(ColaCircular &c)
{
    c.front = 0;
    c.rear = -1;
    c.count = 0;
}

bool vacia(const ColaCircular &c)
{
    return c.count == 0;
}

bool llena(const ColaCircular &c)
{
    return c.count == MAX;
}  

bool encolar(ColaCircular &c, int valor)
{
    if (llena(c)) return false;
    c.rear = (c.rear + 1) % MAX;
    c.data[c.rear] = valor;
    c.count++;
    return true;
    
}

bool desencolar(ColaCircular &c, int &valor)
{
    if (vacia(c)) return false;
    valor = c.data[c.front];
    c.front = (c.front + 1) % MAX;
    c.count--;
    return true;
}  

int main()
{
    ColaCircular c;
    inicializar(c);

    for (int i = 1; i <= 5; ++i)
    {
        if (encolar(c, i*10))
            cout << "Encolado: " << i << endl;
        else
            cout << "Cola llena: " << i << endl;
    }

    int x;

    desencolar(c, x);
    cout << "Desencolado: " << x << endl;   
    encolar(c, 60);

    while (desencolar(c,x))
    cout << "Desencolado: " << x << endl;
    
    return 0;
}   