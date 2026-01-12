/**
Implemente un programa en C++ que reciba un arreglo de números enteros de tamaño variable 
y realice su ordenamiento utilizando un proceso que permita dividir el problema en partes 
más pequeñas, resolver cada parte de manera independiente y combinar los resultados. 
El programa debe mostrar el arreglo original y el arreglo ordenado.
**/

#include <iostream>

using namespace std;

class Ordenador {
public:
    void merge(int arr[], int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        int* izquierda = new int[n1];
        int* derecha = new int[n2];

        for (int i = 0; i < n1; i++)
            izquierda[i] = arr[inicio + i];

        for (int j = 0; j < n2; j++)
            derecha[j] = arr[medio + 1 + j];

        int i = 0, j = 0, k = inicio;

        while (i < n1 && j < n2) {
            if (izquierda[i] <= derecha[j]) {
                arr[k] = izquierda[i];
                i++;
            } else {
                arr[k] = derecha[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = izquierda[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = derecha[j];
            j++;
            k++;
        }

        delete[] izquierda;
        delete[] derecha;
    }

    void mergeSort(int arr[], int inicio, int fin) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;
            mergeSort(arr, inicio, medio);
            mergeSort(arr, medio + 1, fin);
            merge(arr, inicio, medio, fin);
        }
    }
};

int main() {
    int arrtam;
    cout << "Ingrese el tamanio del arreglo: ";
    cin >> arrtam;
    cout << endl;

    int* arr = new int[arrtam];

    for (int i = 0; i < arrtam; i++) {
        cout << "Ingrese numero de posicion " << i << ": ";
        cin >> arr[i];
    }
    cout <<endl;

    cout << "Arreglo desordenado: " << endl;
    for (int j = 0; j < arrtam; j++) {
        cout << arr[j] << " ";
    }
    cout << endl;

    Ordenador ord;
    ord.mergeSort(arr, 0, arrtam - 1);

    cout << "Arreglo ordenado con MergeSort: " << endl;
    for (int k = 0; k < arrtam; k++) {
        cout << arr[k] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}

