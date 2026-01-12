#include <iostream>
#include <string>
using namespace std;
typedef int Codigo;
typedef string Descripcion;
typedef int Cantidad;
typedef float Precio;
struct Producto {
    Codigo codigo;
    Descripcion descripcion;
    Cantidad cantidadDisponible;
    Precio precioUnitario;
};
struct NodoSimple {
    Producto dato;
    NodoSimple* siguiente;
};
void insertarSimple(NodoSimple*& cabeza, Producto prod) {
    NodoSimple* nuevo = new NodoSimple();
    nuevo->dato = prod;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}
void mostrarInventario(NodoSimple* cabeza) {
    cout << "INVENTARIO ORDENADO\n" << endl;
    while (cabeza != nullptr) {
        cout << "Codigo: " << cabeza->dato.codigo << endl;
        cout << "Descripcion: " << cabeza->dato.descripcion << endl;
        cout << "Stock: " << cabeza->dato.cantidadDisponible << endl;
        cout << "Precio: $" << cabeza->dato.precioUnitario << "\n"<< endl;
        cabeza = cabeza->siguiente;
    }
}
// Algoritmo Selection Sort
void ordenarPorStock(NodoSimple* cabeza) {
    for (NodoSimple* i = cabeza; i != nullptr; i = i->siguiente) {
        NodoSimple* menor = i;
        for (NodoSimple* j = i->siguiente; j != nullptr; j = j->siguiente) {
            if (j->dato.cantidadDisponible < menor->dato.cantidadDisponible) {
                menor = j;
            }
        }
        // Swap
        Producto temp = i->dato;
        i->dato = menor->dato;
        menor->dato = temp;
    }
}
void mostrarAlertas(NodoSimple* cabeza, int limite = 5) {
    cout << "PRODUCTOS CON STOCK BAJO\n" << endl;
    bool hayAlertas = false;
    while (cabeza != nullptr) {
        if (cabeza->dato.cantidadDisponible < limite) {
            cout << " Producto: " << cabeza->dato.codigo << " - Stock: " << cabeza->dato.cantidadDisponible << " - Descripcion: " << cabeza->dato.descripcion << endl;
            hayAlertas = true;
        }
        cabeza = cabeza->siguiente;
    }
    if (!hayAlertas) {
        cout << "No hay productos con stock bajo" << endl;
    }
}
int main() {
    NodoSimple* lista = nullptr;
    Producto p1 = {101, "Shampoo", 12, 5.50f};
    Producto p2 = {205, "Tarros Aceite", 3, 2.20f};
    Producto p3 = {330, "Papel Higienico", 20, 3.10f};
    Producto p4 = {150, "Carton de Leche", 1, 1.30f};
    Producto p5 = {499, "Huevos", 7, 0.90f};
    insertarSimple(lista, p1);
    insertarSimple(lista, p2);
    insertarSimple(lista, p3);
    insertarSimple(lista, p4);
    insertarSimple(lista, p5);
    // Ordenar por stock
    ordenarPorStock(lista);
    // Mostrar inventario ordenado
    mostrarInventario(lista);
    // Mostrar alertas de stock bajo
    mostrarAlertas(lista, 5);
    return 0;
}
