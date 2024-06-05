#include "hash.h"

/* Fuente: Modificación del código Component Sum de la clase 8 */
int hashUserID(long long int key) {
    int k = sizeof(long long int)/sizeof(int); /* Número de componentes */
    int sum = (int)key;
    for (int i = 1; i < k; i++) {
        sum += (int)(key >> (32 * i));
    }

    if (sum < 0) sum *= -1;
    return sum % HASHTABLE_SIZE;
}

/* Fuente: Ejemplo de Double Hashing de la clase 8 */
int doubleHashUserID(long long int key) {
    if (key < 0) key *= -1;

    const long long int DOUBLEHASH_SIZE = 21067; /* Número primo anterior */
    return (int)(DOUBLEHASH_SIZE - (key % DOUBLEHASH_SIZE));
}

/* Fuente: Ejemplo de función hash para claves de strings de la clase 8 */
int hashUsername(std::string key) {
    int h = 0;
    int a = 127;
    for (char c : key) {
        h = (a*h + c) % HASHTABLE_SIZE;
    }
    return h;
}

/* Fuente: Implementación del código Component Sum (Strings) de la clase 8 */
int doubleHashUsername(std::string key){
    int sum = 0;
    for (char c : key) {
        sum += c;
    }
    return sum % HASHTABLE_SIZE;
}