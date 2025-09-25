#include <iostream>
#include <fstream>
#include <cstring>
#include "librerias.h"

using namespace std;

// Ruta absoluta que contiene los archivos
const char* RUTA_ABSOLUTA = "C:\\Users\\alexa\\Desktop\\desafio1_0\\datasetDesarrollo\\";

// La función para leer la pista y almacenar los punteros
char** leerPistaEnPunteros(const char* nombreArchivo, int& longitud) {
    char rutaCompleta[200];

    // Combinar la ruta absoluta y el nombre del archivo
    strcpy(rutaCompleta, RUTA_ABSOLUTA);
    strcat(rutaCompleta, nombreArchivo);

    ifstream archivo(rutaCompleta,ios::in | ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de la pista en la ruta " << rutaCompleta << std::endl;
        longitud = 0;
        return nullptr;
    }

    // Contar el número de caracteres para determinar la longitud
    archivo.seekg(0, ios::end);
    longitud = archivo.tellg();
    archivo.seekg(0, ios::beg);

    // Crear un arreglo de punteros y un búfer para los datos
    char** punterosPista = new char*[longitud];
    char* datosPista = new char[longitud + 1];

    // Leer cada caracter y guardar su dirección en el arreglo de punteros
    for (int i = 0; i < longitud; ++i) {
        archivo.get(datosPista[i]);
        punterosPista[i] = &datosPista[i];
    }
    datosPista[longitud] = '\0'; // Terminador nulo

    archivo.close();
    return punterosPista;
}

// Función principal de procesamiento
void procesarPista() {
    char nombreArchivo[100];

    cout << "Por favor, ingrese el nombre del archivo de la pista (ej. pista2.txt): ";
    cin >> nombreArchivo;

    int longitudPista = 0;
    // Llamada a la función para leer la pista y obtener el arreglo de punteros
    char** punterosPista = leerPistaEnPunteros(nombreArchivo, longitudPista);

    if (punterosPista == nullptr || longitudPista == 0) {
        cerr << "Error: La pista no pudo ser leída o está vacía." << std::endl;
        return;
    }

    // Mostrar la pista leída
    cout << "Pista leida: ";
    for (int i = 0; i < longitudPista; ++i) {
        cout << *punterosPista[i];
    }
    cout << endl;

    // Aquí iría la llamada a la función de compresión
    // por ejemplo: compressLZ78(punterosPista, longitudPista);

    // Liberar la memoria asignada dinámicamente
    delete[] punterosPista[0]; // Libera el bloque de datos de la pista
    delete[] punterosPista;    // Libera el arreglo de punteros
}
