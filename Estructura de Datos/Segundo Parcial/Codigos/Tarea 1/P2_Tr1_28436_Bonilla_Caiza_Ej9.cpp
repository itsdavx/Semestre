#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <queue>

using namespace std;

// Estructura del nodo (representa productos)
struct Producto {
    int codigo;
    string nombre;
    double precio;
    string categoria;
    
    Producto(int c, string n, double p, string cat) 
        : codigo(c), nombre(n), precio(p), categoria(cat) {}
    
    void mostrar() const {
        cout << "Cód: " << codigo << " | " << nombre << " | $" 
             << fixed << setprecision(2) << precio << " | " << categoria;
    }
};

class QuickSortArbol {
private:
    vector<Producto> productos;
    int nivelRecursion;
    int particiones;
    int llamadasRecursivas;
    
public:
    QuickSortArbol(vector<Producto> p) : productos(p), nivelRecursion(0), particiones(0), llamadasRecursivas(0) {}
    
    // Función para intercambiar productos
    void intercambiar(int i, int j) {
        cout << "  Intercambiando: ";
        productos[i].mostrar();
        cout << " <-> ";
        productos[j].mostrar();
        cout << endl;
        
        swap(productos[i], productos[j]);
    }
    
    // Función de partición con pivote aleatorio
    int particion(int low, int high) {
        particiones++;
        cout << "\n--- PARTICION [" << low << ", " << high << "] ---" << endl;
        
        // Selección aleatoria del pivote
        int randomIndex = low + rand() % (high - low + 1);
        Producto pivote = productos[randomIndex];
        
        cout << "Pivote seleccionado (índice " << randomIndex << "): ";
        pivote.mostrar();
        cout << endl;
        
        // Mover pivote al final temporalmente
        intercambiar(randomIndex, high);
        
        int i = low - 1;
        cout << "Índice i inicial: " << i << endl;
        cout << "Recorriendo desde " << low << " hasta " << high - 1 << endl;
        
        for (int j = low; j < high; j++) {
            cout << "  j=" << j << " | Comparando: ";
            productos[j].mostrar();
            cout << " <= pivote? ";
            
            // Comparar por código (podría ser cualquier campo)
            if (productos[j].codigo <= pivote.codigo) {
                cout << "SÍ" << endl;
                i++;
                if (i != j) {
                    cout << "  i=" << i << " | ";
                    intercambiar(i, j);
                }
            } else {
                cout << "NO" << endl;
            }
        }
        
        // Colocar pivote en su posición correcta
        intercambiar(i + 1, high);
        
        cout << "Partición completada. Pivote en posición: " << (i + 1) << endl;
        cout << "Subarreglo izquierdo: [" << low << ", " << i << "]" << endl;
        cout << "Subarreglo derecho: [" << (i + 2) << ", " << high << "]" << endl;
        
        return i + 1;
    }
    
    // Implementación recursiva de Quicksort
    void quicksort(int low, int high) {
        llamadasRecursivas++;
        int nivelActual = nivelRecursion++;
        
        cout << string(nivelActual * 2, ' ') << "└─ Quicksort([" << low << ", " << high << "]) - Nivel " << nivelActual << endl;
        
        if (low < high) {
            // Mostrar subarreglo actual
            cout << string(nivelActual * 2, ' ') << "  Subarreglo: ";
            for (int i = low; i <= high; i++) {
                cout << productos[i].codigo;
                if (i < high) cout << ", ";
            }
            cout << endl;
            
            int pi = particion(low, high);
            
            // Mostrar estado después de partición
            cout << string(nivelActual * 2, ' ') << "  Después de partición: ";
            for (int i = low; i <= high; i++) {
                if (i == pi) cout << "[" << productos[i].codigo << "] ";
                else cout << productos[i].codigo << " ";
            }
            cout << endl;
            
            // Llamadas recursivas
            quicksort(low, pi - 1);
            nivelRecursion--;
            quicksort(pi + 1, high);
            nivelRecursion--;
        } else {
            cout << string(nivelActual * 2, ' ') << "  Caso base - subarreglo de tamaño 0 o 1" << endl;
        }
    }
    
