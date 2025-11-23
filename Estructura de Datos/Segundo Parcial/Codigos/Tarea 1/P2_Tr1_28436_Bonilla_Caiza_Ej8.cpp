#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Estructura para la venta
struct Venta {
    int id_venta;
    string fecha;
    double valor;
    
    Venta(int id, string f, double v) : id_venta(id), fecha(f), valor(v) {}
    
    // Para facilitar la impresión
    void mostrar() const {
        cout << "ID: " << id_venta << " | Fecha: " << fecha << " | Valor: $" << fixed << setprecision(2) << valor;
    }
};

class ExchangeSortVentas {
private:
    vector<Venta> ventas;
    int comparaciones;
    int intercambios;
    
public:
    ExchangeSortVentas(vector<Venta> v) : ventas(v), comparaciones(0), intercambios(0) {}
    
    // Implementación de Exchange Sort (Bubble Sort)
    void ordenar() {
        int n = ventas.size();
        bool intercambiado;
        
        cout << "=== INICIO DEL ORDENAMIENTO EXCHANGE SORT ===" << endl;
        cout << "Arreglo inicial:" << endl;
        mostrarArreglo();
        
        for (int i = 0; i < n - 1; i++) {
            intercambiado = false;
            cout << "\n--- PASADA " << (i + 1) << " ---" << endl;
            
            for (int j = 0; j < n - i - 1; j++) {
                // Mostrar comparación actual
                cout << "Comparando posiciones " << j << " y " << (j + 1) << ":" << endl;
                cout << "  ";
                ventas[j].mostrar();
                cout << " vs ";
                ventas[j + 1].mostrar();
                cout << endl;
                
                comparaciones++;
                
                if (ventas[j].valor > ventas[j + 1].valor) {
                    // INTERCAMBIO
                    cout << "  >>> INTERCAMBIO REQUERIDO <<<" << endl;
                    
                    // Mostrar elementos antes del intercambio
                    cout << "  Antes: ";
                    ventas[j].mostrar();
                    cout << " | ";
                    ventas[j + 1].mostrar();
                    cout << endl;
                    
                    // Realizar intercambio
                    swap(ventas[j], ventas[j + 1]);
                    intercambios++;
                    intercambiado = true;
                    
                    // Mostrar elementos después del intercambio
                    cout << "  Después: ";
                    ventas[j].mostrar();
                    cout << " | ";
                    ventas[j + 1].mostrar();
                    cout << endl;
                    
                    // Verificar estabilidad si hay valores iguales
                    verificarEstabilidad(j, j + 1);
                } else {
                    cout << "  ✓ No se intercambia (orden correcto)" << endl;
                    
                    // Verificar si son valores iguales pero no se intercambian
                    if (ventas[j].valor == ventas[j + 1].valor) {
                        cout << "  NOTA: Valores iguales detectados - ";
                        cout << "Manteniendo orden original: ";
                        cout << "ID " << ventas[j].id_venta << " antes de ID " << ventas[j + 1].id_venta << endl;
                    }
                }
            }
            
            // Mostrar estado después de cada pasada
            cout << "\nEstado después de pasada " << (i + 1) << ":" << endl;
            mostrarArreglo();
            
            // Si no hubo intercambios, el arreglo ya está ordenado
            if (!intercambiado) {
                cout << "\n✓ No hubo intercambios en esta pasada. Ordenamiento completado." << endl;
                break;
            }
        }
        
        cout << "\n=== ORDENAMIENTO FINALIZADO ===" << endl;
    }
    
    // Verificar estabilidad cuando se intercambian elementos
    void verificarEstabilidad(int pos1, int pos2) {
        // Solo verificar si los valores son iguales
        if (ventas[pos1].valor == ventas[pos2].valor) {
            cout << "  ⚠️  ALERTA DE ESTABILIDAD: Se intercambiaron elementos con VALOR IGUAL" << endl;
            cout << "     ID anterior: " << ventas[pos2].id_venta << " ahora está antes de ID: " << ventas[pos1].id_venta << endl;
            cout << "     ¡El orden relativo de elementos iguales ha cambiado!" << endl;
        }
    }
    
