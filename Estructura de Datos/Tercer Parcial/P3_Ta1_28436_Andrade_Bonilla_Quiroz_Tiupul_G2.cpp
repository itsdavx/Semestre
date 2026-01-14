#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Venta {
    string producto;
    double monto;
    int cantidad;

    Venta() : producto(""), monto(0.0), cantidad(0) {}

    Venta(string p, double m, int c) : producto(p), monto(m), cantidad(c) {}
};

void fusionar(vector<Venta>& ventas, int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    vector<Venta> izquierda(n1);
    vector<Venta> derecha(n2);

    for (int i = 0; i < n1; i++) {
        izquierda[i] = ventas[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        derecha[j] = ventas[medio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (izquierda[i].monto <= derecha[j].monto) {
            ventas[k] = izquierda[i];
            i++;
        } else {
            ventas[k] = derecha[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        ventas[k] = izquierda[i];
        i++;
        k++;
    }

    while (j < n2) {
        ventas[k] = derecha[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Venta>& ventas, int inicio, int fin) {
    if (inicio >= fin) return;

    int medio = inicio + (fin - inicio) / 2;

    mergeSort(ventas, inicio, medio);
    mergeSort(ventas, medio + 1, fin);
    fusionar(ventas, inicio, medio, fin);
}

void mostrarVentas(const vector<Venta>& ventas) {
    for (size_t i = 0; i < ventas.size(); i++) {
        cout << "       Producto: " << ventas[i].producto << endl;
        cout << "            Monto: $" << ventas[i].monto << endl;
        cout << "            Cantidad: " << ventas[i].cantidad << endl;
    }
}

int main() {
    vector<Venta> ventas = {
        Venta("Laptop", 1200.50, 2),
        Venta("Mouse", 25.99, 15),
        Venta("Teclado", 45.75, 8),
        Venta("Monitor", 350.00, 3),
        Venta("USB 32GB", 12.99, 30),
        Venta("Audifonos", 89.99, 12),
        Venta("Tablet", 299.99, 5),
        Venta("Impresora", 180.00, 4)
    };

    cout << "Ventas originales:\n";
    mostrarVentas(ventas);

    mergeSort(ventas, 0, ventas.size() - 1);

    cout << "\nVentas ordenadas por monto:\n";
    mostrarVentas(ventas);

    return 0;
}