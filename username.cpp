#include <iostream>
#include <string>
#include <chrono>

#include "user.h"
#include "map.h"
#include "test.h"

void testUsernameMap(UsernameMap& map, User * users, std::string * keys, int n, std::string testname) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        map.put(users[i].username, users[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
  
    // Calculamos el tiempo transcurrido
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
								   start).count();
 
    running_time *= 1e-9;

    // Imprimimos el resultado
    std::cout << testname << ";Username;" << n << ";" << running_time << std::endl;
}

int main(int argc, char** argv) {
  // Si no hay suficientes argumentos, terminamos la ejecución
  if(argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
    exit(1);
  }
  int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    User* users = readEntries(n);
    std::string* names = readUsernames(n);
    
    Open_UsernameMap dict6{};
    Linear_UsernameMap dict7{};
    Cuadratic_UsernameMap dict8{};
    Double_UsernameMap dict9{};
    STL_UsernameMap dict10{};

    testUsernameMap(dict6, users, names, n, tests[0]);
    testUsernameMap(dict7, users, names, n, tests[1]);
    testUsernameMap(dict8, users, names, n, tests[2]);
    testUsernameMap(dict9, users, names, n, tests[3]);
    testUsernameMap(dict10, users, names, n, tests[4]);

    return 0;
}