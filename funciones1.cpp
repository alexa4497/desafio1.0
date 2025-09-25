#include "librerias.h"

bool leerArchivoEncriptado(char nombreArchivo[], char** contenido, int* tamanoContenido) {
    char rutaCompleta[200];
    int i = 0;
    int caracter;
    int capacidad = 1024; // Capacidad inicial
    int tamano = 0;
    char* contenidoTemp = NULL;

    int pos = 0;

    while (nombreArchivo[i] != '\0' && i < 50) {
        rutaCompleta[pos + i] = nombreArchivo[i];
        i++;
    }
    rutaCompleta[pos + i] = '\0';

    FILE* archivo = fopen(rutaCompleta, "rb");
    if (archivo == NULL) {
        cout << "Error: No se pudo abrir el archivo " << rutaCompleta << endl;
        return false;
    }

    *contenido = new char[capacidad];
    if (*contenido == NULL) {
        cout << "Error: No se pudo asignar memoria" << endl;
        fclose(archivo);
        return false;
    }

    while ((caracter = fgetc(archivo)) != EOF) {
        // Si necesitamos más espacio, redimensionar
        if (tamano >= capacidad - 1) {
            capacidad *= 2;
            contenidoTemp = new char[capacidad];
            if (contenidoTemp == NULL) {
                cout << "Error: No se pudo redimensionar la memoria" << endl;
                delete[] *contenido;
                fclose(archivo);
                return false;
            }

            // Copiar contenido existente
            for (int k = 0; k < tamano; k++) {
                contenidoTemp[k] = (*contenido)[k];
            }

            // Liberar memoria anterior y asignar nueva
            delete[] *contenido;
            *contenido = contenidoTemp;
        }

        (*contenido)[tamano] = (char)caracter;
        tamano++;
    }

    (*contenido)[tamano] = '\0';

    fclose(archivo);

    *tamanoContenido = tamano;
    cout << "Archivo " << rutaCompleta << " leido exitosamente." << endl;
    cout << "Tamano del contenido: " << tamano << " caracteres" << endl;

    return true;
}


int obtenerNombreArchivo(char nombreArchivo[], int tamanoMaximo) {
    char caracter;
    int i = 0;

    cout << "Ingrese el nombre del archivo (ej: EncriptadoX): ";

    // Leer caracteres hasta encontrar salto de línea
    while ((caracter = getchar()) != '\n' && caracter != EOF && i < tamanoMaximo - 1) {
        nombreArchivo[i] = caracter;
        i++;
    }

    // Agregar carácter nulo al final
    nombreArchivo[i] = '\0';

    return i;
}

bool leerArchivoEncriptadoCompleto(char** contenido, int* tamanoContenido) {
    char nombreArchivo[100];

    int caracteresNombre = obtenerNombreArchivo(nombreArchivo, 100);
    if (caracteresNombre == 0) {
        cout << "Error: No se ingreso nombre de archivo" << endl;
        return false;
    }

    return leerArchivoEncriptado(nombreArchivo, contenido, tamanoContenido);
}
