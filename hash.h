#pragma once

#include <string>

#define HASHTABLE_SIZE 21089 /* Número primo siguiente */

/* Funciones hash */
/* Función hash principal para claves númericas */
int hashUserID(long long int);
/* Función hash auxiliar para double hashing */
int doubleHashUserID(long long int);
/* Función hash principal para claves alfabéticas */
int hashUsername(std::string);
/* Función hash auxiliar para double hashing */
int doubleHashUsername(std::string);