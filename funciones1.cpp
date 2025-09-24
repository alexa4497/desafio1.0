#include "librerias.h"


long obtenerTamanoArchivo(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::ate | ios::binary);
    if (!archivo.is_open()) {
        return -1;
    }
    long tamano = archivo.tellg();
    archivo.close();
    return tamano;
}

// Función para leer archivo de texto
char* leerArchivo(const char* nombreArchivo) {
    long tamano = obtenerTamanoArchivo(nombreArchivo);
    if (tamano == -1) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return nullptr;
    }


    char* contenido = new char[tamano + 1];

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        delete[] contenido;
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return nullptr;
    }

    archivo.read(contenido, tamano);
    contenido[tamano] = '\0'; // Terminar la cadena

    archivo.close();
    return contenido;
}

// Función para identificar tipo de compresión
char* identificarTipoCompresion(const char* contenido) {
    if (!contenido) return nullptr;

    int longitud = strlen(contenido);
    bool esRLE = false;
    bool esLZ78 = false;

    // Detectar RLE: busca patrones como "3A" o "5B" (número seguido de carácter)
    for (int i = 0; i < longitud - 1; i++) {
        if (isdigit(contenido[i]) && isalpha(contenido[i + 1])) {
            esRLE = true;
            break;
        }
    }

    // Detectar LZ78: busca patrones como diccionario con índices
    if (strstr(contenido, "dict") != nullptr ||
        strstr(contenido, "index") != nullptr ||
        (strchr(contenido, '(') != nullptr && strchr(contenido, ')') != nullptr)) {
        esLZ78 = true;
    }

    char* resultado = new char[20];
    if (esRLE) {
        strcpy(resultado, "RLE");
    } else if (esLZ78) {
        strcpy(resultado, "LZ78");
    } else {
        strcpy(resultado, "DESCONOCIDO");
    }

    return resultado;
}
