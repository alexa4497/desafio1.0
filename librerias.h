#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <cstdio>
#include <fstream>
#include <cstring>
#include <vector>


void procesarPista();
char** leerPistaEnPunteros(const char* nombreArchivo, int& longitud);
void mostrarTextoPlano(char** pista, int longitud);
void mostrarCompresion(char** pista, int longitud);

char* descomprimirConRLE(const char* datosComprimidos, int longitudComprimida, int* longitudDescomprimida);


#endif // LIBRERIAS_H
