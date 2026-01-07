#include <iostream>
#include <vector>

using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
};

void mostrarMenu() {
    cout << "\n____________________________Menu Principal____________________________\n";
    cout << "1. Ingresar conjunto de numeros enteros.\n";
    cout << "2. Mostrar conjunto de numeros enteros.\n";
    cout << "3. Ordenar conjunto de numeros enteros (Burbuja).\n";
    cout << "4. Buscar un numero en el conjunto.\n";
    cout << "5. Arbol binario (recorridos).\n";
    cout << "6. Grafo (recorrido DFS).\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

void ingresarEnteros(vector<int>& enteros) {
    enteros.clear();
    int n;
    cout << "Cantidad de numeros: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int dato;
        cout << "Numero en posicion " << i + 1 << ": ";
        cin >> dato;
        enteros.push_back(dato);
    }
}

void mostrarEnteros(const vector<int>& enteros) {
    if (enteros.empty()) {
        cout << "No hay enteros registrados.\n";
        return;
    }
    for (size_t i = 0; i < enteros.size(); i++) {
        cout << "Posicion " << i + 1 << ": " << enteros[i] << endl;
    }
}

void ordenarBurbuja(vector<int>& enteros) {
    if (enteros.empty()) {
        cout << "No hay datos para ordenar.\n";
        return;
    }

    cout << "\nANTES DE ORDENAR:\n";
    mostrarEnteros(enteros);

    for (size_t i = 0; i < enteros.size(); i++) {
        for (size_t j = 0; j < enteros.size() - 1; j++) {
            if (enteros[j] > enteros[j + 1]) {
                int aux = enteros[j];
                enteros[j] = enteros[j + 1];
                enteros[j + 1] = aux;
            }
        }
    }

    cout << "\nDESPUES DE ORDENAR:\n";
    mostrarEnteros(enteros);
}

void buscarEntero(const vector<int>& enteros) {
    if (enteros.empty()) {
        cout << "No hay numeros para buscar.\n";
        return;
    }

    int dato;
    cout << "Numero a buscar: ";
    cin >> dato;

    for (size_t i = 0; i < enteros.size(); i++) {
        if (enteros[i] == dato) {
            cout << "Encontrado en posicion " << i + 1 << endl;
            cout << "			Numero: " << dato <<endl;
            return;
        }
    }
    cout << "Numero no encontrado.\n";
}

Nodo* crearNodo(int dato) {
    return new Nodo{dato, nullptr, nullptr};
}

Nodo* insertar(Nodo* raiz, int dato) {
    if (!raiz) return crearNodo(dato);
    if (dato < raiz->dato)
        raiz->izq = insertar(raiz->izq, dato);
    else
        raiz->der = insertar(raiz->der, dato);
    return raiz;
}

void inorden(Nodo* r) {
    if (r) {
        inorden(r->izq);
        cout << r->dato << " ";
        inorden(r->der);
    }
}

void preorden(Nodo* r) {
    if (r) {
        cout << r->dato << " ";
        preorden(r->izq);
        preorden(r->der);
    }
}

void postorden(Nodo* r) {
    if (r) {
        postorden(r->izq);
        postorden(r->der);
        cout << r->dato << " ";
    }
}

void mostrarArbol(const vector<int>& enteros) {
    if (enteros.empty()) {
        cout << "Primero ingrese enteros.\n";
        return;
    }

    Nodo* raiz = nullptr;
    for (int v : enteros)
        raiz = insertar(raiz, v);

    cout << "Recorrido INORDEN (ascendente): ";
    inorden(raiz);
    cout << "\nRecorrido PREORDEN: ";
    preorden(raiz);
    cout << "\nRecorrido POSTORDEN: ";
    postorden(raiz);
    cout << endl;
}

void dfs(int v, vector<vector<int>>& grafo, vector<bool>& visitado) {
    visitado[v] = true;
    cout << v << " ";
    for (int u : grafo[v]) {
        if (!visitado[u])
            dfs(u, grafo, visitado);
    }
}

void mostrarGrafo(const vector<int>& enteros) {
    if (enteros.size() < 2) {
        cout << "Se requieren al menos 2 elementos para el grafo.\n";
        return;
    }

    int n = enteros.size();
    vector<vector<int>> grafo(n);

    for (int i = 0; i < n - 1; i++) {
        grafo[i].push_back(i + 1);
        grafo[i + 1].push_back(i);
    }

    vector<bool> visitado(n, false);
    cout << "Recorrido DFS del grafo (indices): ";
    dfs(0, grafo, visitado);
    cout << endl;
}

int main() {
    vector<int> enteros;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            ingresarEnteros(enteros);
            break;
        case 2:
            mostrarEnteros(enteros);
            break;
        case 3:
            ordenarBurbuja(enteros);
            break;
        case 4:
            buscarEntero(enteros);
            break;
        case 5:
            mostrarArbol(enteros);
            break;
        case 6:
            mostrarGrafo(enteros);
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}

