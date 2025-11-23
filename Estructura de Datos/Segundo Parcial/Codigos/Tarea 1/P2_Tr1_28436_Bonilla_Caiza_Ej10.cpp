#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura del nodo para procesos
struct Proceso {
    int pid;
    int tiempo_cpu;
    int prioridad;
    Proceso* anterior;
    Proceso* siguiente;
    
    Proceso(int id, int tiempo, int prio) 
        : pid(id), tiempo_cpu(tiempo), prioridad(prio), anterior(nullptr), siguiente(nullptr) {}
    
    void mostrar() const {
        cout << "PID: " << pid << " | CPU: " << tiempo_cpu << "ms | Prioridad: " << prioridad;
    }
};

class ListaCircularQuicksort {
private:
    Proceso* cabeza;
    int llamadasRecursivas;
    
public:
    ListaCircularQuicksort() : cabeza(nullptr), llamadasRecursivas(0) {}
    
    // Insertar proceso al final
    void insertar(int pid, int tiempo_cpu, int prioridad) {
        Proceso* nuevo = new Proceso(pid, tiempo_cpu, prioridad);
        
        if (!cabeza) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            Proceso* ultimo = cabeza->anterior;
            
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
    }
    
    // Mostrar lista completa
    void mostrarLista(const string& mensaje = "") {
        if (!cabeza) {
            cout << "Lista vacía" << endl;
            return;
        }
        
        if (!mensaje.empty()) {
            cout << mensaje << endl;
        }
        
        Proceso* actual = cabeza;
        int contador = 0;
        
        do {
            cout << "[" << contador << "] ";
            actual->mostrar();
            cout << " | Ant: " << (actual->anterior ? actual->anterior->pid : -1)
                 << " | Sig: " << (actual->siguiente ? actual->siguiente->pid : -1) << endl;
            actual = actual->siguiente;
            contador++;
        } while (actual != cabeza);
        
        cout << "--- Fin de lista ---" << endl;
    }
    
    // Función para obtener el último nodo de un segmento
    Proceso* obtenerUltimo(Proceso* primera) {
        if (!primera) return nullptr;
        
        Proceso* actual = primera;
        while (actual->siguiente && actual->siguiente != primera) {
            actual = actual->siguiente;
        }
        return actual;
    }
    
    // Partición para lista doblemente enlazada
    Proceso* particion(Proceso* primero, Proceso* ultimo, int& comparaciones, int& intercambios) {
        cout << "\n--- PARTICION DESDE ";
        primero->mostrar();
        cout << " HASTA ";
        ultimo->mostrar();
        cout << " ---" << endl;
        
        // Seleccionar pivote (último elemento)
        Proceso* pivote = ultimo;
        cout << "Pivote seleccionado: ";
        pivote->mostrar();
        cout << endl;
        
        Proceso* i = primero->anterior;  // Simula i = low - 1
        Proceso* j = primero;            // Simula j = low
        
        cout << "Inicialización:" << endl;
        cout << "  i: " << (i ? to_string(i->pid) : "NULL") << endl;
        cout << "  j: ";
        j->mostrar();
        cout << endl;
        
        // Avanzar j desde primero hasta último-1
        while (j != ultimo) {
            comparaciones++;
            cout << "Comparando j (";
            j->mostrar();
            cout << ") <= pivote (";
            pivote->mostrar();
            cout << ")? ";
            
            // Comparar por prioridad (podría ser cualquier campo)
            if (j->prioridad <= pivote->prioridad) {
                cout << "SÍ" << endl;
                
                // Mover i al siguiente nodo
                i = (i == primero->anterior) ? primero : i->siguiente;
                
                cout << "  Avanzando i a: ";
                i->mostrar();
                cout << endl;
                
                if (i != j) {
                    cout << "  INTERCAMBIO: i (";
                    i->mostrar();
                    cout << ") <-> j (";
                    j->mostrar();
                    cout << ")" << endl;
                    
                    intercambiarNodos(i, j);
                    intercambios++;
                    
                    // Mostrar estado después del intercambio
                    cout << "  Después del intercambio:" << endl;
                    cout << "    i: ";
                    i->mostrar();
                    cout << " | j: ";
                    j->mostrar();
                    cout << endl;
                }
            } else {
                cout << "NO" << endl;
            }
            
            j = j->siguiente;
            if (j != ultimo) {
                cout << "  Avanzando j a: ";
                j->mostrar();
                cout << endl;
            }
        }
        
        // Colocar pivote en posición correcta
        i = (i == primero->anterior) ? primero : i->siguiente;
        cout << "Colocando pivote - i final: ";
        i->mostrar();
        cout << endl;
        
        if (i != ultimo) {
            cout << "INTERCAMBIO FINAL: i (";
            i->mostrar();
            cout << ") <-> pivote (";
            ultimo->mostrar();
            cout << ")" << endl;
            intercambiarNodos(i, ultimo);
            intercambios++;
        }
        
        cout << "Partición completada. Pivote en posición con PID: " << i->pid << endl;
        return i;
    }
    
