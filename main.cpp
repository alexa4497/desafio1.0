#include "librerias.h"
#include <iostream>

using namespace std;

int main() {
    int cantPistas = 0;
    cout << "Ingrese la cantidad de archivos a desencriptar: ";
    cin >> cantPistas;
    for (int i = 0; i < cantPistas; i++) {
        procesarArchivo();
    }
    return 0;
}
