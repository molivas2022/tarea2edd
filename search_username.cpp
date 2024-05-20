#include <iostream>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUsernameMap(UsernameMap& map, User * users, std::string * names, int n, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].username, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < n; i++) {
        if (map.get(names[i]) == NULL_USER) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";Username;" << "Almacenados;" << running_time << std::endl;
}

/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void negativeTestUsernameMap(UsernameMap& map, User * users, std::string * falsenames, int n, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].username, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < n; i++) {
        if (!(map.get(falsenames[i]) == NULL_USER)) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    std::cout << testname << ";Username;" << "No almacenados;" << running_time << std::endl;
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

    /* Generamos usernames aleatorios */
    Random r(users);
    std::string * names = r.generateUsernameSample(n);
    std::string * fnames = r.generateFalseUsernameSample(n);
    
    Open_UsernameMap dict6{};
    Linear_UsernameMap dict7{};
    Cuadratic_UsernameMap dict8{};
    Double_UsernameMap dict9{};
    STL_UsernameMap dict10{};

    testUsernameMap(dict6, users, names,  n, tests[0]);
    negativeTestUsernameMap(dict6, users, fnames, n, tests[0]);
    testUsernameMap(dict7, users, names, n, tests[1]);
    negativeTestUsernameMap(dict7, users, fnames, n, tests[1]);
    testUsernameMap(dict8, users, names, n, tests[2]);
    negativeTestUsernameMap(dict8, users, fnames, n, tests[2]);
    testUsernameMap(dict9, users, names, n, tests[3]);
    negativeTestUsernameMap(dict9, users, fnames, n, tests[3]);
    testUsernameMap(dict10, users, names, n, tests[4]);
    negativeTestUsernameMap(dict10, users, fnames, n, tests[4]);

    /* Liberamos memoria */
    delete[] users;
    delete[] names;
    delete[] fnames;

    return 0;
}