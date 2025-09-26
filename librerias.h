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


#endif // LIBRERIAS_H
