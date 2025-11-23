#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// Estructura para representar una transaccion bancaria
struct Transaccion {
    int id_transaccion;
    double monto;
    string tipo;
    string fecha;
    // Constructor
    Transaccion(int id = 0, double m = 0.0, string t = "", string f = "") 
        : id_transaccion(id), monto(m), tipo(t), fecha(f) {}
};
// Clase para manejar el arreglo y el algoritmo
class GestorTransacciones {
private:
    Transaccion* transacciones;
    int capacidad;
    int totalComparaciones;
    int totalDesplazamientos;
    void mostrarTransaccion(const Transaccion& t) {
        cout << "[ID:" << setw(3) << t.id_transaccion 
             << " | Monto: $" << setw(8) << fixed << setprecision(2) << t.monto
             << " | Tipo: " << setw(10) << t.tipo 
             << " | Fecha: " << t.fecha << "]";
    }
public:
    GestorTransacciones(int cap) : capacidad(cap), totalComparaciones(0), totalDesplazamientos(0) {
        transacciones = new Transaccion[capacidad];
    }
    void agregarTransaccion(int pos, int id, double monto, string tipo, string fecha) {
        if (pos >= 0 && pos < capacidad) {
            transacciones[pos] = Transaccion(id, monto, tipo, fecha);
        }
    }
    void mostrarArreglo(string titulo = "") {
        if (!titulo.empty()) {
            cout << "\n" << titulo << endl;
        }
        for (int i = 0; i < capacidad; i++) {
            cout << "  [" << i << "] ";
            mostrarTransaccion(transacciones[i]);
            cout << endl;
        }
    }
    void insertionSort() {
        cout << "\n--- INSERTION SORT CON ESTABILIDAD EN ARREGLO ---" << endl;
        cout << "    Ordenamiento por MONTO (menor a mayor)" << endl;
        cout << "\n[ARREGLO INICIAL - DESORDENADO]";
        mostrarArreglo();
        cout << "\n*** NOTA: Observar que hay montos IGUALES ***" << endl;
        cout << "    Transacciones con monto igual deben mantener su orden original" << endl;
        cout << "    para demostrar la ESTABILIDAD del algoritmo." << endl;
        // Algoritmo Insertion Sort
        for (int i = 1; i < capacidad; i++) {
            cout << "\n--- ITERACION " << i << " ---" << endl;
            // Guardar la clave (registro completo)
            Transaccion clave = transacciones[i];
            cout << "\n> CLAVE seleccionada en posicion [" << i << "]:" << endl;
            cout << "  ";
            mostrarTransaccion(clave);
            cout << endl;
            int comparacionesIteracion = 0;
            int desplazamientosIteracion = 0;
            // Buscar posicion correcta y desplazar
            int j = i - 1;
            cout << "\n> Iniciando busqueda de posicion correcta..." << endl;
            cout << "  Comparando clave (monto: $" << fixed << setprecision(2) 
                 << clave.monto << ") con elementos anteriores:\n" << endl;
            // Desplazar elementos mayores hacia la derecha
            while (j >= 0) {
                comparacionesIteracion++;
                totalComparaciones++;
                cout << "  Comparacion #" << comparacionesIteracion << ": ";
                cout << "$" << clave.monto << " vs $" << transacciones[j].monto;
                // CRITICO: Usar > (no >=) para mantener estabilidad
                if (transacciones[j].monto > clave.monto) {
                    cout << " -> Clave MENOR, desplazar elemento hacia derecha" << endl;
                    // Desplazar el elemento hacia la derecha
                    cout << "     Desplazamiento #" << (desplazamientosIteracion + 1) << ": ";
                    cout << "transacciones[" << (j+1) << "] = transacciones[" << j << "]" << endl;
                    cout << "     Moviendo: ";
                    mostrarTransaccion(transacciones[j]);
                    cout << endl;
                    cout << "     Desde posicion [" << j << "] hacia [" << (j+1) << "]" << endl;
                    transacciones[j + 1] = transacciones[j];
                    desplazamientosIteracion++;
                    totalDesplazamientos++;
                    j--;
                } else if (transacciones[j].monto == clave.monto) {
                    cout << " -> Montos IGUALES (";
                    cout << "ID:" << transacciones[j].id_transaccion << " vs ID:" << clave.id_transaccion;
                    cout << ")" << endl;
                    cout << "     ESTABILIDAD: Mantener orden original, NO desplazar" << endl;
                    cout << "     Elemento actual queda antes que la clave" << endl;
                    break;
                } else {
                    cout << " -> Clave MAYOR o igual, posicion encontrada" << endl;
                    break;
                }
            }
            // Insertar la clave en su posicion
            int posicionFinal = j + 1;
            transacciones[posicionFinal] = clave;
            cout << "\n> INSERCION de la clave en posicion [" << posicionFinal << "]" << endl;
            if (posicionFinal != i) {
                cout << "  La clave se movio desde posicion [" << i << "] a [" << posicionFinal << "]" << endl;
            } else {
                cout << "  La clave permanece en su posicion original [" << i << "]" << endl;
            }
            cout << "\n[RESUMEN DE LA ITERACION]:" << endl;
            cout << "  * Comparaciones realizadas: " << comparacionesIteracion << endl;
            cout << "  * Desplazamientos realizados: " << desplazamientosIteracion << endl;
            cout << "  * Elementos movidos: " << desplazamientosIteracion << " registros" << endl;
            cout << "\n[ESTADO DEL ARREGLO]:" << endl;
            mostrarArreglo();
        }
    }
    void mostrarAnalisisFinal() {
        cout << "\n--- ANALISIS FINAL ---" << endl;
        cout << "\n[ARREGLO FINAL ORDENADO POR MONTO]:" << endl;
        mostrarArreglo();
        cout << "\n[ESTADISTICAS TOTALES]:" << endl;
        cout << "  * Total de comparaciones: " << totalComparaciones << endl;
        cout << "  * Total de desplazamientos: " << totalDesplazamientos << endl;
        cout << "  * Registros completos movidos: " << totalDesplazamientos << endl;
        cout << "\n[DEMOSTRACION DE ESTABILIDAD]:" << endl;
        cout << "\nVerificando transacciones con el MISMO monto:" << endl;
        // Verificar estabilidad
        for (int i = 0; i < capacidad - 1; i++) {
            for (int j = i + 1; j < capacidad; j++) {
                if (transacciones[i].monto == transacciones[j].monto) {
                    cout << "\n  Monto: $" << fixed << setprecision(2) << transacciones[i].monto << endl;
                    cout << "    - Transaccion ID " << transacciones[i].id_transaccion 
                         << " (posicion " << i << ")" << endl;
                    cout << "    - Transaccion ID " << transacciones[j].id_transaccion 
                         << " (posicion " << j << ")" << endl;
                    if (transacciones[i].id_transaccion < transacciones[j].id_transaccion) {
                        cout << "    [OK] Orden original preservado: ID menor aparece primero" << endl;
                    } else {
                        cout << "    [ADVERTENCIA] Orden alterado - perdida de estabilidad" << endl;
                    }
                }
            }
        }
    }
    ~GestorTransacciones() {
        delete[] transacciones;
    }
};
int main() {
    cout << "--- INSERTION SORT CON ESTABILIDAD - TRANSACCIONES BANCARIAS ---" << endl;
    cout << "    Demostracion de ordenamiento estable de registros" << endl;
    // Crear gestor con 8 transacciones
    GestorTransacciones gestor(8);
    cout << "\n[CONSTRUCCION DEL ARREGLO DE TRANSACCIONES]" << endl;
    cout << "Agregando transacciones con MONTOS REPETIDOS para demostrar estabilidad...\n" << endl;
    // Agregar transacciones - IMPORTANTE: hay montos iguales para demostrar estabilidad
    gestor.agregarTransaccion(0, 101, 1500.00, "Deposito", "2025-01-15");
    gestor.agregarTransaccion(1, 102, 750.50, "Retiro", "2025-01-16");
    gestor.agregarTransaccion(2, 103, 2300.00, "Transferencia", "2025-01-17");
    gestor.agregarTransaccion(3, 104, 750.50, "Deposito", "2025-01-18");  // Mismo monto que ID 102
    gestor.agregarTransaccion(4, 105, 1200.75, "Pago", "2025-01-19");
    gestor.agregarTransaccion(5, 106, 750.50, "Retiro", "2025-01-20");    // Mismo monto que ID 102 y 104
    gestor.agregarTransaccion(6, 107, 1500.00, "Transferencia", "2025-01-21"); // Mismo monto que ID 101
    gestor.agregarTransaccion(7, 108, 980.25, "Pago", "2025-01-22");
    // Aplicar Insertion Sort
    gestor.insertionSort();
    // Mostrar analisis final
    gestor.mostrarAnalisisFinal();
    return 0;
}