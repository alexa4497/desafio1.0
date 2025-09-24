#include "librerias.h"

int main() {
    const char* nombreArchivo = "archivo.txt";

    // Leer el archivo
    char* contenido = leerArchivo(nombreArchivo);

    if (!contenido) {
        cout << "No se pudo leer el archivo." << endl;
        return 1;
    }

    // Identificar tipo de compresión
    char* tipoCompresion = identificarTipoCompresion(contenido);

    cout << "Contenido del archivo:" << endl;
    cout << contenido << endl;
    cout << "\nTipo de compresión detectado: " << tipoCompresion << endl;

    // Liberar memoria
    delete[] contenido;
    delete[] tipoCompresion;

    return 0;
}
