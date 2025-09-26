#include <cstdio>
#include <fstream>
#include <cstring>
#include <vector>
#include "librerias.h"

// Ruta absoluta fija
const char* RUTA_ABSOLUTA = "C:\\Users\\alexa\\Desktop\\desafio1_0\\datasetDesarrollo\\";


// Función para leer la pista y almacenar los punteros
char** leerPistaEnPunteros(const char* nombreArchivo, int& longitud) {
    char rutaCompleta[200];

    strcpy(rutaCompleta, RUTA_ABSOLUTA);
    strcat(rutaCompleta, nombreArchivo);

    std::ifstream archivo(rutaCompleta, std::ios::in | std::ios::binary | std::ios::ate);
    if (!archivo.is_open()) {
        printf("Error: No se pudo abrir el archivo de la pista en la ruta %s\n", rutaCompleta);
        longitud = 0;
        return nullptr;
    }

    longitud = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    char* datosPista = new char[longitud + 1];
    archivo.read(datosPista, longitud);
    datosPista[longitud] = '\0';

    char** punterosPista = new char*[longitud];
    for (int i = 0; i < longitud; ++i) {
        punterosPista[i] = &datosPista[i];
    }

    archivo.close();
    return punterosPista;
}

// Función principal de procesamiento
void procesarPista() {
    char nombreArchivo[100];
    puts("Por favor, ingrese el nombre del archivo de la pista (ej. pista1.txt): ");
    scanf("%s", nombreArchivo);

    int longitudPista = 0;
    char** punterosPista = leerPistaEnPunteros(nombreArchivo, longitudPista);

    if (punterosPista == nullptr || longitudPista == 0) {
        puts("Error: La pista no pudo ser leída o está vacía.");
        return;
    }


    mostrarCompresion(punterosPista,longitudPista);

    delete[] punterosPista[0];
    delete[] punterosPista;
}

// Función para mostrar el texto plano
void mostrarTextoPlano(char** pista, int longitud) {
    puts("Texto plano leido: ");
    for (int i = 0; i < longitud; ++i) {
        putchar(*pista[i]);
    }
    puts("");
}

char* comprimirConRLE(char** pista, int longitud, int* longitudComprimida) {
    if (longitud <= 0) {
        *longitudComprimida = 0;
        return NULL;
    }

    // Se asigna memoria dinámicamente. Un tamaño máximo de dos veces la longitud original es un valor seguro.
    char* datosComprimidos = (char*)malloc(longitud * 2);
    int indiceComprimido = 0;
    int i = 0;

    // Recorre la pista para encontrar repeticiones
    while (i < longitud) {
        char caracterActual = *pista[i];
        int contador = 1;
        int j = i + 1;

        while (j < longitud && *pista[j] == caracterActual) {
            contador++;
            j++;
        }

        if (contador > 1) {
            // Si el caracter se repite, guarda el contador y luego el caracter
            datosComprimidos[indiceComprimido++] = (char)('0' + contador);
            datosComprimidos[indiceComprimido++] = caracterActual;
        } else {
            // Si no se repite, guarda solo el caracter
            datosComprimidos[indiceComprimido++] = caracterActual;
        }

        i = j;
    }

    // Ajusta el tamaño del arreglo al tamaño real de los datos comprimidos
    *longitudComprimida = indiceComprimido;
    datosComprimidos = (char*)realloc(datosComprimidos, *longitudComprimida);

    return datosComprimidos;
}

void mostrarCompresionRLE(char* comprimido, int longitud) {
    puts("Resultado de la compresion RLE: ");
    for (int i = 0; i < longitud; ++i) {
        putchar(comprimido[i]);
    }
    puts("");
}

// Integracion en tu funcion principal de procesamiento
void mostrarCompresion(char** pista, int longitud) {
    // 1. Muestra el texto plano primero
    mostrarTextoPlano(pista, longitud);

    // 2. Comprime con LZ78 y muestra el resultado

    // 3. Comprime con RLE y muestra el resultado
    int longitudComprimida = 0;
    char* datosComprimidos = comprimirConRLE(pista, longitud, &longitudComprimida);

    if (datosComprimidos != NULL) {
        mostrarCompresionRLE(datosComprimidos, longitudComprimida);
        free(datosComprimidos);
    }
}

//FUNCIONES LZ78

