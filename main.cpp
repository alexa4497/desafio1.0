#include "librerias.h"
#include <iostream>

using namespace std;
<<<<<<< HEAD

int main() {
    int cantPistas = 0;
    cout << "Ingrese la cantidad de archivos a desencriptar: ";
    cin >> cantPistas;
    for (int i = 0; i < cantPistas; i++) {
        procesarArchivo();
    }
    return 0;
=======
int main() {
    int cantPistas=0;
    cout << "Ingrese la cantidad de archivos a desencriptar: ";
    cin >> cantPistas ;
    for (int i=0; i < cantPistas;i++){
        procesarPista();
    }return 0;
     procesarPista();

>>>>>>> f3ed99dad48e677befa7e92b21440aaa31abb47e
}
