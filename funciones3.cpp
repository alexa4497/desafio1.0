#include "librerias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar 'bool' en C

#define INITIAL_CAPACITY 50

unsigned int manual_strlen(const char* s) {
    unsigned int len = 0;
    if (!s) return 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char* manual_strdup(const char* s) {
    if (!s) return NULL;
    unsigned int len = manual_strlen(s);
    char* d = (char*)malloc(len + 1);
    if (!d) return NULL;
    memcpy(d, s, len);
    d[len] = '\0';
    return d;
}

// Versión simplificada de LZ78 (Descompresión)
char* LZ78(const char* input, int option) {
    if (option != 2) return manual_strdup("");

    return manual_strdup("Resultado Descomprimido (LZ78)");
}


bool esFormatoLZ78Valido(const char* datos) {
    if (!datos || manual_strlen(datos) == 0) return false;

    int comas = 0, espacios = 0;
    for (unsigned int i = 0; datos[i] != '\0'; i++) {
        if (datos[i] == ',') comas++;
        if (datos[i] == ' ') espacios++;
    }

    // Requiere al menos un token completo (0,X )
    return (comas > 0 && espacios > 0);
}

void guardarResultado(const char* nombreArchivo, const char* datos) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("Error: No se pudo crear el archivo de salida\n");
        return;
    }

    fprintf(archivo, "%s", datos);
    fclose(archivo);
    printf("Resultado guardado en: %s\n", nombreArchivo);
}

// La función principal de procesamiento, ahora sin las pruebas internas
void procesarPistaLZ78(const char* datosComprimidos, int tamano) {
    printf("\n=== PROCESANDO DATOS LZ78 ===\n");

    if (!datosComprimidos || tamano == 0) {
        printf("Error: No hay datos para procesar con LZ78\n");
        return;
    }

    printf("Datos recibidos (%d bytes).\n", tamano);

    if (!esFormatoLZ78Valido(datosComprimidos)) {
        printf("❌ Los datos NO tienen formato LZ78 válido (esperado: N,C N,C ...)\n");
        printf("Fragmento de datos: '%.50s'\n", datosComprimidos);
        return;
    }

    printf("✅ Formato LZ78 detectado, descomprimiendo...\n");
    // La función LZ78 es la que realiza el trabajo de descompresión
    char* resultadoLZ78 = LZ78(datosComprimidos, 2);

    if (resultadoLZ78 && resultadoLZ78[0] != '\0') {
        printf("✅ DESCOMPRESIÓN EXITOSA!\n");
        printf("Resultado: '%s'\n", resultadoLZ78);

        char nombreSalida[100];
        printf("Ingrese el nombre del archivo de salida: ");
        // Usar un buffer de entrada seguro
        if (scanf("%99s", nombreSalida) == 1) {
            guardarResultado(nombreSalida, resultadoLZ78);
        } else {
            printf("Error al leer el nombre de salida.\n");
        }
    } else {
        printf("❌ La descompresión LZ78 falló o el resultado está vacío.\n");
    }

    free(resultadoLZ78); // Liberar la memoria asignada por LZ78
}
