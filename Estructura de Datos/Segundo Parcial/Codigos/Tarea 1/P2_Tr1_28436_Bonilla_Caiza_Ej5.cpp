#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// Estructura de usuario en la cola
struct Usuario {
    int id_usuario;
    int tiempo_espera;
    Usuario* siguiente;
    
    Usuario(int id, int tiempo) : id_usuario(id), tiempo_espera(tiempo), siguiente(nullptr) {}
};

// Clase Cola dinamica
class Cola {
private:
    Usuario* frente;
    Usuario* final;
    int tamano;
    double promedioCache;
    bool promedioCacheValido;
    
public:
    Cola() : frente(nullptr), final(nullptr), tamano(0), promedioCache(0.0), promedioCacheValido(false) {}
    
    // Agregar usuario a la cola
    void encolar(int id, int tiempo) {
        Usuario* nuevo = new Usuario(id, tiempo);
        if (!frente) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamano++;
        promedioCacheValido = false;
    }
    
    // Calcular promedio de tiempo de espera
    double calcularPromedio() {
        if (promedioCacheValido) {
            return promedioCache;
        }
        
        if (tamano == 0) {
            promedioCache = 0.0;
            promedioCacheValido = true;
            return 0.0;
        }
        
        int suma = 0;
        Usuario* actual = frente;
        while (actual) {
            suma += actual->tiempo_espera;
            actual = actual->siguiente;
        }
        
        promedioCache = static_cast<double>(suma) / tamano;
        promedioCacheValido = true;
        return promedioCache;
    }
    
    int getTamano() const { return tamano; }
    