    // Intercambiar dos nodos (modificando enlaces)
    void intercambiarNodos(Proceso* a, Proceso* b) {
        if (a == b) return;
        
        // Caso especial: nodos adyacentes
        if (a->siguiente == b) {
            // a y b son adyacentes, a antes que b
            Proceso* a_ant = a->anterior;
            Proceso* b_sig = b->siguiente;
            
            a_ant->siguiente = b;
            b->anterior = a_ant;
            b->siguiente = a;
            a->anterior = b;
            a->siguiente = b_sig;
            b_sig->anterior = a;
        } else if (b->siguiente == a) {
            // b y a son adyacentes, b antes que a
            intercambiarNodos(b, a);
        } else {
            // Nodos no adyacentes
            Proceso* a_ant = a->anterior;
            Proceso* a_sig = a->siguiente;
            Proceso* b_ant = b->anterior;
            Proceso* b_sig = b->siguiente;
            
            a_ant->siguiente = b;
            a_sig->anterior = b;
            b_ant->siguiente = a;
            b_sig->anterior = a;
            
            a->anterior = b_ant;
            a->siguiente = b_sig;
            b->anterior = a_ant;
            b->siguiente = a_sig;
        }
        
        // Actualizar cabeza si es necesario
        if (cabeza == a) cabeza = b;
        else if (cabeza == b) cabeza = a;
    }
    
    // Quicksort recursivo para lista doblemente enlazada
    void quicksort(Proceso* primero, Proceso* ultimo, int nivel = 0) {
        llamadasRecursivas++;
        
        string indent(nivel * 2, ' ');
        cout << indent << "└─ Quicksort(nivel " << nivel << "): ";
        cout << "Desde ";
        primero->mostrar();
        cout << " hasta ";
        ultimo->mostrar();
        cout << endl;
        
        // Mostrar segmento actual
        cout << indent << "  Segmento: ";
        Proceso* actual = primero;
        do {
            cout << actual->pid;
            if (actual != ultimo) cout << " → ";
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
        cout << endl;
        
        if (primero != ultimo && primero && ultimo && primero != ultimo->siguiente) {
            int comparaciones = 0, intercambios = 0;
            Proceso* pivote = particion(primero, ultimo, comparaciones, intercambios);
            
            // Mostrar después de partición
            cout << indent << "  Después de partición:" << endl;
            cout << indent << "  Izquierda: ";
            if (primero != pivote) {
                actual = primero;
                while (actual != pivote) {
                    cout << actual->pid << " ";
                    actual = actual->siguiente;
                }
            } else {
                cout << "vacío";
            }
            cout << endl;
            
            cout << indent << "  Pivote: " << pivote->pid << endl;
            cout << indent << "  Derecha: ";
            if (pivote->siguiente != ultimo->siguiente) {
                actual = pivote->siguiente;
                while (actual != ultimo->siguiente) {
                    cout << actual->pid << " ";
                    actual = actual->siguiente;
                }
            } else {
                cout << "vacío";
            }
            cout << endl;
            
            // Llamadas recursivas
            if (primero != pivote) {
                quicksort(primero, pivote->anterior, nivel + 1);
            }
            if (pivote != ultimo) {
                quicksort(pivote->siguiente, ultimo, nivel + 1);
            }
        } else {
            cout << indent << "  ✓ Caso base alcanzado" << endl;
        }
    }
    
    // Wrapper público para ordenar
    void ordenar() {
        if (!cabeza) {
            cout << "Lista vacía - nada que ordenar" << endl;
            return;
        }
        
        cout << "=== QUICKSORT EN LISTA DOBLEMENTE ENLAZADA CIRCULAR ===" << endl;
        cout << "Lista inicial:" << endl;
        mostrarLista();
        
        Proceso* ultimo = cabeza->anterior;
        llamadasRecursivas = 0;
        
        quicksort(cabeza, ultimo);
        
        cout << "\n=== ORDENAMIENTO COMPLETADO ===" << endl;
        cout << "Total llamadas recursivas: " << llamadasRecursivas << endl;
        cout << "Lista ordenada:" << endl;
        mostrarLista();
    }
    
    // Destructor
    ~ListaCircularQuicksort() {
        if (!cabeza) return;
        
        Proceso* actual = cabeza;
        Proceso* siguiente;
        
        do {
            siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
};

// Función para demostración
void demostrarQuicksortLista() {
    ListaCircularQuicksort lista;
    
    // Insertar procesos de prueba
    lista.insertar(101, 150, 3);
    lista.insertar(102, 200, 1);
    lista.insertar(103, 100, 5);
    lista.insertar(104, 300, 2);
    lista.insertar(105, 250, 4);
    lista.insertar(106, 180, 3);
    lista.insertar(107, 220, 1);
    
    lista.ordenar();
}

int main() {
    srand(time(0));
    
    cout << "QUICKSORT EN LISTA DOBLEMENTE ENLAZADA CIRCULAR" << endl;
    
    demostrarQuicksortLista();
    
    return 0;
}