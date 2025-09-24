#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

char* leerArchivo(const char* nombreArchivo);
char* identificarTipoCompresion(const char* contenido);
long obtenerTamanoArchivo(const char* nombreArchivo);

#endif
