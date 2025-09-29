#include <stdio.h>
#include <stdlib.h>
#include "librerias.h"

const char* RUTA_RELATIVA = "Encriptadosx/";

char* leerArchivo(const char* nombreArchivo, int* tamanioArchivo) {
    char rutaCompleta[256];

    int len_ruta = strlen(RUTA_RELATIVA);
    int len_nombre = strlen(nombreArchivo);

    if (len_ruta + len_nombre >= sizeof(rutaCompleta) - 1) {
        printf("Error: La ruta completa es demasiado larga.\n");
        *tamanioArchivo = 0;
        return NULL;
    }

    strcpy(rutaCompleta, RUTA_RELATIVA);
    strcat(rutaCompleta, nombreArchivo);

    FILE* archivo = fopen(rutaCompleta, "rb");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo en la ruta %s\n", rutaCompleta);
        *tamanioArchivo = 0;
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    *tamanioArchivo = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char* arrayArchivo = (char*)malloc(*tamanioArchivo);
    if (arrayArchivo == NULL) {
        printf("Error: Fallo la asignacion de memoria.\n");
        *tamanioArchivo = 0;
        fclose(archivo);
        return NULL;
    }

    size_t elementosLeidos = fread(arrayArchivo, 1, *tamanioArchivo, archivo);
    fclose(archivo);

    if (elementosLeidos != *tamanioArchivo) {
        printf("Advertencia: Se leyeron %zu bytes, pero el tamaño esperado era %d.\n", elementosLeidos, *tamanioArchivo);
    }

    return arrayArchivo;
}

// FUNCIÓN procesarArchivo ORIGINAL
void procesarArchivo() {
    char nombreArchivo[100];
    int tamComprimido = 0;
    int tamDescomprimido = 0;

    char* arrayComprimido = NULL;
    char* arrayDescomprimido = NULL;

    printf("Ingrese el nombre del archivo : ");

    if (scanf("%99s", nombreArchivo) != 1) {
        printf("Error al leer la entrada.\n");
        return;
    }

    arrayComprimido = leerArchivo(nombreArchivo, &tamComprimido);

    if (arrayComprimido == NULL || tamComprimido == 0) {
        if (tamComprimido == 0) {
            printf("Error: archivo vacio o no pudo ser leido.\n");
        }
        return;
    }

    printf("\n");
    printf("Tamano comprimido: %d bytes\n", tamComprimido);

    arrayDescomprimido = descomprimir_rle_terna(
        arrayComprimido,
        tamComprimido,
        &tamDescomprimido
        );

    printf("\n");
    printf("Tamano descomprimido: %d bytes\n", tamDescomprimido);

    if (arrayComprimido != NULL && tamComprimido > 0) {
        desencriptarCharArray(arrayComprimido, tamComprimido, "ARRAY COMPRIMIDO");
    }

    if (arrayDescomprimido != NULL && tamDescomprimido > 0) {
        desencriptarCharArray(arrayDescomprimido, tamDescomprimido, "ARRAY DESCOMPRIMIDO");
    }

    free(arrayComprimido);
    free(arrayDescomprimido);
}

#include <cstdio>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>

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

// Función para mostrar el texto plano
void mostrarTextoPlano(char** pista, int longitud) {
    puts("Texto plano leido: ");
    for (int i = 0; i < longitud; ++i) {
        putchar(*pista[i]);
    }
    puts("");
}

// Función de compresión RLE
char* comprimirConRLE(char** pista, int longitud, int* longitudComprimida) {
    if (longitud <= 0) {
        *longitudComprimida = 0;
        return NULL;
    }

    char* datosComprimidos = (char*)malloc(longitud * 2);
    int indiceComprimido = 0;
    int i = 0;

    while (i < longitud) {
        char caracterActual = *pista[i];
        int contador = 1;
        int j = i + 1;

        while (j < longitud && *pista[j] == caracterActual && contador < 9) {
            contador++;
            j++;
        }

        if (contador > 1) {
            datosComprimidos[indiceComprimido++] = (char)('0' + contador);
            datosComprimidos[indiceComprimido++] = caracterActual;
        } else {
            datosComprimidos[indiceComprimido++] = caracterActual;
        }
        i = j;
    }

    *longitudComprimida = indiceComprimido;
    datosComprimidos = (char*)realloc(datosComprimidos, *longitudComprimida + 1);
    datosComprimidos[*longitudComprimida] = '\0';

    return datosComprimidos;
}

