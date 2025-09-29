#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <cstdio>
<<<<<<< HEAD
#include <cstring>

// funciones1
char* leerArchivo(const char* nombreArchivo, int* tamanioArchivo);
void procesarArchivo();

// funciones2
char* descomprimir_rle_terna(const char* datos_comprimidos, int tam_comprimido, int* tam_descomprimido);

// funcion3
void procesarPistaLZ78(const char* datosDescomprimidos, int tamano);
void guardarResultado(const char* nombreArchivo, const char* datos);

// FUNCIONES DE DESENCRIPTACIÓN ORIGINALES
unsigned char rotarIzquierda(unsigned char byte, int rotaciones);
unsigned char rotarDerecha(unsigned char byte, int rotaciones);
int calcularPuntuacion(unsigned char c);
int contarImprimiblesMejorado(unsigned char* mensaje, int longitud);
void desencriptarArray(unsigned char* arrayEncriptado, int longitud, const char* nombreArray);
void desencriptarCharArray(char* arrayEncriptado, int longitud, const char* nombreArray);

#endif
=======
#include <fstream>
#include <cstring>
#include <vector>


void procesarPista();
char** leerPistaEnPunteros(const char* nombreArchivo, int& longitud);
void mostrarTextoPlano(char** pista, int longitud);
void mostrarCompresion(char** pista, int longitud);

char* descomprimirConRLE(const char* datosComprimidos, int longitudComprimida, int* longitudDescomprimida);


#endif // LIBRERIAS_H
>>>>>>> f3ed99dad48e677befa7e92b21440aaa31abb47e
