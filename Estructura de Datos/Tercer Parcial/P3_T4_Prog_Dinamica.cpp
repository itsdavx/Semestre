#include <iostream>
using namespace std;

int main() {
    int n;
    int limite;

    cout << "Ingrese el numero de elementos: ";
    cin >> n;
    cout << "Ingrese el limite maximo de costo: ";
    cin >> limite;

    int id[n + 1];
    int costo[n + 1];
    int beneficio[n + 1];

    for (int i = 1; i <= n; i++) {
        cout << "Elemento " << i << endl;
        cout << "Identificador: ";
        cin >> id[i];
        cout << "Costo: ";
        cin >> costo[i];
        cout << "Beneficio: ";
        cin >> beneficio[i];
    }

    // Tabla de programacion dinamica
    int dp[n + 1][limite + 1];

    // Inicializacion de la tabla
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= limite; j++) {
            dp[i][j] = 0;
        }
    }

    // Construccion de la tabla (programacion dinamica)
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= limite; j++) {
            if (costo[i] <= j) {
                int incluir = beneficio[i] + dp[i - 1][j - costo[i]];
                int excluir = dp[i - 1][j];
                dp[i][j] = (incluir > excluir) ? incluir : excluir;
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Mostrar tabla de resultados intermedios
    cout << endl;
    cout << "Tabla de programacion dinamica:" << endl;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= limite; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    // Resultado final
    cout << endl;
    cout << "Beneficio maximo alcanzado: " << dp[n][limite] << endl;

    // Recuperar elementos seleccionados
    cout << "Elementos seleccionados:" << endl;
    int j = limite;

    for (int i = n; i > 0; i--) {
        if (dp[i][j] != dp[i - 1][j]) {
            cout << "Elemento ID: " << id[i]
                 << " | Costo: " << costo[i]
                 << " | Beneficio: " << beneficio[i] << endl;
            j = j - costo[i];
        }
    }

    return 0;
}

