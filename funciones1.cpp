#include "librerias.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Función para leer archivo y devolver puntero al contenido
char* leerArchivo(const char* nombreArchivo) {
    cout << "Intentando leer: " << nombreArchivo << endl;

    ifstream archivo(nombreArchivo, ios::binary | ios::ate);
    if (!archivo.is_open()) {
        cout << "ERROR: Fallo al abrir archivo para lectura" << endl;
        return nullptr;
    }

    streamsize tamano = archivo.tellg();
    if (tamano == 0) {
        archivo.close();
        return new char[1];
    }
    archivo.seekg(0, ios::beg);

    char* contenido = new char[tamano + 1];
    archivo.read(contenido, tamano);
    contenido[tamano] = '\0'; // Null-terminate the string

    archivo.close();
    cout << "Archivo leido exitosamente. Tamano: " << tamano << " bytes" << endl;
    return contenido;
}

// Función para identificar el método de compresión
void identificarMetodoCompresion(char* contenido) {
    if (contenido == nullptr || contenido[0] == '\0') {
        cout << "Contenido vacio." << endl;
        return;
    }

    int patronRLE = 0;
    int patronLZ78 = 0;

    char* ptr = contenido;

    // Contadores para evitar loops infinitos en casos malformados
    int maxIter = 100000;
    int iter = 0;

    while (*ptr != '\0' && iter < maxIter) {
        // Logica para RLE
        if (*(ptr+1) != '\0' && (*(ptr+1) >= '0' && *(ptr+1) <= '9')) {
            patronRLE++;
        }

        // Logica para LZ78
        if (*ptr == '(') {
            char* temp = ptr + 1;
            bool found_comma = false;
            bool found_number = false;
            bool found_char = false;

            while (*temp != '\0' && *temp != ')') {
                if (*temp >= '0' && *temp <= '9') {
                    found_number = true;
                } else if (*temp == ',') {
                    found_comma = true;
                } else if (found_comma) {
                    found_char = true;
                    // Avanzar temp para encontrar el ')'
                }
                temp++;
            }
            if (*temp == ')' && found_number && found_comma && found_char) {
                patronLZ78++;
                ptr = temp; // Mover el puntero principal despues del patron
            }
        }
        ptr++;
        iter++;
    }

    cout << "=== ANALISIS DE COMPRESION ===" << endl;
    cout << "Patrones RLE detectados: " << patronRLE << endl;
    cout << "Patrones LZ78 detectados: " << patronLZ78 << endl;

    if (patronRLE > patronLZ78) {
        cout << "METODO IDENTIFICADO: RLE (Run-Length Encoding)" << endl;
    } else if (patronLZ78 > patronRLE) {
        cout << "METODO IDENTIFICADO: LZ78" << endl;
    } else {
        cout << "METODO: NO SE PUDO IDENTIFICAR CLARAMENTE" << endl;
    }
    cout << "================================" << endl;
}

// La función iniciodescompresion sigue siendo la misma
void iniciodescompresion() {
    int cantidadArchivos;
    cout << "Ingrese la cantidad de archivos a analizar: ";
    cin >> cantidadArchivos;
    cin.ignore();

    vector<char*> nombresArchivos(cantidadArchivos);
    vector<char*> contenidosArchivos(cantidadArchivos);

    for (int i = 0; i < cantidadArchivos; i++) {
        char* nombre = new char[100];
        cout << "Ingrese el nombre del archivo " << i + 1 << ": ";

        char* ptr = nombre;
        char c;
        while (cin.get(c) && c != '\n') {
            *ptr = c;
            ptr++;
        }
        *ptr = '\0';

        nombresArchivos[i] = nombre;
        contenidosArchivos[i] = leerArchivo(nombre);

        if (contenidosArchivos[i] != nullptr) {
            cout << "Archivo leido correctamente" << endl;
            identificarMetodoCompresion(contenidosArchivos[i]);
        } else {
            cout << "Error leyendo archivo" << endl;
        }
        cout << endl;

        // Liberar memoria del contenido y el nombre
        delete[] contenidosArchivos[i];
        delete[] nombresArchivos[i];
    }
}
