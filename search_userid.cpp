#include <iostream>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUserIDMap(UserIDMap& map, User * users, long long * ids, int n, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].userID, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < n; i++) {
        if (map.get(ids[i]) == NULL_USER) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";UserID;" << "Almacenados;" << running_time << std::endl;
}

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void negativeTestUserIDMap(UserIDMap& map, User * users, long long * falseids, int n, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].userID, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < n; i++) {
        if (!(map.get(falseids[i]) == NULL_USER)) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";UserID;" << "No almacenados;" << running_time << std::endl;
}

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
int main(int argc, char** argv) {
    /* Si no hay suficientes argumentos, terminamos la ejecución */
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    User* users = readEntries(ENTRIES_SIZE);

    /* Generamos userids aleatorios */
    Random r(users);
    long long * ids = r.generateIDSample(n);
    long long * fids = r.generateFalseIDSample(n);
    
    Open_UserIDMap dict1{};
    Linear_UserIDMap dict2{};
    Cuadratic_UserIDMap dict3{};
    Double_UserIDMap dict4{};
    STL_UserIDMap dict5{};

    testUserIDMap(dict1, users, ids,  n, tests[0]);
    negativeTestUserIDMap(dict1, users, fids, n, tests[0]);
    testUserIDMap(dict2, users, ids, n, tests[1]);
    negativeTestUserIDMap(dict2, users, fids, n, tests[1]);
    testUserIDMap(dict3, users, ids, n, tests[2]);
    negativeTestUserIDMap(dict3, users, fids, n, tests[2]);
    testUserIDMap(dict4, users, ids, n, tests[3]);
    negativeTestUserIDMap(dict4, users, fids, n, tests[3]);
    testUserIDMap(dict5, users, ids, n, tests[4]);
    negativeTestUserIDMap(dict5, users, fids, n, tests[4]);

    /* Liberamos memoria */
    delete[] users;
    delete[] ids;
    delete[] fids;

    return 0;
}