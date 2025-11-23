#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Estructura del nodo para lista doblemente enlazada
struct Nodo {
    string titulo;
    string autor;
    int anio;
    string ISBN;
    Nodo* next;
    Nodo* prev;
    
    Nodo(string t, string a, int an, string i) 
        : titulo(t), autor(a), anio(an), ISBN(i), next(nullptr), prev(nullptr) {}
};

// Clase para manejar la lista doblemente enlazada
class ListaLibros {
private:
    Nodo* cabeza;
    Nodo* cola;
    int totalComparaciones;
    int totalMovimientos;
    int totalIntercambios;
    
    // Funcion de comparacion compuesta
    // Retorna true si nodo1 debe ir ANTES que nodo2
    bool esmenor(Nodo* n1, Nodo* n2) {
        // Prioridad 1: Autor (alfabetico)
        if (n1->autor != n2->autor) {
            return n1->autor < n2->autor;
        }
        // Prioridad 2: Anio (ascendente)
        return n1->anio < n2->anio;
    }
    
    void mostrarNodo(Nodo* nodo, bool conDireccion = false) {
        if (!nodo) {
            cout << "[NULL]";
            return;
        }
        cout << "[ISBN:" << nodo->ISBN << " | \"" << nodo->titulo << "\" | " 
             << nodo->autor << " (" << nodo->anio << ")";
        if (conDireccion) {
            cout << " @" << nodo;
        }
        cout << "]";
    }
    
    void dibujarEsquemaNodo(Nodo* nodo, string etiqueta) {
        cout << "      " << etiqueta << ": ";
        if (!nodo) {
            cout << "NULL" << endl;
            return;
        }
        cout << "ISBN:" << nodo->ISBN << " - " << nodo->titulo << endl;
        cout << "         prev -> ";
        if (nodo->prev) cout << "ISBN:" << nodo->prev->ISBN;
        else cout << "NULL";
        cout << " | next -> ";
        if (nodo->next) cout << "ISBN:" << nodo->next->ISBN;
        else cout << "NULL";
        cout << endl;
    }
    
public:
    ListaLibros() : cabeza(nullptr), cola(nullptr), totalComparaciones(0), 
                    totalMovimientos(0), totalIntercambios(0) {}
    
