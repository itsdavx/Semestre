#include <iostream>
using namespace std;

const int N = 8;
int tablero[N];
int contador = 0;   // contador GLOBAL de soluciones

bool esSeguro(int fila, int columna) {
    for (int i = 0; i < fila; i++) {
        if (tablero[i] == columna ||
            tablero[i] - i == columna - fila ||
            tablero[i] + i == columna + fila) {
            return false;
        }
    }
    return true;
}

void resolverNReinas(int fila) {
    if (fila == N) {
        contador++;   // una solución encontrada

        for (int i = 0; i < N; i++) {
            cout << tablero[i] << " ";
        }
        cout << " // Solucion #" << contador << endl;
        return;
    }

    for (int columna = 0; columna < N; columna++) {
        if (esSeguro(fila, columna)) {
            tablero[fila] = columna;
            resolverNReinas(fila + 1);
        }
    }
}

int main() {
    resolverNReinas(0);
    cout << "\nTotal de soluciones: " << contador << endl;
    return 0;
}
