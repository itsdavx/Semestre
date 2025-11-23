#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Estructura de nodo para representar una tarea
struct Nodo {
    int prioridad;
    string descripcion;
    
    Nodo(int p, string d) : prioridad(p), descripcion(d) {}
};

// Clase para gestionar el vector de punteros
class GestorTareas {
private:
    Nodo** tareas;  // Vector de punteros a Nodo
    int capacidad;
    int totalComparaciones;
    int totalIntercambios;
    
    void mostrarNodo(Nodo* nodo, bool conDireccion = false) {
        if (!nodo) {
            cout << "[NULL]";
            return;
        }
        cout << "[P:" << nodo->prioridad << " | " << nodo->descripcion;
        if (conDireccion) {
            cout << " @" << nodo;
        }
        cout << "]";
    }
    
public:
    GestorTareas(int cap) : capacidad(cap), totalComparaciones(0), totalIntercambios(0) {
        tareas = new Nodo*[capacidad];
        // Inicializar todos los punteros a nullptr
        for (int i = 0; i < capacidad; i++) {
            tareas[i] = nullptr;
        }
    }
    
    void agregarTarea(int pos, int prioridad, string descripcion) {
        if (pos >= 0 && pos < capacidad) {
            tareas[pos] = new Nodo(prioridad, descripcion);
        }
    }
    
    void mostrarVector(string titulo = "", bool conDirecciones = false) {
        if (!titulo.empty()) {
            cout << "\n" << titulo << endl;
        }
        
        for (int i = 0; i < capacidad; i++) {
            cout << "  tareas[" << i << "] -> ";
            mostrarNodo(tareas[i], conDirecciones);
            cout << endl;
        }
    }
    
    void mostrarComparacion(int i, int j) {
        cout << "\n    Comparando tareas[" << i << "] con tareas[" << j << "]:" << endl;
        cout << "      tareas[" << i << "] -> Prioridad: " << tareas[i]->prioridad 
             << " (" << tareas[i]->descripcion << ")" << endl;
        cout << "      tareas[" << j << "] -> Prioridad: " << tareas[j]->prioridad 
             << " (" << tareas[j]->descripcion << ")" << endl;
        cout << "      Direcciones de memoria: " << tareas[i] << " vs " << tareas[j] << endl;
    }
    
    void mostrarIntercambio(int i, int j) {
        cout << "\n    [INTERCAMBIO DE PUNTEROS]" << endl;
        cout << "      ANTES:" << endl;
        cout << "        tareas[" << i << "] apunta a: " << tareas[i] 
             << " (P:" << tareas[i]->prioridad << ")" << endl;
        cout << "        tareas[" << j << "] apunta a: " << tareas[j] 
             << " (P:" << tareas[j]->prioridad << ")" << endl;
        
        // Realizar intercambio de punteros
        Nodo* temp = tareas[i];
        tareas[i] = tareas[j];
        tareas[j] = temp;
        
        cout << "      DESPUES:" << endl;
        cout << "        tareas[" << i << "] apunta a: " << tareas[i] 
             << " (P:" << tareas[i]->prioridad << ")" << endl;
        cout << "        tareas[" << j << "] apunta a: " << tareas[j] 
             << " (P:" << tareas[j]->prioridad << ")" << endl;
        cout << "      Nota: Solo se intercambiaron los PUNTEROS (direcciones)" << endl;
        cout << "            Los nodos en memoria NO se movieron" << endl;
    }
    
    void bubbleSort() {
        cout << "\n--- BUBBLE SORT EN VECTOR DE PUNTEROS ---" << endl;
        cout << "    Criterio: Prioridad (menor a mayor)" << endl;
        cout << "    Intercambiando: PUNTEROS (no estructuras completas)" << endl;
        
        cout << "\n[VECTOR INICIAL - DESORDENADO]";
        mostrarVector("", true);
        
        // Tabla de registro
        cout << "\n[TABLA DE REGISTRO POR PASADA]" << endl;
        cout << setw(8) << "Pasada" << " | " 
             << setw(15) << "Comparaciones" << " | "
             << setw(14) << "Intercambios" << " | "
             << setw(20) << "Bytes movidos" << " | "
             << setw(12) << "Estado" << endl;
        cout << string(80, '-') << endl;
        
        bool huboIntercambio = true;
        int pasada = 1;
        int limite = capacidad - 1;
        
        while (huboIntercambio && limite > 0) {
            cout << "\n\n--- PASADA " << pasada << " ---" << endl;
            cout << "Comparando elementos desde [0] hasta [" << limite << "]" << endl;
            
            huboIntercambio = false;
            int comparacionesPasada = 0;
            int intercambiosPasada = 0;
            
            for (int i = 0; i < limite; i++) {
                cout << "\n  Comparacion #" << (comparacionesPasada + 1) << ":" << endl;
                mostrarComparacion(i, i + 1);
                
                comparacionesPasada++;
                totalComparaciones++;
                
                // Comparar por prioridad (accediendo a traves de punteros)
                cout << "      Evaluando: " << tareas[i]->prioridad 
                     << " > " << tareas[i+1]->prioridad << " ?";
                
                if (tareas[i]->prioridad > tareas[i+1]->prioridad) {
                    cout << " => SI, intercambiar" << endl;
                    
                    mostrarIntercambio(i, i + 1);
                    
                    intercambiosPasada++;
                    totalIntercambios++;
                    huboIntercambio = true;
                } else {
                    cout << " => NO, mantener orden" << endl;
                    cout << "      No se requiere intercambio" << endl;
                }
            }
            
            // Calcular bytes movidos (solo punteros, no estructuras completas)
            int bytesMovidos = intercambiosPasada * sizeof(Nodo*) * 3;  // temp, asignacion1, asignacion2
            
            string estado = huboIntercambio ? "Continuar" : "DETENIDO";
            cout << "\n";
            cout << setw(8) << pasada << " | " 
                 << setw(15) << comparacionesPasada << " | "
                 << setw(14) << intercambiosPasada << " | "
                 << setw(20) << bytesMovidos << " | "
                 << setw(12) << estado << endl;
            
            if (!huboIntercambio) {
                cout << "\n*** OPTIMIZACION: Pasada sin intercambios detectada ***" << endl;
                cout << "El vector ya esta ordenado. Deteniendo algoritmo." << endl;
            }
            
            cout << "\n[ESTADO DEL VECTOR DESPUES DE LA PASADA " << pasada << "]";
            mostrarVector();
            
            limite--;
            pasada++;
        }
    }
    
