#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

int main()
{
    vector<int> valores = {10, 20, 30, 40, 50};

    try
    {
        for (int i = 0; i <= valores.size(); i++)
        {
            cout << "Elemento en posicion " << i << ": " << valores.at(i) << endl;
        }
    }
    catch (const out_of_range &e)
    {
        cout << "Error: Intentaste acceder a una posicion inexistente" << endl;
    }

    return 0;
}