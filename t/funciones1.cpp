#include <stdio.h>
#include <stdlib.h>
#include "librerias.h"

const char* RUTA_RELATIVA = "Encriptadosx/";

// Función manual para calcular longitud de cadena
int mi_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Función manual para copiar cadenas
void mi_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Función manual para concatenar cadenas
void mi_strcat(char* dest, const char* src) {
    int i = 0;
    // Encontrar el final de dest
    while (dest[i] != '\0') {
        i++;
    }
    // Copiar src al final de dest
    int j = 0;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

char* leerArchivo(const char* nombreArchivo, int* tamanioArchivo) {
    char rutaCompleta[256];

    int len_ruta = mi_strlen(RUTA_RELATIVA);
    int len_nombre = mi_strlen(nombreArchivo);

    if (len_ruta + len_nombre >= sizeof(rutaCompleta) - 1) {
        printf("Error: La ruta completa es demasiado larga.\n");
        *tamanioArchivo = 0;
        return NULL;
    }

    mi_strcpy(rutaCompleta, RUTA_RELATIVA);
    mi_strcat(rutaCompleta, nombreArchivo);

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

    // Desencriptar array comprimido con RLE
    if (arrayComprimido != NULL && tamComprimido > 0) {
        desencriptarCharArray(arrayComprimido, tamComprimido, "ARRAY COMPRIMIDO RLE");
    }

    // Desencriptar array descomprimido con LZ78
    if (arrayDescomprimido != NULL && tamDescomprimido > 0) {
        desencriptarCharArray(arrayDescomprimido, tamDescomprimido, "ARRAY DESCOMPRIMIDO LZ78");
    }

    free(arrayComprimido);
    free(arrayDescomprimido);
}