    // Mostrar el arreglo completo
    void mostrarArreglo() {
        for (size_t i = 0; i < ventas.size(); i++) {
            cout << "[" << i << "] ";
            ventas[i].mostrar();
            cout << endl;
        }
    }
    
    // Mostrar estadísticas
    void mostrarEstadisticas() {
        cout << "\n=== ESTADÍSTICAS ===" << endl;
        cout << "Total de comparaciones: " << comparaciones << endl;
        cout << "Total de intercambios: " << intercambios << endl;
        cout << "Número de elementos: " << ventas.size() << endl;
        
        double eficiencia = (double)intercambios / comparaciones * 100;
        cout << "Eficiencia de intercambios: " << fixed << setprecision(2) << eficiencia << "%" << endl;
    }
    
    // Análisis formal de estabilidad
    void analizarEstabilidad() {
        cout << "\n=== ANÁLISIS FORMAL DE ESTABILIDAD ===" << endl;
        
        // Buscar pares de elementos con valores iguales en el resultado final
        bool estable = true;
        vector<pair<int, int>> paresInestables;
        
        for (size_t i = 0; i < ventas.size() - 1; i++) {
            if (ventas[i].valor == ventas[i + 1].valor) {
                // Verificar si el orden de IDs es creciente (estable)
                if (ventas[i].id_venta > ventas[i + 1].id_venta) {
                    estable = false;
                    paresInestables.push_back({ventas[i].id_venta, ventas[i + 1].id_venta});
                }
            }
        }
        
        if (estable) {
            cout << "✓ RESULTADO: Exchange Sort ES ESTABLE en esta ejecución" << endl;
            cout << "  Todos los elementos con valores iguales mantienen su orden relativo original" << endl;
        } else {
            cout << "✗ RESULTADO: Exchange Sort NO ES ESTABLE en esta ejecución" << endl;
            cout << "  Se encontraron " << paresInestables.size() << " pares donde el orden relativo cambió:" << endl;
            for (const auto& par : paresInestables) {
                cout << "  - ID " << par.first << " aparece antes de ID " << par.second << endl;
            }
        }
    }
    
    // Getter para estadísticas
    int getComparaciones() const { return comparaciones; }
    int getIntercambios() const { return intercambios; }
    vector<Venta> getVentasOrdenadas() const { return ventas; }
};

// Función para crear datos de prueba con elementos duplicados
vector<Venta> crearDatosPrueba() {
    return {
        Venta(1, "2024-01-01", 100.50),
        Venta(2, "2024-01-02", 50.25),    // Valor duplicado
        Venta(3, "2024-01-03", 200.75),
        Venta(4, "2024-01-04", 50.25),    // Valor duplicado
        Venta(5, "2024-01-05", 150.00),
        Venta(6, "2024-01-06", 100.50),   // Valor duplicado
        Venta(7, "2024-01-07", 75.80),
        Venta(8, "2024-01-08", 50.25)     // Valor duplicado
    };
}

// Función para demostrar con diferentes casos
void demostrarCasosEstabilidad() {
    cout << "DEMOSTRACIÓN DE ESTABILIDAD EN EXCHANGE SORT" << endl;
    cout << "============================================" << endl;
    
    // Caso 1: Datos con valores duplicados
    cout << "\n*** CASO 1: Datos con valores duplicados ***" << endl;
    vector<Venta> ventas = crearDatosPrueba();
    
    cout << "Datos iniciales (notar IDs con valores iguales):" << endl;
    for (const auto& venta : ventas) {
        venta.mostrar();
        cout << endl;
    }
    
    ExchangeSortVentas sorter(ventas);
    sorter.ordenar();
    sorter.mostrarEstadisticas();
    sorter.analizarEstabilidad();
}

int main() {
    demostrarCasosEstabilidad();
    return 0;
}