// Función para mostrar el resultado de la compresión RLE
void mostrarCompresionRLE(char* comprimido, int longitud) {
    puts("Resultado de la compresion RLE: ");
    for (int i = 0; i < longitud; ++i) {
        putchar(comprimido[i]);
    }
    puts("");
}

// Nueva función de descompresión RLE
char* descomprimirConRLE(const char* nombreArchivo, int* longitudDescomprimida) {
    char rutaCompleta[200];
    strcpy(rutaCompleta, RUTA_ABSOLUTA);
    strcat(rutaCompleta, nombreArchivo);

    std::ifstream archivo(rutaCompleta, std::ios::in | std::ios::binary | std::ios::ate);
    if (!archivo.is_open()) {
        printf("Error: No se pudo abrir el archivo comprimido en la ruta %s\n", rutaCompleta);
        *longitudDescomprimida = 0;
        return NULL;
    }

    int longitudComprimida = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    char* datosComprimidos = new char[longitudComprimida + 1];
    archivo.read(datosComprimidos, longitudComprimida);
    datosComprimidos[longitudComprimida] = '\0';

    char* datosDescomprimidos = (char*)malloc(longitudComprimida * 10);
    int indiceDescomprimido = 0;

    for (int i = 0; i < longitudComprimida; ++i) {
        if (datosComprimidos[i] >= '2' && datosComprimidos[i] <= '9') {
            int contador = datosComprimidos[i] - '0';
            char caracter = datosComprimidos[++i];
            for (int j = 0; j < contador; ++j) {
                datosDescomprimidos[indiceDescomprimido++] = caracter;
            }
        } else {
            datosDescomprimidos[indiceDescomprimido++] = datosComprimidos[i];
        }
    }

    delete[] datosComprimidos;
    archivo.close();

    *longitudDescomprimida = indiceDescomprimido;
    datosDescomprimidos = (char*)realloc(datosDescomprimidos, *longitudDescomprimida + 1);
    datosDescomprimidos[*longitudDescomprimida] = '\0';

    return datosDescomprimidos;
}

// Función para mostrar el resultado de la descompresión
void mostrarDescompresionRLE(char* descomprimido, int longitud) {
    puts("Resultado de la descompresion RLE: ");
    if (descomprimido != NULL) {
        for (int i = 0; i < longitud; ++i) {
            putchar(descomprimido[i]);
        }
    }
    puts("");
}

// Función principal de procesamiento
void procesarPista() {
    char nombreArchivo[100];
    int opcion;

    puts("Por favor, ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    puts("Seleccione una opcion:");
    puts("1. Comprimir y mostrar");
    puts("2. Descomprimir y mostrar");
    scanf("%d", &opcion);

    if (opcion == 1) {
        int longitudPista = 0;
        char** punterosPista = leerPistaEnPunteros(nombreArchivo, longitudPista);

        if (punterosPista == nullptr || longitudPista == 0) {
            puts("Error: archivo no pudo ser leido o esta vacio.");
            return;
        }

        mostrarTextoPlano(punterosPista, longitudPista);

        int longitudComprimida = 0;
        char* datosComprimidos = comprimirConRLE(punterosPista, longitudPista, &longitudComprimida);

        if (datosComprimidos != NULL) {
            mostrarCompresionRLE(datosComprimidos, longitudComprimida);
            free(datosComprimidos);
        }

        delete[] punterosPista[0];
        delete[] punterosPista;

    } else if (opcion == 2) {
        int longitudDescomprimida = 0;
        char* datosDescomprimidos = descomprimirConRLE(nombreArchivo, &longitudDescomprimida);

        if (datosDescomprimidos != NULL) {
            mostrarDescompresionRLE(datosDescomprimidos, longitudDescomprimida);
            free(datosDescomprimidos);
        }
    } else {
        puts("Opcion no valida.");
    }
}
