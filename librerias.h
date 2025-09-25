#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <iostream>
#include <fstream>
#include <direct.h>  // Agregar esta línea

using namespace std;

// Declaración de funciones para leer archivos encriptados
bool leerArchivoEncriptado(char nombreArchivo[], char** contenido, int* tamanoContenido);
int obtenerNombreArchivo(char nombreArchivo[], int tamanoMaximo);
bool leerArchivoEncriptadoCompleto(char** contenido, int* tamanoContenido);

#endif // LIBRER
