#include "librerias.h"
#include <cstring>
#include <cstdlib>  // <- AGREGAR ESTA LÍNEA



// Función para rotar bits a la izquierda (CORREGIDA)
unsigned char rotarIzquierda(unsigned char byte, int rotaciones) {
    if (rotaciones <= 0 || rotaciones >= 8) {
        rotaciones = rotaciones % 8;
        if (rotaciones < 0) rotaciones += 8;
    }
    return (byte << rotaciones) | (byte >> (8 - rotaciones));
}

// Función para rotar bits a la derecha (CORREGIDA)
unsigned char rotarDerecha(unsigned char byte, int rotaciones) {
    if (rotaciones <= 0 || rotaciones >= 8) {
        rotaciones = rotaciones % 8;
        if (rotaciones < 0) rotaciones += 8;
    }
    return (byte >> rotaciones) | (byte << (8 - rotaciones));
}

// FUNCIÓN DE PUNTUACIÓN MEJORADA (COMENTADA - MÉTODO ANTIGUO)
int calcularPuntuacion(unsigned char c) {
    // Caracteres comunes en texto plano:
    if (c >= 'a' && c <= 'z') return 2; // Minúsculas (mayor peso)
    if (c >= 'A' && c <= 'Z') return 2; // Mayúsculas (mayor peso)
    if (c >= '0' && c <= '9') return 1; // Números
    if (c == ' ') return 1; // Espacio

    // Acentos y caracteres especiales comunes en español
    if (c == 225 || c == 233 || c == 237 || c == 243 || c == 250) return 2; // á, é, í, ó, ú
    if (c == 241 || c == 209) return 2; // ñ, Ñ
    if (c == 193 || c == 201 || c == 205 || c == 211 || c == 218) return 2; // Á, É, Í, Ó, Ú

    // Puntuación común
    if (c == '.' || c == ',' || c == '?' || c == '!' || c == 161 || c == 191) return 1;
    if (c == ':' || c == ';' || c == '-' || c == '_') return 1;

    // Caracteres de control (penalización)
    if (c >= 1 && c <= 31) return -1; // Caracteres de control
    if (c == 127) return -1; // DEL

    return 0; // Caracteres no reconocidos
}

// Función para contar la nueva métrica (COMENTADA - MÉTODO ANTIGUO)
int contarImprimiblesMejorado(unsigned char* mensaje, int longitud) {
    int count = 0;
    for (int i = 0; i < longitud; i++) {
        count += calcularPuntuacion(mensaje[i]);
    }
    return count;
}

// FUNCIÓN PRINCIPAL DE DESENCRIPTACIÓN (CORREGIDA) (COMENTADA - MÉTODO ANTIGUO)
void desencriptarArray(unsigned char* arrayEncriptado, int longitud, const char* nombreArray) {
    if (longitud == 0) {
        printf("Error: Array %s vacío\n", nombreArray);
        return;
    }

    if (!arrayEncriptado) {
        printf("Error: Array %s es NULL\n", nombreArray);
        return;
    }

    unsigned char* mejorMensaje = (unsigned char*)malloc(longitud + 1);
    unsigned char* mensajeTemp = (unsigned char*)malloc(longitud);

    if (!mejorMensaje || !mensajeTemp) {
        printf("Error: No se pudo asignar memoria para %s\n", nombreArray);
        if (mejorMensaje) free(mejorMensaje);
        if (mensajeTemp) free(mensajeTemp);
        return;
    }

    mejorMensaje[longitud] = '\0';

    int mejorRotaciones = 0;
    unsigned char mejorClave = 0;
    int mejorOrden = 0;
    int maxImprimibles = -999999; // Valor inicial muy bajo

    printf("\n=== DESENCRIPTANDO %s (%d bytes) ===\n", nombreArray, longitud);

    for (int orden = 0; orden < 2; orden++) {
        for (int clave_val = 0; clave_val <= 255; clave_val++) {
            unsigned char clave = (unsigned char)clave_val;

            for (int rotaciones = 0; rotaciones < 8; rotaciones++) {
                for (int i = 0; i < longitud; i++) {
                    if (orden == 0) {
                        unsigned char temp = rotarDerecha(arrayEncriptado[i], rotaciones);
                        mensajeTemp[i] = temp ^ clave;
                    } else {
                        unsigned char temp = arrayEncriptado[i] ^ clave;
                        mensajeTemp[i] = rotarDerecha(temp, rotaciones);
                    }
                }

                int imprimibles = contarImprimiblesMejorado(mensajeTemp, longitud);

                if (imprimibles > maxImprimibles) {
                    maxImprimibles = imprimibles;
                    mejorRotaciones = rotaciones;
                    mejorClave = clave;
                    mejorOrden = orden;

                    for (int i = 0; i < longitud; i++) {
                        mejorMensaje[i] = mensajeTemp[i];
                    }
                }
            }
        }
    }

    printf("\n=== RESULTADO %s ===\n", nombreArray);
    printf("Mensaje desencriptado: ");

    for (int i = 0; i < longitud; i++) {
        if (mejorMensaje[i] >= 32 && mejorMensaje[i] <= 126) {
            printf("%c", mejorMensaje[i]);
        } else {
            printf("[%02X]", mejorMensaje[i]);
        }
    }
    printf("\n");

    printf("Clave encontrada: 0x%02X (%d decimal)\n", mejorClave, mejorClave);
    printf("Rotaciones encontradas: %d\n", mejorRotaciones);
    printf("Orden de descifrado: %s\n", mejorOrden == 0 ? "Rotar -> XOR" : "XOR -> Rotar");
    printf("Puntuación total: %d (de %d bytes)\n", maxImprimibles, longitud);

    free(mejorMensaje);
    free(mensajeTemp);
}

// FUNCIÓN WRAPPER para usar con char* (COMENTADA - MÉTODO ANTIGUO)
void desencriptarCharArray(char* arrayEncriptado, int longitud, const char* nombreArray) {
    desencriptarArray((unsigned char*)arrayEncriptado, longitud, nombreArray);
}
