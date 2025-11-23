#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para la dirección
struct Direccion {
    string calle;
    int numero;
    string ciudad;
    
    Direccion(string c, int n, string ci) : calle(c), numero(n), ciudad(ci) {}
};

// Estructura para la persona
struct Persona {
    int id;
    string nombre;
    int edad;
    Direccion direccion;
    
    Persona(int i, string n, int e, Direccion d) 
        : id(i), nombre(n), edad(e), direccion(d) {}
};

class ExchangeSortPersonas {
private:
    vector<Persona> personas;
    int comparaciones;
    int intercambios;
    
public:
    ExchangeSortPersonas(vector<Persona> p) : personas(p), comparaciones(0), intercambios(0) {}
    
    // Función de comparación lexicográfica con 3 niveles
    bool compararPersonas(const Persona& a, const Persona& b) {
        comparaciones++;
        
        // 1er nivel: Ciudad
        if (a.direccion.ciudad != b.direccion.ciudad) {
            return a.direccion.ciudad > b.direccion.ciudad;
        }
        
        // 2do nivel: Edad (si las ciudades son iguales)
        if (a.edad != b.edad) {
            return a.edad > b.edad;
        }
        
        // 3er nivel: Nombre (si ciudad y edad son iguales)
        return a.nombre > b.nombre;
    }
    
    // Implementación de Exchange Sort (Bubble Sort mejorado)
    void ordenar() {
        int n = personas.size();
        bool intercambiado;
        
        cout << "=== INICIO DEL ORDENAMIENTO ===" << endl;
        
        for (int i = 0; i < n - 1; i++) {
            intercambiado = false;
            cout << "\n--- Pasada " << (i + 1) << " ---" << endl;
            
            for (int j = 0; j < n - i - 1; j++) {
                cout << "Comparando: " << personas[j].nombre << " vs " << personas[j + 1].nombre << endl;
                cout << "  Ciudad: " << personas[j].direccion.ciudad << " vs " << personas[j + 1].direccion.ciudad;
                cout << " | Edad: " << personas[j].edad << " vs " << personas[j + 1].edad << endl;
                
                if (compararPersonas(personas[j], personas[j + 1])) {
                    // Intercambiar elementos
                    cout << "  ✓ INTERCAMBIO necesario" << endl;
                    swap(personas[j], personas[j + 1]);
                    intercambios++;
                    intercambiado = true;
                    
                    cout << "  Intercambiado: " << personas[j].nombre << " <-> " << personas[j + 1].nombre << endl;
                } else {
                    cout << "  ✗ No se intercambia" << endl;
                }
            }
            
            // Si no hubo intercambios en la pasada, el arreglo ya está ordenado
            if (!intercambiado) {
                cout << "  No hubo intercambios en esta pasada. Ordenamiento completado." << endl;
                break;
            }
        }
        
        cout << "\n=== FIN DEL ORDENAMIENTO ===" << endl;
    }
    
    // Mostrar estadísticas
    void mostrarEstadisticas() {
        cout << "\n=== ESTADÍSTICAS DEL ORDENAMIENTO ===" << endl;
        cout << "Total de comparaciones: " << comparaciones << endl;
        cout << "Total de intercambios: " << intercambios << endl;
        cout << "Número de elementos: " << personas.size() << endl;
        
        // Calcular costo aproximado en memoria por movimiento
        size_t tamanoRegistro = sizeof(Persona) + 
                               sizeof(string) * 3 +  // nombre, calle, ciudad
                               50; // estimación para strings
        
        cout << "Costo total en memoria por intercambios: " 
             << (intercambios * tamanoRegistro) << " bytes" << endl;
        cout << "Costo promedio por intercambio: " << tamanoRegistro << " bytes" << endl;
    }
    
    // Mostrar el arreglo ordenado
    void mostrarArregloOrdenado() {
        cout << "\n=== ARREGLO ORDENADO ===" << endl;
        for (const auto& persona : personas) {
            cout << "ID: " << persona.id 
                 << " | Nombre: " << persona.nombre 
                 << " | Edad: " << persona.edad
                 << " | Ciudad: " << persona.direccion.ciudad
                 << " | Calle: " << persona.direccion.calle 
                 << " " << persona.direccion.numero << endl;
        }
    }
    
    // Getter para acceder a las estadísticas
    int getComparaciones() const { return comparaciones; }
    int getIntercambios() const { return intercambios; }
};

// Función para demostración
void demostracionCompleta() {
    // Crear datos de prueba
    vector<Persona> personas = {
        Persona(1, "Ana", 25, Direccion("Av Principal", 123, "Lima")),
        Persona(2, "Carlos", 30, Direccion("Calle Secundaria", 456, "Arequipa")),
        Persona(3, "Beatriz", 25, Direccion("Av Principal", 123, "Lima")),
        Persona(4, "David", 35, Direccion("Jr Los Olivos", 789, "Lima")),
        Persona(5, "Elena", 30, Direccion("Av Libertad", 321, "Arequipa")),
        Persona(6, "Fernando", 28, Direccion("Calle Real", 654, "Trujillo"))
    };
    
    cout << "=== ARREGLO ORIGINAL ===" << endl;
    for (const auto& p : personas) {
        cout << p.nombre << " (" << p.edad << " años) - " << p.direccion.ciudad << endl;
    }
    
    // Crear y ejecutar el ordenamiento
    ExchangeSortPersonas sorter(personas);
    sorter.ordenar();
    
    // Mostrar resultados
    sorter.mostrarArregloOrdenado();
    sorter.mostrarEstadisticas();
}


int main() {
    cout << "EXCHANGE SORT CON ESTRUCTURAS JERÁRQUICAS COMPLEJAS" << endl;
    
    demostracionCompleta();
    return 0;
}