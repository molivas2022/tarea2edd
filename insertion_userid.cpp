#include <iostream>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

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

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
int main(int argc, char** argv) {
    /* Si no hay suficientes argumentos, terminamos la ejecución */
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    User* users = readEntries(n);
    // long long* ids = readUserIDs(n); No es usado en el resto del programa
    
    Open_UserIDMap dict1{};
    Linear_UserIDMap dict2{};
    Cuadratic_UserIDMap dict3{};
    Double_UserIDMap dict4{};
    STL_UserIDMap dict5{};

    testUserIDMap(dict1, users, n, tests[0]);
    testUserIDMap(dict2, users, n, tests[1]);
    testUserIDMap(dict3, users, n, tests[2]);
    testUserIDMap(dict4, users, n, tests[3]);
    testUserIDMap(dict5, users, n, tests[4]);

    /* Liberamos memoria */
    delete[] users;

    return 0;
}