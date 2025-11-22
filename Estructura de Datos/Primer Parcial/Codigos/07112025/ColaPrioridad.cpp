#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int data;
    int priority;
    Node* next;
};

struct PQueue {
    Node* head;
};

const int MAX_PRIORIDADES = 5;
bool prioridadesUsadas[MAX_PRIORIDADES] = {false};
int prioridadesDisponibles = MAX_PRIORIDADES;

int generarPrioridadAleatoria() {
    if (prioridadesDisponibles == 0) {
        // Reiniciar cuando todas las prioridades han sido usadas
        for (int i = 0; i < MAX_PRIORIDADES; i++) {
            prioridadesUsadas[i] = false;
        }
        prioridadesDisponibles = MAX_PRIORIDADES;
    }

    // Generar números hasta encontrar uno no usado
    int prioridad;
    do {
        prioridad = (rand() % MAX_PRIORIDADES) + 1;
    } while (prioridadesUsadas[prioridad - 1]);
    
    // Marcar la prioridad como usada
    prioridadesUsadas[prioridad - 1] = true;
    prioridadesDisponibles--;
    return prioridad;
}

void init(PQueue &p) {
    p.head = nullptr;
    srand(time(nullptr));
}

bool empty(const PQueue &q) {
    return q.head == nullptr;
}

void push(PQueue &q, int v,int p) {
    Node* n = new Node{v, p, nullptr};
    if (empty(q) || p > q.head->priority) {
        n->next = q.head;
        q.head = n;
        return;
    } else {
        Node* cur = q.head;
        while (cur->next && cur->next->priority >= p) {
            cur = cur->next;
        }
        n->next = cur->next;
        cur->next = n;
    }
}

bool pop(PQueue &q,int &outVal, int &outPri) {
    if (empty(q)) {
        return false;
    }
    Node* temp = q.head;
    outVal = temp->data;
    outPri = temp->priority;
    q.head = q.head->next;
    delete temp;
    return true;
}

int main() {
    srand(time(nullptr));
    
    PQueue pq;
    init(pq);

    cout << "Ingresa elementos:" << endl;
    for (int i = 0; i < 5; ++i) {
        int value;
        cout << "Valor del elemento " << (i + 1) << ": ";
        cin >> value;
        int priority = generarPrioridadAleatoria();
        cout << "Prioridad asignada: " << priority << endl;
        push(pq, value, priority);
    }

    int value, priority;
    while (pop(pq, value, priority)) {
        cout << "Value: " << value << ", Priority: " << priority << endl;
    }

    return 0;
}
