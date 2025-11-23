#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// Estructura del nodo
struct Nodo {
    int id;
    string nombre;
    Nodo* next;
    Nodo(int _id, string _nombre) : id(_id), nombre(_nombre), next(nullptr) {}
};
// Clase para manejar la lista enlazada
class ListaEnlazada {
private:
    Nodo* cabeza;
    int totalComparaciones;
    int totalMovimientos;
    void mostrarNodo(Nodo* nodo) {
        if (nodo) {
            cout << "[ID: " << nodo->id << ", Nombre: " << nodo->nombre << "]";
        } else {
            cout << "[NULL]";
        }
    }
public:
    ListaEnlazada() : cabeza(nullptr), totalComparaciones(0), totalMovimientos(0) {}
    // Insertar al final (para construcción inicial)
    void insertarAlFinal(int id, string nombre) {
        Nodo* nuevo = new Nodo(id, nombre);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo* temp = cabeza;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nuevo;
        }
    }
    // Mostrar la lista completa
    void mostrar() {
        if (!cabeza) {
            cout << "Lista vacía" << endl;
            return;
        }
        Nodo* temp = cabeza;
        cout << "Lista: ";
        while (temp) {
            cout << "[ID:" << temp->id << " " << temp->nombre << "]";
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
    // Insertion Sort con análisis detallado
    void insertionSort() {
        if (!cabeza || !cabeza->next) {
            cout << "\n=== Lista con 0 o 1 elementos, ya está ordenada ===" << endl;
            return;
        }
        cout << "------------INSERTION SORT EN LISTA ENLAZADA------------" << endl;
        cout << "\nLista inicial: ";
        mostrar();
        cout << endl;
        // ordenada apunta al último nodo de la parte ordenada
        Nodo* ordenada = cabeza;
        // actual es el nodo que vamos a insertar (nodo clave)
        Nodo* actual = cabeza->next;
        int iteracion = 1;
        while (actual) {
            cout << "-------------------------------------------------------------" << endl;
            cout << " ITERACION " << iteracion << endl;
            cout << "-------------------------------------------------------------" << endl;
            // Guardar el nodo clave
            Nodo* clave = actual;
            cout << "> Nodo CLAVE seleccionado: ";
            mostrarNodo(clave);
            cout << endl;
            // Avanzar actual al siguiente nodo
            actual = actual->next;
            int comparacionesIteracion = 0;
            int movimientosIteracion = 0;
            // Caso 1: El nodo clave debe ir al inicio
            if (clave->id < cabeza->id) {
                cout << "\n  > Comparacion 1: " << clave->id << " < " << cabeza->id 
                     << " (clave < cabeza)" << endl;
                comparacionesIteracion++;
                totalComparaciones++;
                cout << "  > Decision: Insertar al INICIO de la lista" << endl;
                // Desconectar clave de su posicion actual
                ordenada->next = clave->next;
                cout << "  > Movimiento 1: ordenada->next = clave->next" << endl;
                movimientosIteracion++;
                totalMovimientos++;
                // Insertar al inicio
                clave->next = cabeza;
                cout << "  > Movimiento 2: clave->next = cabeza" << endl;
                movimientosIteracion++;
                totalMovimientos++;
                cabeza = clave;
                cout << "  > Movimiento 3: cabeza = clave" << endl;
                movimientosIteracion++;
                totalMovimientos++;
            } else {
                // Caso 2: Buscar posicion en la sublista ordenada
                Nodo* previo = cabeza;
                Nodo* siguiente = cabeza->next;
                bool insertado = false;
                cout << "\n  > Buscando posicion en sublista ordenada..." << endl;
                while (siguiente != clave) {
                    comparacionesIteracion++;
                    totalComparaciones++;
                    cout << "  > Comparacion " << comparacionesIteracion << ": " 
                         << clave->id << " vs " << siguiente->id;
                    if (clave->id < siguiente->id) {
                        cout << " -> clave MENOR, insertar aqui" << endl;
                        // Insertar entre previo y siguiente
                        ordenada->next = clave->next;
                        cout << "  > Movimiento 1: ordenada->next = clave->next" << endl;
                        movimientosIteracion++;
                        totalMovimientos++;
                        previo->next = clave;
                        cout << "  > Movimiento 2: previo->next = clave" << endl;
                        movimientosIteracion++;
                        totalMovimientos++;
                        clave->next = siguiente;
                        cout << "  > Movimiento 3: clave->next = siguiente" << endl;
                        movimientosIteracion++;
                        totalMovimientos++;
                        insertado = true;
                        break;
                    } else {
                        cout << " -> clave MAYOR, continuar" << endl;
                    }
                    previo = siguiente;
                    siguiente = siguiente->next;
                }
                // Caso 3: El nodo ya esta en su posicion correcta
                if (!insertado) {
                    cout << "  > El nodo clave ya esta en posicion correcta" << endl;
                    ordenada = clave;
                }
            }
            cout << "\n  * Comparaciones en esta iteracion: " << comparacionesIteracion << endl;
            cout << "  * Movimientos de punteros: " << movimientosIteracion << endl;
            cout << "\n  Estado actual de la lista: ";
            mostrar();
            cout << endl;
            iteracion++;
        }
        
    }
    void mostrarAnalisisFinal() {
        cout << "\n[AnalisisFinal]:" << endl;
        cout << "   * Total de comparaciones realizadas: " << totalComparaciones << endl;
        cout << "   * Total de movimientos de punteros: " << totalMovimientos << endl;
    }
    // Destructor
        ~ListaEnlazada() {
            while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->next;
            delete temp;
        }
    }
};
int main() {
    ListaEnlazada lista;
    cout << "-----------INSERTION SORT EN LISTA ENLAZADA SIMPLE----------" << endl;
    // Construccion de la lista con datos desordenados
    cout << "\nConstruyendo lista enlazada dinamica..." << endl;
    lista.insertarAlFinal(45, "Maria");
    lista.insertarAlFinal(12, "Carlos");
    lista.insertarAlFinal(78, "Ana");
    lista.insertarAlFinal(23, "Pedro");
    lista.insertarAlFinal(56, "Laura");
    lista.insertarAlFinal(8, "Jose");
    cout << "\nLista construida exitosamente" << endl;
    cout << "\nLista original (desordenada):" << endl;
    lista.mostrar();
    // Aplicar Insertion Sort
    lista.insertionSort();
    // Mostrar resultado final
    cout << "\n[LISTA FINAL ORDENADA]:" << endl;
    lista.mostrar();
    // Mostrar analisis completo
    lista.mostrarAnalisisFinal();
    return 0;
}