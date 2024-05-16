#include "hash.h"

/* Fuente: Modificación del código Component Sum de la clase 8 */
int hashUserID(long long int key) {
    int k = sizeof(long long int)/sizeof(int); /* Number of components */
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

    const long long int DOUBLEHASH_SIZE = 21067; /* Previous prime number */
    return (int)(DOUBLEHASH_SIZE - (key % DOUBLEHASH_SIZE));
}