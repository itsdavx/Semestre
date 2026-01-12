#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Producto
{
    int codigo;
    string descripcion;
    float precio;
    int tipo;
};

const int ORDER = 4;

// Nodo del B+

struct NodoBMas
{
    bool esHoja;
    vector<int> claves;                       // claves ordenadas
    vector<NodoBMas*> hijos;                 // punteros a hijos (solo si no es hoja)
    vector<vector<Producto*>> valores;        // solo en hojas: para cada clave, lista de punteros a Producto
    NodoBMas* siguiente;                     // enlace a la siguiente hoja (solo en hojas)

    NodoBMas(bool hoja) : esHoja(hoja), siguiente(nullptr) {}
};


class BPlusTree
{
private:
    NodoBMas* raiz;

    // Buscar la hoja donde debe estar la clave (no crea)
    NodoBMas* buscarHoja(int clave)
    {
        if (!raiz) return nullptr;
        NodoBMas* nodo = raiz;
        while (!nodo->esHoja)
        {
            // encuentra el primer indice i tal que clave < claves[i], si ninguno, ir al ultimo hijo
            size_t i = 0;
            while (i < nodo->claves.size() && clave >= nodo->claves[i]) i++;
            nodo = nodo->hijos[i];
        }
        return nodo;
    }

    // insertar en hoja sin split (asume que hay espacio)
    void insertarEnHojaSinSplit(NodoBMas* hoja, int clave, Producto* producto)
    {
        // ubicar posicion
        auto it = lower_bound(hoja->claves.begin(), hoja->claves.end(), clave);
        size_t pos = it - hoja->claves.begin();

        if (it != hoja->claves.end() && *it == clave)
        {
            // clave ya existe: anadir producto a la lista correspondiente
            hoja->valores[pos].push_back(producto);
        }
        else
        {
            // insertar clave y su vector de valores
            hoja->claves.insert(hoja->claves.begin() + pos, clave);
            hoja->valores.insert(hoja->valores.begin() + pos, vector<Producto*>{producto});
        }
    }

    // split de hoja: hoja -> (izq, der), retorna par (nuevaClavePromovida, nuevoNodoDerecho)
    pair<int, NodoBMas*> splitHoja(NodoBMas* hoja)
    {
        size_t total = hoja->claves.size();
        size_t medio = total / 2; // dividir en medio, izq tiene medio claves

        NodoBMas* derecha = new NodoBMas(true);

        // mover desde medio hasta el final a la derecha
        derecha->claves.assign(hoja->claves.begin() + medio, hoja->claves.end());
        derecha->valores.assign(hoja->valores.begin() + medio, hoja->valores.end());

        // recortar la hoja original
        hoja->claves.erase(hoja->claves.begin() + medio, hoja->claves.end());
        hoja->valores.erase(hoja->valores.begin() + medio, hoja->valores.end());

        // enlaces de hojas
        derecha->siguiente = hoja->siguiente;
        hoja->siguiente = derecha;

        // la clave promovida al padre es la primera clave de la hoja derecha (convencion B+)
        int clavePromovida = derecha->claves.front();
        return {clavePromovida, derecha};
    }

