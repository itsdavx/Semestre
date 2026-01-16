#include <iostream>

using namespace std;

void backtracking(solucion_parcial){
    if(solucion_completa){
        mostrar_solucion();
        return;
    }

    for(cada opcion posible){
        if(opcion_valida){
            agregar_opcion();
            backtracking(solucion_parcial);
            quitar_opcion();
        }
    }
}