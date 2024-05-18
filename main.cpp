#include <iostream>
#include <string>

#include "test.h"
#include "user.h"
#include "map.h"

#define SAMPLE_SIZE 2

void testUserIDMap(UserIDMap& map, User * users, long long * keys, long long * falsekeys) {
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].userID, users[i]);
    }
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        printUser(map.get(keys[i]));
    }
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        printUser(map.get(falsekeys[i]));
    }
    std::cout << std::endl;
}

void testUsernameMap(UsernameMap& map, User * users, std::string * keys, std::string * falsekeys) {
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        map.put(users[i].username, users[i]);
    }
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        printUser(map.get(keys[i]));
    }
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        printUser(map.get(falsekeys[i]));
    }
    std::cout << std::endl;
}

int main() {
    User * users = readEntries();
    Random r{users};
    Clock c;
    c.start();

    long long * ids = r.generateIDSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    std::string * names = r.generateUsernameSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    long long * f_ids = r.generateFalseIDSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    std::string * f_names = r.generateFalseUsernameSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    Open_UserIDMap dict1{};
    Linear_UserIDMap dict2{};
    Cuadratic_UserIDMap dict3{};
    Double_UserIDMap dict4{};
    STL_UserIDMap dict5{};

    Open_UsernameMap dict6{};
    Linear_UsernameMap dict7{};
    Cuadratic_UsernameMap dict8{};
    Double_UsernameMap dict9{};
    STL_UsernameMap dict10{};

    std::cout << std::endl << "UserID Maps: " << std::endl << std::endl;

    testUserIDMap(dict1, users, ids, f_ids);
    testUserIDMap(dict2, users, ids, f_ids);
    testUserIDMap(dict3, users, ids, f_ids);
    testUserIDMap(dict4, users, ids, f_ids);
    testUserIDMap(dict5, users, ids, f_ids);

    std::cout << std::endl << "Username Maps: " << std::endl << std::endl;

    testUsernameMap(dict6, users, names, f_names);
    testUsernameMap(dict7, users, names, f_names);
    testUsernameMap(dict8, users, names, f_names);
    testUsernameMap(dict9, users, names, f_names);
    testUsernameMap(dict10, users, names, f_names);

    return 0;
}