    void insertarAlFinal(string titulo, string autor, int anio, string ISBN) {
        Nodo* nuevo = new Nodo(titulo, autor, anio, ISBN);
        
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->next = nuevo;
            nuevo->prev = cola;
            cola = nuevo;
        }
    }
    
    void mostrarLista(string titulo = "") {
        if (!titulo.empty()) {
            cout << "\n" << titulo << endl;
        }
        
        if (!cabeza) {
            cout << "  Lista vacia" << endl;
            return;
        }
        
        Nodo* temp = cabeza;
        int pos = 0;
        cout << "  Cabeza -> ";
        while (temp) {
            cout << "[" << pos << ":ISBN" << temp->ISBN << "]";
            if (temp->next) cout << " <-> ";
            temp = temp->next;
            pos++;
        }
        cout << " <- Cola" << endl;
        
        // Mostrar detalles
        temp = cabeza;
        pos = 0;
        while (temp) {
            cout << "    [" << pos << "] ";
            mostrarNodo(temp);
            cout << endl;
            temp = temp->next;
            pos++;
        }
    }
    
    void mostrarEsquemaPunteros(Nodo* nodo1, Nodo* nodo2, string momento) {
        cout << "\n    " << momento << ":" << endl;
        dibujarEsquemaNodo(nodo1, "Nodo A");
        dibujarEsquemaNodo(nodo2, "Nodo B");
    }
    
    // Intercambiar dos nodos en la lista doblemente enlazada
    void intercambiarNodos(Nodo* nodo1, Nodo* nodo2) {
        if (!nodo1 || !nodo2 || nodo1 == nodo2) return;
        
        cout << "\n  [REALIZANDO INTERCAMBIO DE NODOS]" << endl;
        cout << "    Nodo A (actual): ISBN:" << nodo1->ISBN << " - " << nodo1->titulo << endl;
        cout << "    Nodo B (minimo): ISBN:" << nodo2->ISBN << " - " << nodo2->titulo << endl;
        
        mostrarEsquemaPunteros(nodo1, nodo2, "ANTES del intercambio");
        
        int movimientos = 0;
        
        // Caso 1: Nodos adyacentes
        if (nodo1->next == nodo2) {
            cout << "\n    Caso especial: Nodos ADYACENTES (nodo1->next == nodo2)" << endl;
            
            // Actualizar enlaces externos
            if (nodo1->prev) {
                nodo1->prev->next = nodo2;
                movimientos++;
            } else {
                cabeza = nodo2;
                movimientos++;
            }
            
            if (nodo2->next) {
                nodo2->next->prev = nodo1;
                movimientos++;
            } else {
                cola = nodo1;
                movimientos++;
            }
            
            // Intercambiar enlaces entre nodo1 y nodo2
            nodo2->prev = nodo1->prev;
            movimientos++;
            nodo1->next = nodo2->next;
            movimientos++;
            nodo1->prev = nodo2;
            movimientos++;
            nodo2->next = nodo1;
            movimientos++;
            
        } else {
            cout << "\n    Caso general: Nodos NO adyacentes" << endl;
            
            // Guardar punteros originales
            Nodo* prev1 = nodo1->prev;
            Nodo* next1 = nodo1->next;
            Nodo* prev2 = nodo2->prev;
            Nodo* next2 = nodo2->next;
            
            // Actualizar prev de nodo1
            if (prev1) {
                prev1->next = nodo2;
                movimientos++;
            } else {
                cabeza = nodo2;
                movimientos++;
            }
            
            // Actualizar next de nodo1
            if (next1) {
                next1->prev = nodo2;
                movimientos++;
            }
            
            // Actualizar prev de nodo2
            if (prev2) {
                prev2->next = nodo1;
                movimientos++;
            } else {
                cabeza = nodo1;
                movimientos++;
            }
            
            // Actualizar next de nodo2
            if (next2) {
                next2->prev = nodo1;
                movimientos++;
            } else {
                cola = nodo1;
                movimientos++;
            }
            
            // Intercambiar punteros de nodo1
            nodo1->prev = prev2;
            movimientos++;
            nodo1->next = next2;
            movimientos++;
            
            // Intercambiar punteros de nodo2
            nodo2->prev = prev1;
            movimientos++;
            nodo2->next = next1;
            movimientos++;
        }
        
        mostrarEsquemaPunteros(nodo2, nodo1, "DESPUES del intercambio");
        
        cout << "\n    Total de movimientos de punteros en este intercambio: " << movimientos << endl;
        totalMovimientos += movimientos;
        totalIntercambios++;
    }
    
    void selectionSort() {
        cout << "\n--- SELECTION SORT EN LISTA DOBLEMENTE ENLAZADA ---" << endl;
        cout << "    Ordenamiento por: 1.Autor, 2.Anio" << endl;
        
        cout << "\n[LISTA INICIAL - DESORDENADA]";
        mostrarLista();
        
        if (!cabeza || !cabeza->next) {
            cout << "\nLista con 0 o 1 elementos, ya esta ordenada." << endl;
            return;
        }
        
        Nodo* actual = cabeza;
        int pasada = 1;
        
        // Tabla de registro
        cout << "\n[TABLA DE REGISTRO DE OPERACIONES]" << endl;
        cout << setw(8) << "Pasada" << " | " 
             << setw(12) << "Comparaciones" << " | "
             << setw(12) << "Movimientos" << " | "
             << setw(15) << "Intercambio" << endl;
        cout << string(65, '-') << endl;
        
        while (actual && actual->next) {
            cout << "\n\n--- PASADA " << pasada << " ---" << endl;
            cout << "Nodo actual (punto de partida): ";
            mostrarNodo(actual);
            cout << endl;
            
            Nodo* minimo = actual;
            Nodo* buscador = actual->next;
            int comparacionesPasada = 0;
            int movimientosAntes = totalMovimientos;
            
            cout << "\nBuscando el MINIMO desde este nodo hasta el final..." << endl;
            
            while (buscador) {
                comparacionesPasada++;
                totalComparaciones++;
                
                cout << "\n  Comparacion #" << comparacionesPasada << ":" << endl;
                cout << "    Candidato actual: ";
                mostrarNodo(buscador);
                cout << endl;
                cout << "    Minimo temporal: ";
                mostrarNodo(minimo);
                cout << endl;
                
                // Comparar por autor
                if (buscador->autor != minimo->autor) {
                    cout << "    Criterio 1 (Autor): \"" << buscador->autor << "\" vs \"" 
                         << minimo->autor << "\"";
                    if (buscador->autor < minimo->autor) {
                        cout << " => Candidato MENOR" << endl;
                        minimo = buscador;
                        cout << "    *** Nuevo minimo encontrado ***" << endl;
                    } else {
                        cout << " => Minimo actual es MENOR" << endl;
                    }
                } else {
                    cout << "    Autor igual: \"" << buscador->autor << "\"" << endl;
                    cout << "    Criterio 2 (Anio): " << buscador->anio << " vs " 
                         << minimo->anio;
                    if (buscador->anio < minimo->anio) {
                        cout << " => Candidato MENOR" << endl;
                        minimo = buscador;
                        cout << "    *** Nuevo minimo encontrado ***" << endl;
                    } else {
                        cout << " => Minimo actual es MENOR o igual" << endl;
                    }
                }
                
                buscador = buscador->next;
            }
            
            cout << "\n[RESULTADO DE LA BUSQUEDA]:" << endl;
            cout << "  Nodo minimo encontrado: ";
            mostrarNodo(minimo);
            cout << endl;
            
            bool huboIntercambio = false;
            if (minimo != actual) {
                cout << "  Se requiere INTERCAMBIO" << endl;
                intercambiarNodos(actual, minimo);
                huboIntercambio = true;
                
                // Importante: actualizar 'actual' porque los nodos se intercambiaron
                actual = minimo;
            } else {
                cout << "  NO se requiere intercambio (el minimo ya esta en posicion)" << endl;
            }
            
            int movimientosPasada = totalMovimientos - movimientosAntes;
            
            // Agregar fila a la tabla
            cout << "\n";
            cout << setw(8) << pasada << " | " 
                 << setw(12) << comparacionesPasada << " | "
                 << setw(12) << movimientosPasada << " | "
                 << setw(15) << (huboIntercambio ? "SI" : "NO") << endl;
            
            cout << "\n[ESTADO DE LA LISTA DESPUES DE LA PASADA " << pasada << "]";
            mostrarLista();
            
            actual = actual->next;
            pasada++;
        }
    }
    
    void mostrarAnalisisFinal() {
        cout << "\n\n--- ANALISIS FINAL ---" << endl;
        
        cout << "\n[LISTA FINAL ORDENADA]";
        mostrarLista();
        
        cout << "\n[ESTADISTICAS TOTALES]:" << endl;
        cout << "  * Total de comparaciones: " << totalComparaciones << endl;
        cout << "  * Total de movimientos de punteros: " << totalMovimientos << endl;
        cout << "  * Total de intercambios realizados: " << totalIntercambios << endl;
        
        cout << "\n[VERIFICACION DEL ORDENAMIENTO]:" << endl;
        cout << "Libros ordenados por Autor y luego por Anio:" << endl;
        
        Nodo* temp = cabeza;
        string autorActual = "";
        while (temp) {
            if (temp->autor != autorActual) {
                autorActual = temp->autor;
                cout << "\n  Autor: " << autorActual << endl;
            }
            cout << "    - Anio " << temp->anio << ": " << temp->titulo 
                 << " (ISBN:" << temp->ISBN << ")" << endl;
            temp = temp->next;
        }
    }
    
    ~ListaLibros() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->next;
            delete temp;
        }
    }
};

