#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <cstdio>
#include <cstdlib>

// funciones1
char* leerArchivo(const char* nombreArchivo, int* tamanioArchivo);
void procesarArchivo();

// funciones2
char* descomprimir_rle_terna(const char* datos_comprimidos, int tam_comprimido, int* tam_descomprimido);

// funcion3
void procesarPistaLZ78(const char* datosDescomprimidos, int tamano);
void guardarResultado(const char* nombreArchivo, const char* datos);

// FUNCIONES DE DESENCRIPTACIÓN
unsigned char rotarIzquierda(unsigned char byte, int rotaciones);
unsigned char rotarDerecha(unsigned char byte, int rotaciones);
int esCaracterImprimible(unsigned char c);
int contarImprimibles(unsigned char* mensaje, int longitud);
void desencriptarArray(unsigned char* arrayEncriptado, int longitud, const char* nombreArray);
void desencriptarCharArray(char* arrayEncriptado, int longitud, const char* nombreArray);

#endif
