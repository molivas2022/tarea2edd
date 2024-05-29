#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip> 

#include "user.h"
#include "map.h"
#include "test.h"

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUserIDMap(UserIDMap& map, User * users, long long * ids, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.put(users[i].userID, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        if (map.get(ids[i]) == NULL_USER) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";UserID;" << "Almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
void testUserIDMap(std::unordered_map<long long, User> map, User * users, long long * ids, int n, int k, std::string testname);

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void negativeTestUserIDMap(UserIDMap& map, User * users, long long * falseids, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.put(users[i].userID, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        if (!(map.get(falseids[i]) == NULL_USER)) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";UserID;" << "No almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
void negativeTestUserIDMap(std::unordered_map<long long, User> map, User * users, long long * falseids, int n, int k, std::string testname);

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
int main(int argc, char** argv) {
    /* Si no hay suficientes argumentos, terminamos la ejecución */
    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de inserciones>" << " <cantidad de busquedas>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); /* Cantidad de inserciones */
    int k = atoi(argv[2]); /* Cantidad de busquedas */

    User* users = readEntries(n);

    /* Generamos userIDs aleatorios */
    Random r(users, n);
    long long * ids = r.generateIDSample(k);
    long long * fids = r.generateFalseIDSample(k);
    
    Chaining_UserIDMap dict6{};
    Linear_UserIDMap dict7{};
    Quadratic_UserIDMap dict8{};
    Double_UserIDMap dict9{};
    std::unordered_map<long long, User> dict10{};

    testUserIDMap(dict6, users, ids, n, k, tests[0]);
    negativeTestUserIDMap(dict6, users, fids, n, k, tests[0]);
    testUserIDMap(dict7, users, ids, n, k, tests[1]);
    negativeTestUserIDMap(dict7, users, fids, n, k, tests[1]);
    testUserIDMap(dict8, users, ids, n, k, tests[2]);
    negativeTestUserIDMap(dict8, users, fids, n, k, tests[2]);
    testUserIDMap(dict9, users, ids, n, k, tests[3]);
    negativeTestUserIDMap(dict9, users, fids, n, k, tests[3]);
    testUserIDMap(dict10, users, ids, n, k, tests[4]);
    negativeTestUserIDMap(dict10, users, fids, n, k, tests[4]);

    /* Liberamos memoria */
    delete[] users;
    delete[] ids;
    delete[] fids;

    return 0;
}


/* -- STL Map -- */
void testUserIDMap(std::unordered_map<long long, User> map, User * users, long long * ids, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].userID, users[i]});
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        map.find(ids[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";UserID;" << "Almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
void negativeTestUserIDMap(std::unordered_map<long long, User> map, User * users, long long * falseids, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].userID, users[i]});
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        map.find(falseids[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";UserID;" << "No almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}