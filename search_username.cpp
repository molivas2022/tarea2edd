#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip> 

#include "user.h"
#include "map.h"
#include "test.h"

/* Se mide el tiempo de realizar k busquedas exitosas en un mapa de tamaño n de claves alfabéticas */
/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void testUsernameMap(UsernameMap& map, User * users, std::string * names, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.put(users[i].username, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        if (map.get(names[i]) == NULL_USER) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";Username;" << "Almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
/* Sobrecarga para probar unordered_map de la STL */
void testUsernameMap(std::unordered_map<std::string, User> map, User * users, std::string * names, int n, int k, std::string testname);

/* Se mide el tiempo de realizar k busquedas fallidas (la clave no existe) en un mapa de tamaño n de claves alfabéticas */
/* Fuente: Modificación del código del video explicativo para experimentación subido en Canvas */
void negativeTestUsernameMap(UsernameMap& map, User * users, std::string * falsenames, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.put(users[i].username, users[i]);
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        if (!(map.get(falsenames[i]) == NULL_USER)) {
            exit(EXIT_FAILURE);
        }
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";Username;" << "No almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
/* Sobrecarga para probar unordered_map de la STL */
void negativeTestUsernameMap(std::unordered_map<std::string, User> map, User * users, std::string * falsenames, int n, int k, std::string testname);

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

    /* Generamos usernames aleatorios */
    Random r(users, n);
    std::string * names = r.generateUsernameSample(k);
    std::string * fnames = r.generateFalseUsernameSample(k);
    
    Chaining_UsernameMap dict6{};
    Linear_UsernameMap dict7{};
    Quadratic_UsernameMap dict8{};
    Double_UsernameMap dict9{};
    std::unordered_map<std::string, User> dict10{};

    testUsernameMap(dict6, users, names, n, k, tests[0]);
    negativeTestUsernameMap(dict6, users, fnames, n, k, tests[0]);
    testUsernameMap(dict7, users, names, n, k, tests[1]);
    negativeTestUsernameMap(dict7, users, fnames, n, k, tests[1]);
    testUsernameMap(dict8, users, names, n, k, tests[2]);
    negativeTestUsernameMap(dict8, users, fnames, n, k, tests[2]);
    testUsernameMap(dict9, users, names, n, k, tests[3]);
    negativeTestUsernameMap(dict9, users, fnames, n, k, tests[3]);
    testUsernameMap(dict10, users, names, n, k, tests[4]);
    negativeTestUsernameMap(dict10, users, fnames, n, k, tests[4]);

    /* Liberamos memoria */
    delete[] users;
    delete[] names;
    delete[] fnames;

    return 0;
}

/* Implementación para unordered_map de la STL */

void testUsernameMap(std::unordered_map<std::string, User> map, User * users, std::string * names, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].username, users[i]});
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        map.find(names[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";Username;" << "Almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}
void negativeTestUsernameMap(std::unordered_map<std::string, User> map, User * users, std::string * falsenames, int n, int k, std::string testname) {
    /* Rellenamos los diccionarios */
    for (int i = 0; i < n; i++) {
        map.insert({users[i].username, users[i]});
    }

    /* Iniciamos el cronometro */
    Clock c;
    c.start();

    /* Ejecutamos las busquedas */
    for (int i = 0; i < k; i++) {
        map.find(falsenames[i]);
    }

    /* Calculamos el tiempo transcurrido */
    double running_time = c.now();

    /* Imprimimos el resultado */
    float load_factor = ((float)n)/((float)HASHTABLE_SIZE);
    std::cout << testname << ";Username;" << "No almacenados;" << std::setprecision(2) << load_factor << ";" << running_time << std::endl;
}