    // insertar recursivamente (o iterativo con stack). Aqui implemento iterativo:
    void insertarClave(int clave, Producto* producto)
    {
        if (!raiz)
        {
            // crear hoja nueva
            raiz = new NodoBMas(true);
            raiz->claves.push_back(clave);
            raiz->valores.push_back(vector<Producto*>{producto});
            return;
        }

        // encontrar hoja donde debe ir
        NodoBMas* hoja = buscarHoja(clave);
        insertarEnHojaSinSplit(hoja, clave, producto);

        // si overflow en hoja (mas de ORDER-1 claves), hacemos splits hacia arriba
        if ((int)hoja->claves.size() <= ORDER - 1) return;

        // Lista de pares (nodo, clavePromovida/nuevoHijo) para propagar hacia arriba
        NodoBMas* nodoActual = hoja;
        int clavePromovida;
        NodoBMas* nuevoHermano = nullptr;

        // split inicial de hoja
        auto p = splitHoja(nodoActual);
        clavePromovida = p.first;
        nuevoHermano = p.second;

        // Si la hoja era la raiz (y raiz es hoja), crear nueva raiz interna
        if (nodoActual == raiz)
        {
            NodoBMas* nuevaRaiz = new NodoBMas(false);
            nuevaRaiz->claves.push_back(clavePromovida);
            nuevaRaiz->hijos.push_back(nodoActual);
            nuevaRaiz->hijos.push_back(nuevoHermano);
            raiz = nuevaRaiz;
            return;
        }

        // recorrer hacia arriba: necesitamos encontrar padres. Como no guardamos padre,
        // hacemos una busqueda desde la raiz para hallar el padre de nodoActual, y asi sucesivamente.
        while (true)
        {
            // encontrar el padre de nodoActual
            NodoBMas* padre = encontrarPadre(raiz, nodoActual);
            if (!padre)
            {
                // deberia pasar solo si nodoActual es raiz, pero ya cubrimos ese caso
                break;
            }

            // insertar clavePromovida y nuevoHermano en padre
            // posicion: primera clave > clavePromovida
            auto it = upper_bound(padre->claves.begin(), padre->claves.end(), clavePromovida);
            size_t pos = it - padre->claves.begin();

            padre->claves.insert(padre->claves.begin() + pos, clavePromovida);
            // insertar hijo derecho despues de la posicion pos
            // encontrar posicion del hijo nodoActual dentro de padre->hijos
            size_t idxHijo = 0;
            while (idxHijo < padre->hijos.size() && padre->hijos[idxHijo] != nodoActual) idxHijo++;
            // insertar el nuevoHermano despues de idxHijo
            padre->hijos.insert(padre->hijos.begin() + idxHijo + 1, nuevoHermano);

            // si no hay overflow en padre, hemos terminado
            if ((int)padre->claves.size() <= ORDER - 1) break;

            // overflow en padre: split interno
            // convencion: dividir claves y hijos; promovemos la clave en posicion medio (claves[medio]) hacia arriba,
            // pero en B+ las claves internas son guias. Aqui hacemos:
            size_t totalClaves = padre->claves.size();
            size_t medio = totalClaves / 2; // indice de clave promovida
            int claveSubida = padre->claves[medio];

            // crear nuevo hermano interno
            NodoBMas* nuevoInterno = new NodoBMas(false);

            // mover claves derechas (desde medio+1) a nuevoInterno
            nuevoInterno->claves.assign(padre->claves.begin() + medio + 1, padre->claves.end());
            // mover hijos derechas (desde medio+1) a nuevoInterno: hijos.size() = claves.size()+1
            nuevoInterno->hijos.assign(padre->hijos.begin() + medio + 1, padre->hijos.end());

            // recortar padre
            padre->claves.erase(padre->claves.begin() + medio, padre->claves.end());
            padre->hijos.erase(padre->hijos.begin() + medio + 1, padre->hijos.end());

            // si padre era la raiz, crear nueva raiz que contenga claveSubida
            if (padre == raiz)
            {
                NodoBMas* nuevaRaiz = new NodoBMas(false);
                nuevaRaiz->claves.push_back(claveSubida);
                nuevaRaiz->hijos.push_back(padre);
                nuevaRaiz->hijos.push_back(nuevoInterno);
                raiz = nuevaRaiz;
                break;
            }
            else
            {
                // propagar hacia arriba: ahora nodoActual = padre, nuevoHermano = nuevoInterno, clavePromovida = claveSubida
                nodoActual = padre;
                clavePromovida = claveSubida;
                nuevoHermano = nuevoInterno;
                // continuar el while para insertar en el padre superior
            }
        } // fin while
    }

