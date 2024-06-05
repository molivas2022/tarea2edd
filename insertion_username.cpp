#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

/* Se mide el tiempo de insertar n entradas en un mapa dado de claves alfabéticas */
/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUsernameMap(UsernameMap& map, User * users, int n, std::string testname) {
    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos la inserción */
    for (int i = 0; i < n; i++) {
        map.put(users[i].username, users[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";Username;" << n << ";" << running_time << std::endl;
}
/* Sobrecarga para probar unordered_map de la STL */
void testUsernameMap(std::unordered_map<std::string, User> map, User * users, int n, std::string testname);

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
int main(int argc, char** argv) {
    /* Si no hay suficientes argumentos, terminamos la ejecución */
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); /* Almacenará la cantidad de elementos */

    /* Leemos el .csv */
    User* users = readEntries(n);
    
    /* Creamos diccionarios... */
    Chaining_UsernameMap dict6{};
    Linear_UsernameMap dict7{};
    Quadratic_UsernameMap dict8{};
    Double_UsernameMap dict9{};
    std::unordered_map<std::string, User> dict10{};

    /* ...y los probamos */
    testUsernameMap(dict6, users, n, tests[0]);
    testUsernameMap(dict7, users, n, tests[1]);
    testUsernameMap(dict8, users, n, tests[2]);
    testUsernameMap(dict9, users, n, tests[3]);
    testUsernameMap(dict10, users, n, tests[4]);

    /* Liberamos memoria */
    delete[] users;

    return 0;
}

/* Implementación para unordered_map de la STL */

void testUsernameMap(std::unordered_map<std::string, User> map, User * users, int n, std::string testname) {
    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos la inserción */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].username, users[i]});
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";Username;"  << n << ";" << running_time << std::endl;
}