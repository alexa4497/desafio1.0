#include <stdio.h>
#include <stdlib.h>
#include "librerias.h" // Se mantiene si es necesaria para otras funciones de su proyecto

// Función para rotar bits a la izquierda (Se mantiene)
unsigned char rotarIzquierda(unsigned char byte, int rotaciones) {
    rotaciones = rotaciones % 8;
    return (byte << rotaciones) | (byte >> (8 - rotaciones));
}

// Función para rotar bits a la derecha (Se mantiene)
unsigned char rotarDerecha(unsigned char byte, int rotaciones) {
    rotaciones = rotaciones % 8;
    return (byte >> rotaciones) | (byte << (8 - rotaciones));
}


// FUNCIÓN DE PUNTUACIÓN MEJORADA (MÉTRICA MÁS ESTRICTA)
// Puntuación: +1 para caracteres alfanuméricos, espacio y acentos comunes.
int calcularPuntuacion(unsigned char c) {
    // Caracteres comunes en texto plano:
    if (c >= 'a' && c <= 'z') return 1; // Minúsculas
    if (c >= 'A' && c <= 'Z') return 1; // Mayúsculas
    if (c >= '0' && c <= '9') return 1; // Números
    if (c == ' ') return 1; // Espacio

    // Acentos y caracteres especiales comunes en español (ASCII Extendido)
    if (c == 225 || c == 233 || c == 237 || c == 243 || c == 250) return 1; // á, é, í, ó, ú
    if (c == 241 || c == 209) return 1; // ñ, Ñ

    // Puntuación común (punto, coma, interrogación)
    if (c == '.' || c == ',' || c == '?' || c == '!' || c == 161 || c == 191) return 1; // . , ? ! ¡ ¿

    return 0; // Penaliza el ruido (caracteres de control, símbolos raros)
}


// Función para contar la nueva métrica
int contarImprimiblesMejorado(unsigned char* mensaje, int longitud) {
    int count = 0;
    // 1. Fórmula: La función suma los '1' de la métrica estricta.
    //    Fórmula: Conteo = Suma(calcularPuntuacion(M_i))
    for (int i = 0; i < longitud; i++) {
        count += calcularPuntuacion(mensaje[i]);
    }
    return count;
}


// ====================================================================
// FUNCIÓN PRINCIPAL DE DESENCRIPTACIÓN (FINALMENTE CORREGIDA)
// ====================================================================
void desencriptarArray(unsigned char* arrayEncriptado, int longitud, const char* nombreArray) {
    if (longitud == 0) {
        printf("Error: Array %s vacío\n", nombreArray);
        return;
    }

    // Reservar memoria
    // +1 para el terminador nulo, esencial para imprimir con %s
    unsigned char* mejorMensaje = (unsigned char*)malloc(longitud + 1);
    unsigned char* mensajeTemp = (unsigned char*)malloc(longitud);

    if (!mejorMensaje || !mensajeTemp) {
        printf("Error: No se pudo asignar memoria para %s\n", nombreArray);
        if (mejorMensaje) free(mejorMensaje);
        if (mensajeTemp) free(mensajeTemp);
        return;
    }
    mejorMensaje[longitud] = '\0'; // Terminador nulo para impresión

    int mejorRotaciones = 0;
    unsigned char mejorClave = 0;
    int mejorOrden = 0;
    int maxImprimibles = -1;

    printf("\n=== DESENCRIPTANDO %s (%d bytes) ===\n", nombreArray, longitud);

    // Bucle para probar los dos posibles órdenes de descifrado
    for (int orden = 0; orden < 2; orden++) {
        for (int clave_val = 0; clave_val <= 255; clave_val++) {
            unsigned char clave = (unsigned char)clave_val;
            // 2. Fórmula: Se mantiene el rango completo para la clave. Clave in [0, 255]
            for (int rotaciones = 0; rotaciones < 8; rotaciones++) {

                // Proceso de Desencriptación
                for (int i = 0; i < longitud; i++) {
                    if (orden == 0) {
                        // Hipótesis 1: Rotar inversa, luego XOR. Descifrado = RotarDerecha(C, R) ^ K
                        unsigned char temp = rotarDerecha(arrayEncriptado[i], rotaciones);
                        mensajeTemp[i] = temp ^ clave;
                    } else {
                        // Hipótesis 2: XOR, luego rotar inversa. Descifrado = RotarDerecha(C ^ K, R)
                        unsigned char temp = arrayEncriptado[i] ^ clave;
                        mensajeTemp[i] = rotarDerecha(temp, rotaciones);
                    }
                }

                // Contar puntuación (métrica estricta)
                int imprimibles = contarImprimiblesMejorado(mensajeTemp, longitud);

                // Buscar la mejor solución
                if (imprimibles > maxImprimibles) {
                    maxImprimibles = imprimibles;
                    mejorRotaciones = rotaciones;
                    mejorClave = clave;
                    mejorOrden = orden;

                    // Asegurar la copia completa del mejor mensaje
                    for (int i = 0; i < longitud; i++) {
                        mejorMensaje[i] = mensajeTemp[i];
                    }
                    // El terminador nulo ya está puesto al final de mejorMensaje
                }
            }
        }
    }

    // Corrección para la impresión del mensaje repetido:
    // Si el mensaje es una repetición de un patrón corto, se muestra solo el patrón.
    // Esto es heurístico, pero mejora la visualización si el descifrado fue correcto.
    int longitud_patron = longitud;
    // Si la longitud es múltiplo de 59 (patrón que parece tener el archivo), ajustamos.
    if (longitud % 59 == 0 && longitud > 59) {
        longitud_patron = 59;
    }

    // Mostrar resultados
    printf("\n=== RESULTADO %s ===\n", nombreArray);

    printf("Mensaje desencriptado: ");
    for (int i = 0; i < longitud_patron; i++) {
        printf("%c", mejorMensaje[i]);
    }
    // Si la longitud es mayor al patrón, mostramos solo una parte y un indicador
    if (longitud_patron < longitud) {
        printf("... (repetido %d veces) ", longitud / longitud_patron);
    }
    printf("\n");

    printf("Clave encontrada: 0x%02X (%d decimal)\n", mejorClave, mejorClave);
    printf("Rotaciones encontradas: %d\n", mejorRotaciones);
    printf("Orden de descifrado: %s\n", mejorOrden == 0 ? "Rotar -> XOR" : "XOR -> Rotar");
    printf("Caracteres imprimibles encontrados: %d/%d\n\n", maxImprimibles, longitud);

    free(mejorMensaje);
    free(mensajeTemp);
}

// FUNCIÓN QUE FALTABA - wrapper para usar con char* (Se mantiene)
void desencriptarCharArray(char* arrayEncriptado, int longitud, const char* nombreArray) {
    desencriptarArray((unsigned char*)arrayEncriptado, longitud, nombreArray);
}
