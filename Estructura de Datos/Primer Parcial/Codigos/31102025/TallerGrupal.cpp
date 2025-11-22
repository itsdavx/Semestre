#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

typedef string Nombre;
typedef int Edad;
typedef string Identificacion;

class Persona
{
private:
    Nombre nombre;
    Edad edad;
    Identificacion cedula;

public:
    Persona(Nombre nombre, Edad edad, Identificacion cedula)
    {
        this->nombre = nombre;
        this->edad = edad;
        this->cedula = cedula;
    }
    ~Persona() {}

    

    void mostrarPersona()
    {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "Identificacion: " << cedula << endl;
    }

    //Getters
    Edad getEdad() const
    {
        return edad;
    }   

};

// Funciones independientes

Persona registarPersona(Nombre &nombre, Edad &edad, Identificacion &cedula)
    {
        cout << "Ingrese el nombre: ";
        getline(cin, nombre);
        cout << "Ingrese la edad: ";
        cin >> edad;
        cin.ignore();
        cout << "Ingrese la identificacion: ";
        getline(cin, cedula);

        return Persona(nombre, edad, cedula);
    }


template <typename T>

class Lista{
private:
    vector<T> listaPersonas;

    int sumarEdadesRecursivo(int index) const {
    if (index == elementos.size())
        return 0;

    return elementos.at(index).getEdad() + sumarEdadesRecursivo(index + 1);
}


public:
    Lista() {}
    ~Lista() {}

    void agregarElemento(const T &elemento)
    {
        listaPersonas.push_back(elemento);
    }


}