    // auxiliar: encontrar padre del nodo dado (recorre desde nodoActual = cur)
    NodoBMas* encontrarPadre(NodoBMas* inicio, NodoBMas* hijo)
    {
        if (!inicio || inicio->esHoja) return nullptr;
        // revisar si alguno de los hijos directos es el 'hijo'
        for (NodoBMas* c : inicio->hijos)
            if (c == hijo) return inicio;

        // sino, bajar recursivamente por los hijos que puedan contenerlo
        for (NodoBMas* c : inicio->hijos)
        {
            NodoBMas* posible = encontrarPadre(c, hijo);
            if (posible) return posible;
        }
        return nullptr;
    }

public:
    BPlusTree() : raiz(nullptr) {}

    // insertar producto en indice por clave 'tipo'
    void insertar(int clave, Producto* producto)
    {
        insertarClave(clave, producto);
    }

    // buscar productos por clave exacta: devuelve vector de punteros a Producto (vacio si no existe)
    vector<Producto*> buscar(int clave)
    {
        vector<Producto*> resultado;
        NodoBMas* hoja = buscarHoja(clave);
        if (!hoja) return resultado;
        auto it = lower_bound(hoja->claves.begin(), hoja->claves.end(), clave);
        size_t pos = it - hoja->claves.begin();
        if (it != hoja->claves.end() && *it == clave)
        {
            // copiar punteros a resultado
            for (Producto* p : hoja->valores[pos]) resultado.push_back(p);
        }
        return resultado;
    }

    // recorrer todas las hojas y devolver todos los productos (por si quieres mostrar todo ordenado por clave)
    vector<Producto*> listarTodosOrdenados()
    {
        vector<Producto*> out;
        if (!raiz) return out;
        // encontrar la hoja mas a la izquierda
        NodoBMas* nodo = raiz;
        while (!nodo->esHoja) nodo = nodo->hijos.front();

        // recorrer hojas por 'siguiente'
        for (; nodo != nullptr; nodo = nodo->siguiente)
        {
            for (size_t i = 0; i < nodo->claves.size(); ++i)
                for (Producto* p : nodo->valores[i])
                    out.push_back(p);
        }
        return out;
    }

    // destructor recursivo (liberar memoria). No elimina productos apuntados (no era creado aqui)
    void liberarNodo(NodoBMas* nodo)
    {
        if (!nodo) return;
        if (!nodo->esHoja)
        {
            for (NodoBMas* h : nodo->hijos) liberarNodo(h);
        }
        delete nodo;
    }

    ~BPlusTree()
    {
        liberarNodo(raiz);
        raiz = nullptr;
    }
};

// CSV y utilidades
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

int main()
{
    string archivo = "productos.csv";

    int n = contarLineas(archivo);

    if (n == 0)
    {
        cout << "No se pudo leer el archivo o esta vacio.\n";
        return 0;
    }

    // reservar inventario dinamico y cargar CSV
    Producto *inventario = new Producto[n];
    cargarCSV(inventario, n, archivo);

    // Crear indice B+ y llenar con punteros a productos (clave = tipo)
    BPlusTree indice;
    for (int i = 0; i < n; ++i)
    {
        indice.insertar(inventario[i].tipo, &inventario[i]);
    }

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
        {
            cout << "\n____________ INVENTARIO COMPLETO (ordenado por tipo) ____________\n"
                 << endl;
            vector<Producto*> todos = indice.listarTodosOrdenados();
            for (Producto* p : todos)
                mostrarProducto(*p);
            break;
        }

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

            vector<Producto*> encontrados = indice.buscar(tipo);

            if (encontrados.empty())
            {
                cout << "No hay productos de ese tipo.\n";
            }
            else
            {
                cout << "\n____________PRODUCTOS DEL TIPO " << tipo << " ____________\n"<<endl ;
                for (Producto* p : encontrados)
                    mostrarProducto(*p);
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