    void mostrarAnalisisFinal() {
        cout << "\n\n--- ANALISIS FINAL ---" << endl;
        
        cout << "\n[VECTOR FINAL ORDENADO]";
        mostrarVector("", true);
        
        cout << "\n[VERIFICACION DEL ORDENAMIENTO]:" << endl;
        cout << "Tareas ordenadas por prioridad (menor a mayor):" << endl;
        for (int i = 0; i < capacidad; i++) {
            cout << "  " << (i + 1) << ". Prioridad " << tareas[i]->prioridad 
                 << ": " << tareas[i]->descripcion << endl;
        }
        
        cout << "\n[ESTADISTICAS TOTALES]:" << endl;
        cout << "  * Total de comparaciones: " << totalComparaciones << endl;
        cout << "  * Total de intercambios: " << totalIntercambios << endl;
        cout << "  * Numero de tareas: " << capacidad << endl;
        
        // Analisis de bytes movidos
        int bytesMovidosPunteros = totalIntercambios * sizeof(Nodo*) * 3;
        int bytesMovidosEstructuras = totalIntercambios * sizeof(Nodo) * 3;
        
        cout << "\n[ANALISIS DE MOVIMIENTO DE DATOS]:" << endl;
        cout << "\nIntercambiando PUNTEROS (metodo usado):" << endl;
        cout << "  - Tamano de un puntero: " << sizeof(Nodo*) << " bytes" << endl;
        cout << "  - Operaciones por intercambio: 3 (temp, asig1, asig2)" << endl;
        cout << "  - Total de bytes movidos: " << bytesMovidosPunteros << " bytes" << endl;
        
        cout << "\nSi intercambiaramos ESTRUCTURAS COMPLETAS:" << endl;
        cout << "  - Tamano de estructura Nodo: " << sizeof(Nodo) << " bytes" << endl;
        cout << "  - Operaciones por intercambio: 3 (temp, asig1, asig2)" << endl;
        cout << "  - Total de bytes movidos: " << bytesMovidosEstructuras << " bytes" << endl;
        
        cout << "\n[COMPARACION]:" << endl;
        cout << "  Bytes ahorrados: " << (bytesMovidosEstructuras - bytesMovidosPunteros) << " bytes" << endl;
        if (bytesMovidosEstructuras > 0) {
            cout << "  Factor de reduccion: " << fixed << setprecision(2)
                 << (static_cast<double>(bytesMovidosEstructuras) / bytesMovidosPunteros) << "x" << endl;
            cout << "  Porcentaje de reduccion: " << fixed << setprecision(1)
                 << (100.0 * (bytesMovidosEstructuras - bytesMovidosPunteros) / bytesMovidosEstructuras) << "%" << endl;
        }
    }
    
    ~GestorTareas() {
        // Liberar memoria de los nodos
        for (int i = 0; i < capacidad; i++) {
            if (tareas[i] != nullptr) {
                delete tareas[i];
            }
        }
        // Liberar el vector de punteros
        delete[] tareas;
    }
};

int main() {
    cout << "--- BUBBLE SORT EN VECTOR DE PUNTEROS ---" << endl;
    cout << "    Ordenamiento de tareas por prioridad" << endl;
    cout << "    Intercambiando punteros, NO estructuras completas" << endl;
    
    // Crear gestor con 6 tareas
    GestorTareas gestor(6);
    
    cout << "\n[CONSTRUCCION DEL VECTOR DE PUNTEROS A NODOS]" << endl;
    cout << "Creando nodos en memoria dinamica y guardando sus direcciones..." << endl;
    
    // Agregar tareas con diferentes prioridades
    gestor.agregarTarea(0, 5, "Revisar correos");
    gestor.agregarTarea(1, 2, "Reunion urgente con cliente");
    gestor.agregarTarea(2, 8, "Organizar escritorio");
    gestor.agregarTarea(3, 1, "Llamada emergencia");
    gestor.agregarTarea(4, 6, "Actualizar documentacion");
    gestor.agregarTarea(5, 3, "Preparar presentacion");
    
    // Aplicar Bubble Sort
    gestor.bubbleSort();
    
    // Mostrar analisis final
    gestor.mostrarAnalisisFinal();
    
    return 0;
}