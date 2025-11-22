#include <iostream>
using namespace std;

// Estructura lista simple

struct NodoSimple
{
	int dato;
	NodoSimple *siguiente;
};

// Estructura lista doble

struct NodoDoble
{
	int dato;
	NodoDoble *siguiente;
	NodoDoble *anterior;
};

// Estructura lista circular

struct NodoCircular
{
	int dato;
	NodoCircular *siguiente;
};

// Funcion lista Simple

void insertarSimple(NodoSimple *&cabeza, int valor)
{
	NodoSimple *nuevo = new NodoSimple();
	nuevo->dato = valor;
	nuevo->siguiente = cabeza;
	cabeza = nuevo;
}

void mostrarSimple(NodoSimple *cabeza)
{
	cout << "Lista Simple-Enlazada: ";
	NodoSimple *actual = cabeza;
	while (actual != nullptr)
	{
		cout << actual->dato << " -> ";
		actual = actual->siguiente;
	}
	cout << "Null\n";
}

// Funcion lista Doble

void insertarDoble(NodoDoble *&cabeza, int valor)
{
	NodoDoble *nuevo = new NodoDoble();
	nuevo->dato = valor;
	nuevo->siguiente = cabeza;
	nuevo->anterior = nullptr;
	if (cabeza != nullptr)
	{
		cabeza->anterior = nuevo;
	}
	cabeza = nuevo;
}

void mostrarDoble(NodoDoble *cabeza)
{
    cout << "Lista Doble-Enlazada hacia adelante: ";
    NodoDoble *actual = cabeza;
    NodoDoble *ultimo = nullptr;
    while (actual != nullptr)
    {
        cout << actual->dato << " <-> ";
        ultimo = actual;
        actual = actual->siguiente;
    }
    cout << "Null\n";

    // Mostrar hacia atrás
    cout << "Lista Doble-Enlazada hacia atras: ";
    actual = ultimo;
    while (actual != nullptr)
    {
        cout << actual->dato << " <-> ";
        actual = actual->anterior;
    }
    cout << "Null\n";
}

// Funcion lista Circular

void insertarCircular(NodoCircular *&cabeza, int valor)
{
	NodoCircular *nuevo = new NodoCircular();
	nuevo->dato = valor;
	if (cabeza == nullptr)
	{
		cabeza = nuevo;
		nuevo->siguiente = cabeza;
	}
	else
	{
		NodoCircular *actual = cabeza;
		while (actual->siguiente != cabeza)
		{
			actual = actual->siguiente;
		}
		actual->siguiente = nuevo;
		nuevo->siguiente = cabeza;
	}
}

void mostrarCircular(NodoCircular *cabeza)
{
	if (cabeza == nullptr)
	{
		cout << "La lista circular esta vacia.\n";
		return;
	}
	cout << "Lista Circular: ";
	NodoCircular *actual = cabeza;
	do
	{
		cout << actual->dato << " -> ";
		actual = actual->siguiente;
	} while (actual != cabeza);
	cout << "Vuelve al inicio\n";
}

// Funcion Circular Doble

void insertarCircularDoble(NodoDoble *&cabeza, int valor)
{
	NodoDoble *nuevo = new NodoDoble();
	nuevo->dato = valor;
	if (cabeza == nullptr)
	{
		cabeza = nuevo;
		nuevo->siguiente = cabeza;
		nuevo->anterior = cabeza;
	}
	else
	{
		NodoDoble *ultimo = cabeza->anterior;
		ultimo->siguiente = nuevo;
		nuevo->anterior = ultimo;
		nuevo->siguiente = cabeza;
		cabeza->anterior = nuevo;
	}
}

void mostrarCircularDoble(NodoDoble *cabeza)
{
	if (cabeza == nullptr)
	{
		cout << "La lista circular doble esta vacia.\n";
		return;
	}
	cout << "Lista Circular Doble hacia adelante: ";
	NodoDoble *actual = cabeza;
	do
	{
		cout << actual->dato << " <-> ";
		actual = actual->siguiente;
	} while (actual != cabeza);
	cout << "Vuelve al inicio\n";

	cout << "Lista Circular Doble hacia atras: ";
	actual = cabeza->anterior;
	do
	{
		cout << actual->dato << " <-> ";
		actual = actual->anterior;
	} while (actual != cabeza->anterior);
	cout << "(vuelve al inicio)\n";
}