int main() {
    cout << "--- SELECTION SORT EN LISTA DOBLEMENTE ENLAZADA ---" << endl;
    cout << "    Ordenamiento de libros por Autor y Anio" << endl;
    
    ListaLibros biblioteca;
    
    cout << "\n[CONSTRUCCION DE LA LISTA DE LIBROS]" << endl;
    cout << "Agregando libros a la lista doblemente enlazada..." << endl;
    
    // Agregar libros con autores y anios variados
    biblioteca.insertarAlFinal("Cien anios de soledad", "Garcia Marquez", 1967, "978-0307474728");
    biblioteca.insertarAlFinal("1984", "Orwell", 1949, "978-0451524935");
    biblioteca.insertarAlFinal("El principito", "Saint-Exupery", 1943, "978-0156012195");
    biblioteca.insertarAlFinal("Cronica de una muerte anunciada", "Garcia Marquez", 1981, "978-1400034956");
    biblioteca.insertarAlFinal("Rebelion en la granja", "Orwell", 1945, "978-0451526342");
    biblioteca.insertarAlFinal("El amor en los tiempos del colera", "Garcia Marquez", 1985, "978-0307389732");
    
    
    // Aplicar Selection Sort
    biblioteca.selectionSort();
    
    // Mostrar analisis final
    biblioteca.mostrarAnalisisFinal();
    
    
    return 0;
}