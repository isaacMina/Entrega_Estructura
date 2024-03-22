#include <iostream>
#include <stdlib.h>

using namespace std;

struct Cliente {
    int numerocuenta;
    int tipoCuenta; 
    Cliente* sig;
};

Cliente *FIFO_tradicional = NULL, *FIFO_preferencial = NULL;
Cliente *firstIn_tradicional = NULL, *firstIn_preferencial = NULL;
Cliente *firstOut_tradicional = NULL, *firstOut_preferencial = NULL;
int turno_tradicional = 1, turno_preferencial = 1;

void registrarCliente() {
    Cliente* nuevoCliente = (struct Cliente*) malloc(sizeof(struct Cliente));
    cout << "Ingrese su numero de cuenta: ";
    cin >> nuevoCliente->numerocuenta;
    cout << "Tipo de cuenta (1: Preferencial, 2: Tradicional): ";
    cin >> nuevoCliente->tipoCuenta;
    nuevoCliente->sig = NULL;

    if (nuevoCliente->tipoCuenta == 1) {
        if (FIFO_preferencial == NULL) {
            FIFO_preferencial = nuevoCliente;
            firstIn_preferencial = FIFO_preferencial;
        } else {
            firstOut_preferencial = FIFO_preferencial;
            while (firstOut_preferencial->sig != NULL) {
                firstOut_preferencial = firstOut_preferencial->sig;
            }
            firstOut_preferencial->sig = nuevoCliente;
        }
        turno_preferencial++;
    } else if (nuevoCliente->tipoCuenta == 2) {
        if (FIFO_tradicional == NULL) {
            FIFO_tradicional = nuevoCliente;
            firstIn_tradicional = FIFO_tradicional;
        } else {
            firstOut_tradicional = FIFO_tradicional;
            while (firstOut_tradicional->sig != NULL) {
                firstOut_tradicional = firstOut_tradicional->sig;
            }
            firstOut_tradicional->sig = nuevoCliente;
        }
        turno_tradicional++;
    }

    
    if (FIFO_tradicional != NULL && FIFO_preferencial != NULL) {
        int count_tradicional = 0;
        Cliente* temp_tradicional = FIFO_tradicional;
        while (temp_tradicional != NULL) {
            count_tradicional++;
            temp_tradicional = temp_tradicional->sig;
        }

        int count_preferencial = 0;
        Cliente* temp_preferencial = FIFO_preferencial;
        while (temp_preferencial != NULL) {
            count_preferencial++;
            temp_preferencial = temp_preferencial->sig;
        }

        if (count_tradicional >= 5 && count_preferencial <= 2) {
            Cliente* temp = FIFO_tradicional;
            FIFO_tradicional = FIFO_tradicional->sig;
            temp->sig = FIFO_preferencial;
            FIFO_preferencial = temp;
            turno_tradicional--;
        }
    }
}

void atenderCliente() {
    if (FIFO_preferencial != NULL) {
        Cliente* temp = FIFO_preferencial;
        FIFO_preferencial = FIFO_preferencial->sig;
        free(temp);
        turno_preferencial--;
    } else if (FIFO_tradicional != NULL) {
        Cliente* temp = FIFO_tradicional;
        FIFO_tradicional = FIFO_tradicional->sig;
        free(temp);
        turno_tradicional--;
    }
}

void eliminarClienteTrad() {
    if (FIFO_tradicional != NULL && FIFO_preferencial != NULL) {
        Cliente* temp_tradicional = FIFO_tradicional;
        FIFO_tradicional = FIFO_tradicional->sig;
        free(temp_tradicional);
        turno_tradicional--;
    }
}

void visualizarFilas() {
    cout << "\nClientes en la fila tradicional:\n";
    Cliente* temp_tradicional = FIFO_tradicional;
    int contador = 1;
    while (temp_tradicional != NULL) {
        cout << contador << ". " << temp_tradicional->numerocuenta << endl;
        contador++;
        temp_tradicional = temp_tradicional->sig;
    }

    cout << "\nClientes en la fila preferencial:\n";
    Cliente* temp_preferencial = FIFO_preferencial;
    contador = 1;
    while (temp_preferencial != NULL) {
        cout << contador << ". " << temp_preferencial->numerocuenta << endl;
        contador++;
        temp_preferencial = temp_preferencial->sig;
    }
}

int main() {
    int opcion;
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Registrar Cliente\n";
        cout << "2. Atender Cliente\n";
        cout << "3. Visualizar Filas\n";
        cout << "4. Salir\n";
        cout << "Ingrese la opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCliente();
                break;
            case 2:
                atenderCliente();
                break;
            case 3:
                visualizarFilas();
                break;
            case 4:
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}