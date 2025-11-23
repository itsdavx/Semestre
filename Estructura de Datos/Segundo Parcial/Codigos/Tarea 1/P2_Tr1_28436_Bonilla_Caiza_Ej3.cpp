#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// Estructura para representar un producto
struct Producto {
    int codigo;
    string descripcion;
    string categoria;
    double peso;
    double precio;
    // Constructor
    Producto(int cod = 0, string desc = "", string cat = "", double p = 0.0, double pr = 0.0)
        : codigo(cod), descripcion(desc), categoria(cat), peso(p), precio(pr) {}
};
// Clase para manejar el arreglo de productos
class GestorProductos {
private:
    Producto* productos;
    int capacidad;
    int totalComparaciones;
    int totalIntercambios;
    // Funcion de comparacion compuesta con tres criterios
    // Retorna true si producto1 debe ir ANTES que producto2
    bool esmenor(const Producto& p1, const Producto& p2) {
        // Prioridad 1: Categoria (orden alfabetico)
        if (p1.categoria != p2.categoria) {
            return p1.categoria < p2.categoria;
        }
        // Prioridad 2: Precio (ascendente)
        if (p1.precio != p2.precio) {
            return p1.precio < p2.precio;
        }
        // Prioridad 3: Peso (ascendente)
        return p1.peso < p2.peso;
    }
    void mostrarProducto(const Producto& p) {
        cout << "[Cod:" << setw(3) << p.codigo 
             << " | Cat:" << setw(12) << p.categoria
             << " | Precio:$" << setw(7) << fixed << setprecision(2) << p.precio
             << " | Peso:" << setw(6) << setprecision(2) << p.peso << "kg"
             << " | " << p.descripcion << "]";
    }
    void mostrarComparacion(const Producto& p1, const Producto& p2, bool resultado) {
        cout << "    Comparando:" << endl;
        cout << "      (A) Cod:" << p1.codigo << " - Cat:" << p1.categoria 
             << ", Precio:$" << p1.precio << ", Peso:" << p1.peso << "kg" << endl;
        cout << "      (B) Cod:" << p2.codigo << " - Cat:" << p2.categoria 
             << ", Precio:$" << p2.precio << ", Peso:" << p2.peso << "kg" << endl;
        // Analizar criterio por criterio
        if (p1.categoria != p2.categoria) {
            cout << "      -> Criterio 1 (Categoria): \"" << p1.categoria << "\" vs \"" << p2.categoria << "\"";
            if (p1.categoria < p2.categoria) {
                cout << " => (A) va ANTES" << endl;
            } else {
                cout << " => (B) va ANTES" << endl;
            }
        } else if (p1.precio != p2.precio) {
            cout << "      -> Categoria igual: \"" << p1.categoria << "\"" << endl;
            cout << "      -> Criterio 2 (Precio): $" << p1.precio << " vs $" << p2.precio;
            if (p1.precio < p2.precio) {
                cout << " => (A) va ANTES" << endl;
            } else {
                cout << " => (B) va ANTES" << endl;
            }
        } else {
            cout << "      -> Categoria igual: \"" << p1.categoria << "\"" << endl;
            cout << "      -> Precio igual: $" << p1.precio << endl;
            cout << "      -> Criterio 3 (Peso): " << p1.peso << "kg vs " << p2.peso << "kg";
            if (p1.peso < p2.peso) {
                cout << " => (A) va ANTES" << endl;
            } else {
                cout << " => (B) va ANTES" << endl;
            }
        }
        cout << "      Resultado: ";
        if (resultado) {
            cout << "(A) es MENOR => actualizar minimo" << endl;
        } else {
            cout << "(B) es MENOR o igual => mantener minimo actual" << endl;
        }
    }
public:
    GestorProductos(int cap) : capacidad(cap), totalComparaciones(0), totalIntercambios(0) {
        productos = new Producto[capacidad];
    }
    void agregarProducto(int pos, int codigo, string descripcion, string categoria, double peso, double precio) {
        if (pos >= 0 && pos < capacidad) {
            productos[pos] = Producto(codigo, descripcion, categoria, peso, precio);
        }
    }
    void mostrarArreglo(string titulo = "") {
        if (!titulo.empty()) {
            cout << "\n" << titulo << endl;
        }
        for (int i = 0; i < capacidad; i++) {
            cout << "  [" << i << "] ";
            mostrarProducto(productos[i]);
            cout << endl;
        }
    }
    void selectionSort() {
        cout << "\n--- SELECTION SORT CON COMPARACION COMPUESTA ---" << endl;
        cout << "    Ordenamiento por: 1.Categoria, 2.Precio, 3.Peso" << endl;
        cout << "\n[ARREGLO INICIAL - DESORDENADO]";
        mostrarArreglo();
        cout << "\n[CRITERIOS DE ORDENAMIENTO]:" << endl;
        cout << "  Prioridad 1: Categoria (orden alfabetico)" << endl;
        cout << "  Prioridad 2: Precio (ascendente - menor a mayor)" << endl;
        cout << "  Prioridad 3: Peso (ascendente - menor a mayor)" << endl;
        // Algoritmo Selection Sort
        for (int i = 0; i < capacidad - 1; i++) {
            cout << "\n\n--- PASADA " << (i + 1) << " ---" << endl;
            cout << "Buscando el MINIMO desde posicion [" << i << "] hasta [" << (capacidad - 1) << "]" << endl;
            int indiceMinimo = i;
            int comparacionesPasada = 0;
            cout << "\nMinimo inicial en posicion [" << i << "]: ";
            mostrarProducto(productos[indiceMinimo]);
            cout << endl;
            // Buscar el minimo en el resto del arreglo
            for (int j = i + 1; j < capacidad; j++) {
                cout << "\n  Comparacion #" << (comparacionesPasada + 1) << " (posicion [" << j << "]):" << endl;
                totalComparaciones++;
                comparacionesPasada++;
                bool resultado = esmenor(productos[j], productos[indiceMinimo]);
                mostrarComparacion(productos[j], productos[indiceMinimo], resultado);
                if (resultado) {
                    indiceMinimo = j;
                    cout << "      *** Nuevo minimo encontrado en posicion [" << j << "] ***" << endl;
                }
            }
            cout << "\n[RESULTADO DE LA BUSQUEDA]:" << endl;
            cout << "  * Comparaciones realizadas en esta pasada: " << comparacionesPasada << endl;
            cout << "  * Posicion del MINIMO encontrado: [" << indiceMinimo << "]" << endl;
            cout << "  * Producto minimo: ";
            mostrarProducto(productos[indiceMinimo]);
            cout << endl;
            // Realizar intercambio si es necesario
            if (indiceMinimo != i) {
                cout << "\n[INTERCAMBIO NECESARIO]:" << endl;
                cout << "  Intercambiando posicion [" << i << "] con posicion [" << indiceMinimo << "]" << endl;
                cout << "  Antes del intercambio:" << endl;
                cout << "    [" << i << "] ";
                mostrarProducto(productos[i]);
                cout << endl;
                cout << "    [" << indiceMinimo << "] ";
                mostrarProducto(productos[indiceMinimo]);
                cout << endl;
                // Realizar el intercambio
                Producto temp = productos[i];
                productos[i] = productos[indiceMinimo];
                productos[indiceMinimo] = temp;
                totalIntercambios++;
                cout << "  Despues del intercambio:" << endl;
                cout << "    [" << i << "] ";
                mostrarProducto(productos[i]);
                cout << endl;
                cout << "    [" << indiceMinimo << "] ";
                mostrarProducto(productos[indiceMinimo]);
                cout << endl;
            } else {
                cout << "\n[SIN INTERCAMBIO]:" << endl;
                cout << "  El elemento en posicion [" << i << "] ya es el minimo" << endl;
                cout << "  No se requiere intercambio" << endl;
            }
            cout << "\n[ESTADO DEL ARREGLO DESPUES DE LA PASADA " << (i + 1) << "]";
            mostrarArreglo();
            cout << "\n  Nota: Los primeros " << (i + 1) << " elementos ya estan ordenados" << endl;
        }
    }
    void mostrarAnalisisFinal() {
        cout << "\n\n--- ANALISIS FINAL ---" << endl;
        cout << "\n[ARREGLO FINAL ORDENADO]";
        mostrarArreglo();
        cout << "\n\n[ESTADISTICAS TOTALES]:" << endl;
        cout << "  * Total de comparaciones realizadas: " << totalComparaciones << endl;
        cout << "  * Total de intercambios realizados: " << totalIntercambios << endl;
        cout << "  * Numero de pasadas: " << (capacidad - 1) << endl;
        cout << "\n[VERIFICACION DEL ORDENAMIENTO]:" << endl;
        cout << "\nAgrupando por CATEGORIA:" << endl;
        string categoriaActual = "";
        for (int i = 0; i < capacidad; i++) {
            if (productos[i].categoria != categoriaActual) {
                categoriaActual = productos[i].categoria;
                cout << "\n  Categoria: " << categoriaActual << endl;
            }
            cout << "    [" << i << "] Precio:$" << fixed << setprecision(2) << productos[i].precio 
                 << " Peso:" << productos[i].peso << "kg - " << productos[i].descripcion << endl;
        }
    }
    ~GestorProductos() {
        delete[] productos;
    }
};
int main() {
    cout << "--- SELECTION SORT EN ARREGLO DE PRODUCTOS ---" << endl;
    cout << "    Ordenamiento con comparacion compuesta en 3 niveles" << endl;
    // Crear gestor con 8 productos
    GestorProductos gestor(8);
    cout << "\n[CONSTRUCCION DEL ARREGLO DE PRODUCTOS]" << endl;
    cout << "Agregando productos con diferentes categorias, precios y pesos..." << endl;
    // Agregar productos con datos variados para demostrar ordenamiento compuesto
    // Nota: algunos tienen misma categoria y precio para demostrar el tercer criterio
    gestor.agregarProducto(0, 101, "Laptop HP", "Electronica", 2.5, 899.99);
    gestor.agregarProducto(1, 102, "Mesa de madera", "Muebles", 15.0, 299.50);
    gestor.agregarProducto(2, 103, "Mouse inalambrico", "Electronica", 0.15, 25.99);
    gestor.agregarProducto(3, 104, "Silla ergonomica", "Muebles", 8.5, 199.99);
    gestor.agregarProducto(4, 105, "Teclado mecanico", "Electronica", 0.8, 89.99);
    gestor.agregarProducto(5, 106, "Estante metalico", "Muebles", 12.0, 150.00);
    gestor.agregarProducto(6, 107, "Monitor 24 pulgadas", "Electronica", 4.2, 299.99);
    gestor.agregarProducto(7, 108, "Lampara LED", "Electronica", 0.5, 45.00);
    // Aplicar Selection Sort
    gestor.selectionSort();
    // Mostrar analisis final
    gestor.mostrarAnalisisFinal();
    return 0;
}