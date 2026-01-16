#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Elemento {
    int id;
    int costo;
    int beneficio;
};

int main() {
    cout << "=== PROBLEMA DE LA MOCHILA - PROGRAMACION DINAMICA ===" << endl;

    int capacidad;
    cout << "\nCapacidad maxima: ";
    cin >> capacidad;

    int n;
    cout << "Numero de elementos: ";
    cin >> n;

    vector<Elemento> elementos(n);
    cout << "\nIngrese los datos de cada elemento (ID, Costo, Beneficio):" << endl;

    for (int i = 0; i < n; i++) {
        cout << "Elemento " << (i + 1) << " - ID: ";
        cin >> elementos[i].id;
        cout << "  Costo: ";
        cin >> elementos[i].costo;
        cout << "  Beneficio: ";
        cin >> elementos[i].beneficio;
    }

    // CREAR TABLA DP
    vector<vector<int>> dp(n + 1, vector<int>(capacidad + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacidad; w++) {
            // No tomar el elemento
            dp[i][w] = dp[i - 1][w];

            // Intentar tomar el elemento
            if (elementos[i - 1].costo <= w) {
                int beneficioConElemento = dp[i - 1][w - elementos[i - 1].costo] + elementos[i - 1].beneficio;
                if (beneficioConElemento > dp[i][w]) {
                    dp[i][w] = beneficioConElemento;
                }
            }
        }
    }

    // MOSTRAR TABLA DP
    cout << "\n\n=== TABLA DE PROGRAMACION DINAMICA ===" << endl;
    cout << "Filas: elementos (0 a " << n << ") | Columnas: capacidad (0 a " << capacidad << ")" << endl;
    cout << "\nCapacidad: ";
    for (int w = 0; w <= capacidad; w++) {
        cout << setw(4) << w;
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << "Elem" << setw(2) << i << ": ";
        for (int w = 0; w <= capacidad; w++) {
            cout << setw(4) << dp[i][w];
        }
        cout << endl;
    }

    // RECONSTRUIR SOLUCIÓN
    cout << "\n\n=== RECONSTRUCCION DE LA SOLUCION ===" << endl;
    vector<int> seleccionados;
    int w = capacidad;
    int i = n;

    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            seleccionados.push_back(elementos[i - 1].id);
            cout << "Elemento " << elementos[i - 1].id << " SELECCIONADO (Costo: " 
                 << elementos[i - 1].costo << ", Beneficio: " << elementos[i - 1].beneficio << ")" << endl;
            w -= elementos[i - 1].costo;
        }
        i--;
    }

    // MOSTRAR RESULTADO FINAL
    cout << "\n\n=== RESULTADO FINAL ===" << endl;
    cout << "Elementos seleccionados: ";
    for (int id : seleccionados) {
        cout << id << " ";
    }
    cout << "\nBeneficio maximo: " << dp[n][capacidad] << endl;

    int costoTotal = 0;
    for (int id : seleccionados) {
        for (const auto& elem : elementos) {
            if (elem.id == id) {
                costoTotal += elem.costo;
                break;
            }
        }
    }
    cout << "Costo total utilizado: " << costoTotal << " / " << capacidad << endl;

    return 0;
}