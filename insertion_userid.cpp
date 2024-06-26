#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

/* Se mide el tiempo de insertar n entradas en un mapa dado de claves númericas */
/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUserIDMap(UserIDMap& map, User * users, int n, std::string testname) {
    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos la inserción */
    for (int i = 0; i < n; i++) {
        map.put(users[i].userID, users[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";UserID;"  << n << ";" << running_time << std::endl;
}

/* Sobrecarga para probar unordered_map de la STL */
void testUserIDMap(std::unordered_map<long long, User> map, User * users, int n, std::string testname);

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
    Chaining_UserIDMap dict1{};
    Linear_UserIDMap dict2{};
    Quadratic_UserIDMap dict3{};
    Double_UserIDMap dict4{};
    std::unordered_map<long long, User> dict5{};

    /* ...y los probamos */
    testUserIDMap(dict1, users, n, tests[0]);
    testUserIDMap(dict2, users, n, tests[1]);
    testUserIDMap(dict3, users, n, tests[2]);
    testUserIDMap(dict4, users, n, tests[3]);
    testUserIDMap(dict5, users, n, tests[4]);

    /* Liberamos memoria */
    delete[] users;

    return 0;
}

/* Implementación para unordered_map de la STL */

void testUserIDMap(std::unordered_map<long long, User> map, User * users, int n, std::string testname) {
    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos la inserción */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].userID, users[i]});
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";UserID;"  << n << ";" << running_time << std::endl;
}