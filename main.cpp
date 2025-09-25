#include "librerias.h"
#include <direct.h>

int main() {
    char* contenido = NULL;
    int tamanoContenido = 0;

    cout << "=== Lector de Archivos Encriptados ===" << endl;

    // Verificar la ubicación actual
    char directorioActual[256];
    if (getcwd(directorioActual, sizeof(directorioActual)) != NULL) {
        cout << "Directorio actual: " << directorioActual << endl;
    }

    // Leer archivo encriptado
    if (leerArchivoEncriptadoCompleto(&contenido, &tamanoContenido)) {
        cout << "\nContenido leido exitosamente!" << endl;
        cout << "Tamaño total: " << tamanoContenido << " caracteres" << endl;

        cout << "\nPrimeros 100 caracteres del archivo:" << endl;
        cout << "----------------------------------------" << endl;

        // Mostrar primeros 100 caracteres
        for (int i = 0; i < 100 && i < tamanoContenido; i++) {
            cout << contenido[i];
        }
        cout << endl;
        cout << "----------------------------------------" << endl;

        delete[] contenido;
        cout << "Memoria liberada correctamente." << endl;
    } else {
        cout << "Error al leer el archivo." << endl;
    }
    system("pause");

    return 0;
}