void mostrarMenu()
{
	cout << "________MENU________" << endl;
	cout << "1. Insertar Lista Enlazada" << endl;
	cout << "2. Mostrar Lista Enlazada" << endl;
	cout << "3. Insertar Lista Doble Enlazada" << endl;
	cout << "4. Mostrar Lista Doble Enlazada" << endl;
	cout << "5. Insertar Lista Circular" << endl;
	cout << "6. Mostrar Lista Circular" << endl;
	cout << "7. Insertar Lista Circular Doble" << endl;
	cout << "8. Mostrar Lista Circular Doble" << endl;
	cout << "9. Salir " << endl;

	cout << "Ingresa la opcion deseada: ";
}

int main()
{
	int opcion;

	// Nodos vacios
	NodoSimple *cabezaSimple = nullptr;
	NodoDoble *cabezaDoble = nullptr;
	NodoCircular *cabezaCircular = nullptr;

	do
	{
		mostrarMenu();
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			cout << "_____Insertar Lista Enlazada_____" << endl;
			{
				int valor;
				cout << "Ingrese un valor entero a insertar: ";
				if (!(cin >> valor))
				{
					// Si la entrada no es válida, limpiar cin y avisar
					cin.clear();
					cout << "Entrada no valida. Vuelva a intentarlo." << endl;
				}
				else
				{
					insertarSimple(cabezaSimple, valor);
					cout << "Valor insertado en la lista simple." << endl;
				}
			}
			cout << "_________________________________" << endl;
			break;
		case 2:
			cout << "_____Mostrar Lista Enlazada_____" << endl;
			mostrarSimple(cabezaSimple);
			cout << "_________________________________" << endl;
			break;
		case 3:
			cout << "_____Insertar Lista Doble Enlazada_____" << endl;
			{
				int valor;
				cout << "Ingrese un valor entero a insertar: ";
				if (!(cin >> valor))
				{
					// Si la entrada no es válida, limpiar cin y avisar
					cin.clear();
					cout << "Entrada no valida. Vuelva a intentarlo." << endl;
				}
				else
				{
					insertarDoble(cabezaDoble, valor);
					cout << "Valor insertado en la lista doble." << endl;
				}
			}
			cout << "_______________________________________" << endl;
			break;
		case 4:
			cout << "_____Mostrar Lista Doble Enlazada_____" << endl;
			mostrarDoble(cabezaDoble);
			cout << "______________________________________" << endl;
			break;
		case 5:
			cout << "_____Insertar Lista Circular_____" << endl;
			{
				int valor;
				cout << "Ingrese un valor entero a insertar: ";
				if (!(cin >> valor))
				{
					// Si la entrada no es válida, limpiar cin y avisar
					cin.clear();
					cout << "Entrada no valida. Vuelva a intentarlo." << endl;
				}
				else
				{
					insertarCircular(cabezaCircular, valor);
					cout << "Valor insertado en la lista circular." << endl;
				}
			}
			cout << "_________________________________" << endl;
			break;
		case 6:
			cout << "_____Mostrar Lista Circular_____" << endl;
			mostrarCircular(cabezaCircular);
			cout << "_________________________________" << endl;
			break;
		case 7:
			cout << "_____Insertar Lista Circular Doble_____" << endl;
			{
				int valor;
				cout << "Ingrese un valor entero a insertar: ";
				if (!(cin >> valor))
				{
					// Si la entrada no es válida, limpiar cin y avisar
					cin.clear();
					cout << "Entrada no valida. Vuelva a intentarlo." << endl;
				}
				else
				{
					insertarCircularDoble(cabezaDoble, valor);
					cout << "Valor insertado en la lista circular doble." << endl;
				}
			}
			cout << "______________________________________" << endl;
			break;
		case 8:
			cout << "_____Mostrar Lista Circular Doble_____" << endl;
			mostrarCircularDoble(cabezaDoble);
			cout << "______________________________________" << endl;
			break;
		case 9:
			cout << "Saliendo del programa..." << endl;
			break;
		default:
			cout << "Ingresar una opcion valida" << endl;
			break;
		}
	} while (opcion != 9);
}