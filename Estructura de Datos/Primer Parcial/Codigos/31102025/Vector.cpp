#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;   

int main()
{
    vector<int> numeros = {5,10,15,20};

    try
    {
            cout << "Elemento en posicion 2: " << numeros.at(2) << endl;
            cout << "Elemento en posicion 10: " << numeros.at(10) << endl;
    }
    catch (const std::out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}