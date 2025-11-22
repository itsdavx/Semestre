#include <iostream>

using namespace std;

#define MAX 5

struct Cola
{
    int datos[MAX];
    int frente;
    int rear;
};

void inicializarCola(Cola &c)
{
    c.frente = 0;
    c.rear = -1;
}

bool estaVacia(const Cola &c)
{
    return c.rear < c.frente;
}

bool estaLlena(const Cola &c)
{
    return c.rear == MAX - 1;
}

void encolar(Cola &c, int valor)
{
    if (!estaLlena(c))
    {
        c.rear++;
        c.datos[c.rear] = valor;
        cout << "Encolado: " << valor << endl;
    }
    else
    {
        cout << "Cola llena: " << valor << endl;
    }
}

int desencolar(Cola &c)
{
    if (!estaVacia(c))
    {
        int valor = c.datos[c.frente];
        c.frente++;
        cout << "Desencolado: " << valor << endl;
        return valor;
    }
    else
    {
        cout << "Cola vacia" << endl;
        return -1; // Indicador de cola vacía
    }
}

int main()
{
    Cola c;
    inicializarCola(c);

    encolar(c, 10);
    encolar(c, 20);
    encolar(c, 30);

    cout << "Desencolado: " << desencolar(c) << endl;
    cout << "Desencolado: " << desencolar(c) << endl;

    encolar(c, 40);
    encolar(c, 50);
    encolar(c, 60); // Intentara encolar en una cola llena

    cout << "Desencolado: " << desencolar(c) << endl;

    /*Para comprobacion - imprime direcciones de memoria contiguas
    cout << "Direccion de la cola: " << &c << endl;
    cout << "Direccion del arreglo datos: " << &c.datos << endl;
    cout << "Direccion del primer elemento: " << &c.datos[0] << endl;*/

    return 0;
}