#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Producto
{
    int codigo;
    string descripcion;
    float precio;
    int tipo;
};

//BUBBLE SORT  ------------------------
void bubbleSort(Producto *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].tipo > arr[j + 1].tipo)
                swap(arr[j], arr[j + 1]);
}

//BUSQUEDA BINARIA ---------------------------
int buscarBinarioTipo(Producto *arr, int n, int tipoBuscado)
{
    int inicio = 0, fin = n - 1;

    while (inicio <= fin)
    {
        int mid = (inicio + fin) / 2;

        if (arr[mid].tipo == tipoBuscado)
            return mid;

        if (arr[mid].tipo < tipoBuscado)
            inicio = mid + 1;
        else
            fin = mid - 1;
    }
    return -1;
}

// CSV-------------------------------
int contarLineas(const string &archivo)
{
    ifstream file(archivo);
    if (!file.is_open())
        return 0;

    string linea;
    int count = 0;

    while (getline(file, linea))
        if (!linea.empty())
            count++;

    return count;
}

void cargarCSV(Producto *arr, int n, const string &archivo)
{
    ifstream file(archivo);
    string linea;
    int index = 0;

    while (getline(file, linea) && index < n)
    {
        if (linea.empty())
            continue;

        stringstream ss(linea);
        string campo;

        // codigo
        getline(ss, campo, ',');
        arr[index].codigo = stoi(campo);

        // descripcion
        getline(ss, campo, ',');
        arr[index].descripcion = campo;

        // precio
        getline(ss, campo, ',');
        arr[index].precio = stof(campo);

        // tipo
        getline(ss, campo, ',');
        arr[index].tipo = stoi(campo);

        index++;
    }
}

void mostrarProducto(const Producto &p)
{
    cout << "Codigo: " << p.codigo << endl;
    cout << "Descripcion: " << p.descripcion << endl;
    cout << "Precio: $" << p.precio << endl;
    cout << "Tipo: " << p.tipo << "\n\n";
}

//MAIN---------------------------
int main()
{
    string archivo = "productos.csv";

    int n = contarLineas(archivo);

    if (n == 0)
    {
        cout << "No se pudo leer el archivo o esta vacio.\n";
        return 0;
    }

    Producto *inventario = new Producto[n];
    cargarCSV(inventario, n, archivo);

    // Ordenar por tipo
    bubbleSort(inventario, n);

    int opcion;

    do
    {
        cout << "\n____________MENU____________\n";
        cout << "1. Mostrar todos los productos\n";
        cout << "2. Buscar productos por tipo\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "\n____________ INVENTARIO COMPLETO ____________\n"
                 << endl;
            for (int i = 0; i < n; i++)
                mostrarProducto(inventario[i]);
            break;

        case 2:
        {
            int tipo;

            cout << "Lista de Tipos:" << endl;
            cout << "0 - Comida Rapida" << endl;
            cout << "1 - Dulces y Chocolates" << endl;
            cout << "2 - Lacteos" << endl;
            cout << "3 - Bebidas" << endl;
            cout << "4 - Enlatados" << endl;
            cout << "5 - Cereales y Granos" << endl;
            cout << "6 - Cuidado Personal" << endl;
            cout << "7 - Limpieza del Hogar" << endl;
            cout << "8 - Carnes y Aves" << endl;
            cout << "9 - Frutas y Verduras" << endl;
            cout << "10 - Accesorios" << endl;
            cout << "Ingrese tipo (0-10): ";
            cin >> tipo;

            if (tipo < 0 || tipo > 10)
            {
                cout << "Tipo invalido.\n";
                break;
            }

            int pos = buscarBinarioTipo(inventario, n, tipo);

            if (pos == -1)
            {
                cout << "No hay productos de ese tipo.\n";
            }
            else
            {
                // Retroceder hasta el primer elemento del tipo
                while (pos > 0 && inventario[pos - 1].tipo == tipo)
                    pos--;

                cout << "\n____________PRODUCTOS DEL TIPO " << tipo << " ____________\n"<<endl ;

                // Mostrar todos los consecutivos
                for (int i = pos; i < n && inventario[i].tipo == tipo; i++)
                    mostrarProducto(inventario[i]);
            }
        }
        break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    delete[] inventario;

    return 0;
}