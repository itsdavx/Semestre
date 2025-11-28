#include <iostream>
using namespace std;

class NodoSimple {
public:
    int dato;
    NodoSimple* siguiente;
    
    NodoSimple(int valor) { dato = valor; siguiente = nullptr;}
};

class ListaEnlazada {
private:
    NodoSimple* cabeza;

public:
    ListaEnlazada() { cabeza = nullptr; }

    // Funcion para insertar al final
    void insertarFinal(int valor) {
        NodoSimple* nuevo = new NodoSimple(valor);
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            NodoSimple* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    // Método para mostrar la lista
    void mostrar() const {
        cout << "Lista Simple-Enlazada: ";
        NodoSimple* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente != nullptr)
                cout << " -> ";
            actual = actual->siguiente;
        }
        cout << " -> Null\n";
    }

    // Método para aplicar Insertion Sort
    void insertionSort() {
        if (cabeza == nullptr || cabeza->siguiente == nullptr)
            return;
        
        NodoSimple* listaOrdenada = nullptr;
        
        while (cabeza != nullptr) {
            // Tomar el primer nodo de la lista original
            NodoSimple* actual = cabeza;
            cabeza = cabeza->siguiente;
            actual->siguiente = nullptr;
            
            // Insertar el nodo en la posición correcta en la lista ordenada
            if (listaOrdenada == nullptr || actual->dato <= listaOrdenada->dato) {
                // Insertar al principio
                actual->siguiente = listaOrdenada;
                listaOrdenada = actual;
            } else {
                // Buscar la posición correcta para insertar
                NodoSimple* temp = listaOrdenada;
                while (temp->siguiente != nullptr && temp->siguiente->dato < actual->dato) {
                    temp = temp->siguiente;
                }
                // Insertar después de temp
                actual->siguiente = temp->siguiente;
                temp->siguiente = actual;
            }
        }
        
        cabeza = listaOrdenada;
    }
};

int main() {
    ListaEnlazada lista;
    
    // Insertar elementos en la lista
    lista.insertarFinal(42);
    lista.insertarFinal(17);
    lista.insertarFinal(89);
    lista.insertarFinal(53);
    lista.insertarFinal(71);
    lista.insertarFinal(32);
    lista.insertarFinal(65);
    lista.insertarFinal(80);
    lista.insertarFinal(15);
    lista.insertarFinal(72);
    lista.insertarFinal(34);
    lista.insertarFinal(78);
    lista.insertarFinal(132);
    lista.insertarFinal(125);
    lista.insertarFinal(4163);
    
    // Mostrar lista antes del ordenamiento
    cout << "\nANTES del ordenamiento:\n";
    lista.mostrar();
    cout << endl;
    
    // Aplicar Insertion Sort
    lista.insertionSort();
    
    // Mostrar lista después del ordenamiento
    cout << "\nDESPUES del ordenamiento:\n";
    lista.mostrar();
    cout << endl;
    
    return 0;
}

/*

Preguntas del Taller:

1. ¿Por qué Insertion Sort funciona de manera tan natural en listas enlazadas?
    Las listas enlazadas permiten insertar elementos en cualquier posicion lo que deja reorganizar los nodos
    solo ajustando los punteros haciendolo mas eficiente.

2. ¿Cuál es la diferencia entre desplazar elementos en un vector y mover nodos mediante punteros?
    Los vectores realizan desplazamiento fisico, copiando los datos y moviendolos en memoria contigua, 
    mientras que las listas solo ajustan los punteros y dejan los datos en su lugar, haciendo que sean 
    menos costosos en cuanto a procesamiento.

3. ¿En qué casos reales el uso de una estructura dinámica puede resultar más eficiente que la manipulación de memoria contigua?
    La estructuras dinamicas son mas eficientes en sistemas que necesitas insertar o eliminar con frecuencia, o donde los datos 
    son variables, o simplemente estructuras grandes que son muy dificiles de organizar.

*/