    // Wrapper público
    void ordenar() {
        cout << "=== QUICKSORT CON PIVOTE ALEATORIO ===" << endl;
        cout << "Vector inicial (in-order del árbol):" << endl;
        mostrarVector();
        cout << endl;
        
        srand(time(0)); // Semilla para aleatoriedad
        quicksort(0, productos.size() - 1);
        
        cout << "\n=== ORDENAMIENTO COMPLETADO ===" << endl;
        cout << "Vector ordenado:" << endl;
        mostrarVector();
    }
    
    // Mostrar el vector completo
    void mostrarVector() {
        for (size_t i = 0; i < productos.size(); i++) {
            cout << "[" << i << "] ";
            productos[i].mostrar();
            cout << endl;
        }
    }
    
    // Dibujar árbol de recursión
    void dibujarArbolRecursion() {
        cout << "\n=== ÁRBOL DE RECURSIÓN ===" << endl;
        cout << "Se generaron " << llamadasRecursivas << " llamadas recursivas" << endl;
        cout << "Se realizaron " << particiones << " particiones" << endl;
        cout << "\nEstructura del árbol:" << endl;
        cout << "Quicksort([0, " << (productos.size()-1) << "])" << endl;
        cout << "├─ Particiones sucesivas hasta casos base" << endl;
        cout << "└─ Cada nodo representa una llamada recursiva" << endl;
        
        // Simular árbol de recursión
        cout << "\nRepresentación simplificada:" << endl;
        simularArbolRecursion(0, productos.size()-1, 0);
    }
    
    void simularArbolRecursion(int low, int high, int nivel) {
        if (low > high) return;
        
        string indent(nivel * 4, ' ');
        cout << indent << "Nivel " << nivel << ": [" << low << ", " << high << "]";
        
        if (low < high) {
            cout << " → Partición" << endl;
            // Simular posición del pivote (mitad para la visualización)
            int mid = low + (high - low) / 2;
            simularArbolRecursion(low, mid-1, nivel+1);
            simularArbolRecursion(mid+1, high, nivel+1);
        } else {
            cout << " → Caso base" << endl;
        }
    }
    
    
    // Getter para obtener el vector ordenado
    vector<Producto> getProductosOrdenados() const {
        return productos;
    }
};

// Función para crear datos de prueba (simulando in-order de un árbol)
vector<Producto> crearDatosArbol() {
    return {
        Producto(50, "Tablet", 299.99, "Electrónicos"),
        Producto(20, "Mouse", 25.50, "Computación"),
        Producto(70, "Monitor", 199.99, "Computación"),
        Producto(10, "Teclado", 45.99, "Computación"),
        Producto(30, "Smartphone", 599.99, "Electrónicos"),
        Producto(60, "Laptop", 899.99, "Computación"),
        Producto(80, "Impresora", 149.99, "Oficina"),
        Producto(40, "Tablet", 399.99, "Electrónicos"),
        Producto(90, "Escáner", 79.99, "Oficina")
    };
}

// Función para demostrar diferentes ejecuciones
void demostrarQuicksortAleatorio() {
    cout << "QUICKSORT SOBRE VECTOR DE ÁRBOL (IN-ORDER)" << endl;
    cout << "===========================================" << endl;
    
    vector<Producto> productos = crearDatosArbol();
    QuickSortArbol sorter(productos);
    
    sorter.ordenar();
    sorter.dibujarArbolRecursion();
    
    // Demostrar múltiples ejecuciones con diferentes semillas
    cout << "\n\n=== DEMOSTRACIÓN DE ALEATORIEDAD ===" << endl;
    cout << "Ejecutando con diferentes semillas aleatorias..." << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << "\n--- Ejecución " << (i + 1) << " ---" << endl;
        vector<Producto> productosCopy = crearDatosArbol();
        QuickSortArbol sorterTemp(productosCopy);
        
        // Usar semilla diferente para cada ejecución
        srand(time(0) + i);
        sorterTemp.quicksort(0, productosCopy.size() - 1);
    }
}

int main() {
    demostrarQuicksortAleatorio();
    return 0;
}