    void mostrarCola() const {
        if (!frente) {
            cout << "[Cola vacia]";
            return;
        }
        
        Usuario* actual = frente;
        cout << "[";
        while (actual) {
            cout << "U" << actual->id_usuario << "(" << actual->tiempo_espera << "min)";
            if (actual->siguiente) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << "]";
    }
    
    // Constructor de copia
    Cola(const Cola& otra) : frente(nullptr), final(nullptr), tamano(0), 
                              promedioCache(otra.promedioCache), 
                              promedioCacheValido(otra.promedioCacheValido) {
        Usuario* actual = otra.frente;
        while (actual) {
            encolar(actual->id_usuario, actual->tiempo_espera);
            actual = actual->siguiente;
        }
    }
    
    // Operador de asignacion
    Cola& operator=(const Cola& otra) {
        if (this != &otra) {
            // Limpiar cola actual
            while (frente) {
                Usuario* temp = frente;
                frente = frente->siguiente;
                delete temp;
            }
            
            // Copiar nueva cola
            frente = final = nullptr;
            tamano = 0;
            promedioCache = otra.promedioCache;
            promedioCacheValido = otra.promedioCacheValido;
            
            Usuario* actual = otra.frente;
            while (actual) {
                encolar(actual->id_usuario, actual->tiempo_espera);
                actual = actual->siguiente;
            }
        }
        return *this;
    }
    
    ~Cola() {
        while (frente) {
            Usuario* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }
};

// Clase para manejar el arreglo de colas
class GestorColas {
private:
    Cola* colas;
    int numColas;
    int totalComparaciones;
    int totalIntercambios;
    int totalCalculosPromedio;
    
    void mostrarGraficoPromedios(string titulo) {
        cout << "\n" << titulo << endl;
        cout << "Promedios de tiempo de espera:" << endl;
        cout << "\n  Cola |  Promedio  | Grafico" << endl;
        cout << "  -----|------------|----------------------------------------" << endl;
        
        for (int i = 0; i < numColas; i++) {
            double promedio = colas[i].calcularPromedio();
            cout << "   " << i << "   | " << setw(8) << fixed << setprecision(2) 
                 << promedio << "   | ";
            
            // Grafico de barras
            int barras = static_cast<int>(promedio / 2);
            for (int j = 0; j < barras; j++) {
                cout << "*";
            }
            cout << " (" << promedio << " min)" << endl;
        }
    }
    
public:
    GestorColas(int n) : numColas(n), totalComparaciones(0), totalIntercambios(0), 
                         totalCalculosPromedio(0) {
        colas = new Cola[numColas];
    }
    
    void agregarUsuarioACola(int indiceCola, int idUsuario, int tiempoEspera) {
        if (indiceCola >= 0 && indiceCola < numColas) {
            colas[indiceCola].encolar(idUsuario, tiempoEspera);
        }
    }
    
    void mostrarArreglo(string titulo = "") {
        if (!titulo.empty()) {
            cout << "\n" << titulo << endl;
        }
        
        for (int i = 0; i < numColas; i++) {
            double promedio = colas[i].calcularPromedio();
            cout << "  Cola[" << i << "] (Prom: " << fixed << setprecision(2) 
                 << promedio << " min, " << colas[i].getTamano() << " usuarios): ";
            colas[i].mostrarCola();
            cout << endl;
        }
    }
    
    void bubbleSortOptimizado() {
        cout << "\n--- BUBBLE SORT OPTIMIZADO SOBRE ARREGLO DE COLAS ---" << endl;
        cout << "    Criterio: Promedio de tiempo de espera (menor a mayor)" << endl;
        
        cout << "\n[ARREGLO INICIAL DE COLAS]";
        mostrarArreglo();
        mostrarGraficoPromedios("[GRAFICO INICIAL]");
        
        // Tabla de registro
        cout << "\n\n[TABLA DE REGISTRO POR PASADA]" << endl;
        cout << setw(8) << "Pasada" << " | " 
             << setw(15) << "Comparaciones" << " | "
             << setw(14) << "Intercambios" << " | "
             << setw(20) << "Calculo Promedios" << " | "
             << setw(12) << "Estado" << endl;
        cout << string(85, '-') << endl;
        
        bool huboIntercambio = true;
        int pasada = 1;
        int limite = numColas - 1;
        
        while (huboIntercambio && limite > 0) {
            cout << "\n\n--- PASADA " << pasada << " ---" << endl;
            cout << "Comparando elementos desde [0] hasta [" << limite << "]" << endl;
            
            huboIntercambio = false;
            int comparacionesPasada = 0;
            int intercambiosPasada = 0;
            int calculosPasada = 0;
            
            for (int i = 0; i < limite; i++) {
                cout << "\n  Comparacion entre Cola[" << i << "] y Cola[" << (i+1) << "]:" << endl;
                
                // Calcular promedios (operacion costosa)
                cout << "    Calculando promedio de Cola[" << i << "]..." << endl;
                double prom1 = colas[i].calcularPromedio();
                calculosPasada++;
                totalCalculosPromedio++;
                cout << "      Promedio Cola[" << i << "] = " << fixed << setprecision(2) 
                     << prom1 << " min" << endl;
                
                cout << "    Calculando promedio de Cola[" << (i+1) << "]..." << endl;
                double prom2 = colas[i+1].calcularPromedio();
                calculosPasada++;
                totalCalculosPromedio++;
                cout << "      Promedio Cola[" << (i+1) << "] = " << fixed << setprecision(2) 
                     << prom2 << " min" << endl;
                
                comparacionesPasada++;
                totalComparaciones++;
                
                cout << "    Comparando: " << prom1 << " vs " << prom2;
                
                if (prom1 > prom2) {
                    cout << " -> INTERCAMBIAR (Cola[" << i << "] > Cola[" << (i+1) << "])" << endl;
                    
                    // Realizar intercambio
                    Cola temp = colas[i];
                    colas[i] = colas[i+1];
                    colas[i+1] = temp;
                    
                    intercambiosPasada++;
                    totalIntercambios++;
                    huboIntercambio = true;
                    
                    cout << "    Intercambio realizado exitosamente" << endl;
                } else {
                    cout << " -> NO intercambiar (orden correcto)" << endl;
                }
            }
            
            // Registrar en la tabla
            string estado = huboIntercambio ? "Continuar" : "DETENIDO";
            cout << "\n";
            cout << setw(8) << pasada << " | " 
                 << setw(15) << comparacionesPasada << " | "
                 << setw(14) << intercambiosPasada << " | "
                 << setw(20) << calculosPasada << " | "
                 << setw(12) << estado << endl;
            
            if (!huboIntercambio) {
                cout << "\n*** OPTIMIZACION ACTIVADA ***" << endl;
                cout << "No hubo intercambios en esta pasada." << endl;
                cout << "El arreglo ya esta ordenado. Deteniendo algoritmo." << endl;
                cout << "Pasadas restantes evitadas: " << (numColas - pasada - 1) << endl;
            }
            
            cout << "\n[ESTADO DEL ARREGLO DESPUES DE LA PASADA " << pasada << "]";
            mostrarArreglo();
            mostrarGraficoPromedios("[GRAFICO DESPUES DE PASADA " + to_string(pasada) + "]");
            
            limite--;
            pasada++;
        }
    }
    
    void mostrarAnalisisFinal() {
        cout << "\n\n--- ANALISIS FINAL ---" << endl;
        
        cout << "\n[ARREGLO FINAL ORDENADO]";
        mostrarArreglo();
        mostrarGraficoPromedios("[GRAFICO FINAL - ORDENADO]");
        
        cout << "\n\n[ESTADISTICAS TOTALES]:" << endl;
        cout << "  * Total de comparaciones: " << totalComparaciones << endl;
        cout << "  * Total de intercambios: " << totalIntercambios << endl;
        cout << "  * Total de calculos de promedio: " << totalCalculosPromedio << endl;
        cout << "  * Numero de colas: " << numColas << endl;
        
        // Analisis de complejidad
        int comparacionesMaximas = (numColas * (numColas - 1)) / 2;
        int calculosMaximos = comparacionesMaximas * 2;
        
        cout << "\n[ANALISIS DE EFICIENCIA]:" << endl;
        cout << "  Comparaciones teoricas maximas (sin optimizacion): " << comparacionesMaximas << endl;
        cout << "  Comparaciones realizadas (con optimizacion): " << totalComparaciones << endl;
        cout << "  Reduccion: " << (comparacionesMaximas - totalComparaciones) << " comparaciones evitadas" << endl;
        cout << "  Porcentaje de reduccion: " << fixed << setprecision(1)
             << (100.0 * (comparacionesMaximas - totalComparaciones) / comparacionesMaximas) << "%" << endl;
        
        cout << "\n  Calculos de promedio teoricos maximos: " << calculosMaximos << endl;
        cout << "  Calculos de promedio realizados: " << totalCalculosPromedio << endl;
    }
    
    ~GestorColas() {
        delete[] colas;
    }
};

int main() {
    cout << "--- BUBBLE SORT OPTIMIZADO SOBRE ARREGLO DE COLAS ---" << endl;
    cout << "    Ordenamiento por promedio de tiempo de espera" << endl;
    
    // Crear gestor con 5 colas
    GestorColas gestor(5);
    
    cout << "\n[CONSTRUCCION DEL ARREGLO DE COLAS]" << endl;
    cout << "Creando 5 colas con diferentes usuarios y tiempos de espera..." << endl;
    
    // Cola 0 - Promedio alto
    gestor.agregarUsuarioACola(0, 101, 25);
    gestor.agregarUsuarioACola(0, 102, 30);
    gestor.agregarUsuarioACola(0, 103, 28);
    
    // Cola 1 - Promedio medio
    gestor.agregarUsuarioACola(1, 201, 15);
    gestor.agregarUsuarioACola(1, 202, 18);
    gestor.agregarUsuarioACola(1, 203, 12);
    
    // Cola 2 - Promedio bajo
    gestor.agregarUsuarioACola(2, 301, 5);
    gestor.agregarUsuarioACola(2, 302, 8);
    gestor.agregarUsuarioACola(2, 303, 6);
    gestor.agregarUsuarioACola(2, 304, 7);
    
    // Cola 3 - Promedio muy alto
    gestor.agregarUsuarioACola(3, 401, 35);
    gestor.agregarUsuarioACola(3, 402, 40);
    
    // Cola 4 - Promedio medio-bajo
    gestor.agregarUsuarioACola(4, 501, 10);
    gestor.agregarUsuarioACola(4, 502, 12);
    gestor.agregarUsuarioACola(4, 503, 11);
    gestor.agregarUsuarioACola(4, 504, 13);
    
    // Aplicar Bubble Sort Optimizado
    gestor.bubbleSortOptimizado();
    
    // Mostrar analisis final
    gestor.mostrarAnalisisFinal();
    
    return 0;
}