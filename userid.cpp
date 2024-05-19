#include <iostream>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

void testUserIDMap(UserIDMap& map, User * users, long long * keys, int n, std::string testname) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        map.put(users[i].userID, users[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculamos el tiempo transcurrido
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
								   start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    std::cout << testname << ";UserID;"  << n << ";" << running_time << std::endl;
}

int main(int argc, char** argv) {
  // Si no hay suficientes argumentos, terminamos la ejecución
  if(argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
    exit(1);
  }
  int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    User* users = readEntries(n);
    long long* ids = readUserIDs(n);
    
    Open_UserIDMap dict1{};
    Linear_UserIDMap dict2{};
    Cuadratic_UserIDMap dict3{};
    Double_UserIDMap dict4{};
    STL_UserIDMap dict5{};

    testUserIDMap(dict1, users, ids, n, tests[0]);
    testUserIDMap(dict2, users, ids, n, tests[1]);
    testUserIDMap(dict3, users, ids, n, tests[2]);
    testUserIDMap(dict4, users, ids, n, tests[3]);
    testUserIDMap(dict5, users, ids, n, tests[4]);

    return 0;
}