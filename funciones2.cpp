#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "librerias.h"

char* descomprimir_rle_terna(const char* datos_comprimidos, int tam_comprimido, int* tam_descomprimido) {
    const unsigned char* datos_u = (const unsigned char*)datos_comprimidos;

    if (tam_comprimido % 3 != 0) {
        printf("Advertencia: El tamaño comprimido (%d) no es multiplo de 3.\n", tam_comprimido);
    }

    int capacidad = 1024;
    *tam_descomprimido = 0;
    char* arrayDescomprimidos = (char*)malloc(capacidad);

    if (arrayDescomprimidos == NULL) {
        printf("Error: Fallo la asignacion de memoria para descompresion.\n");
        return NULL;
    }

    for (int i = 0; i < tam_comprimido; i += 3) {
        if (i + 2 >= tam_comprimido) {
            printf("Error: Terna incompleta al final. Se ignora.\n");
            break;
        }

        unsigned char conteo = datos_u[i + 1];
        unsigned char valor = datos_u[i + 2];

        for (unsigned char j = 0; j < conteo; ++j) {
            if (*tam_descomprimido >= capacidad) {
                capacidad *= 2;
                char* temp = (char*)realloc(arrayDescomprimidos, capacidad);
                if (temp == NULL) {
                    printf("Error: Fallo la reasignacion de memoria.\n");
                    free(arrayDescomprimidos);
                    return NULL;
                }
                arrayDescomprimidos = temp;
            }
            arrayDescomprimidos[*tam_descomprimido] = (char)valor;
            (*tam_descomprimido)++;
        }
    }

    char* final = (char*)realloc(arrayDescomprimidos, *tam_descomprimido);
    if (*tam_descomprimido > 0 && final != NULL) {
        arrayDescomprimidos = final;
    } else if (*tam_descomprimido == 0) {
        free(arrayDescomprimidos);
        return NULL;
    }

    return arrayDescomprimidos;
}
