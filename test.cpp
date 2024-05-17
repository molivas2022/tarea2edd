#include <iostream>
#include <random>

#include "hash.h"
#include "map.h"

/* Fuente: Modificación del código encontrado en: https://stackoverflow.com/a/22883968 */
class Random {
    std::mt19937_64 * eng;
    std::uniform_int_distribution<unsigned long long> distr;
public:
    Random() {
        std::random_device rd;
        eng = new std::mt19937_64(rd());
    }
    long long generate() {
        return distr(*eng);
    }
    ~Random() {
        delete eng;
    }
};

long long getRandomUserID(User * users) {
    int idx = rand() % ENTRIES_SIZE;
    return users[idx].userID;
}

std::string getRandomUsername(User * users) {
    int idx = rand() % ENTRIES_SIZE;
    return users[idx].username;
}

/* Función auxiliar */
void printUser(User user) {
    std::cout << "[User] ";
    std::cout << "University: " << user.university << " | ";
    std::cout << "UserID: " << user.userID << " | ";
    std::cout << "Username: " << user.username << " | ";
    std::cout << "Tweets Count: " << user.tweetCount << " | ";
    std::cout << "Friends Count: " << user.friendCount << " | ";
    std::cout << "Followers Count: " << user.followerCount << " | ";
    std::cout << "Creation Date: " << user.creationDate << std::endl;
}

int main() {
    srand(time(nullptr));
    Random r;

    /*
    for(int n=0; n<5; n++) {
        auto i = r.generate();
        std::cout << "Key: " << i << " \tHash: " << hashUserID(i) << " \tDoubleHash: " << doubleHashUserID(i) << std::endl;
    }
    */

    /*
    Double_UserIDMap dict;

    auto key1 = r.generate();
    auto key2 = r.generate();
    auto key3 = r.generate();
    User value1 = {"UDEC", 0, "Pepe", 0, 0 , 0, "May 15"};
    User value2 = {"USS", 0, "Seba", 0, 0, 0, "June 15"};
    User value3 = {"USC", 0, "Cata", 0, 0, 0, "July 15"};

    printUser(dict.put(key1, value1));
    printUser(dict.put(key2, value2));
    printUser(dict.put(key1, value3));
    std::cout << std::endl;

    printUser(dict.get(key1));
    printUser(dict.get(key2));
    printUser(dict.get(key3));
    */
    
    User * users = readEntries();
    /*
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        printUser(users[i]);
    }
    */

    /*
    Open_UserIDMap dict1;
    Linear_UserIDMap dict2;
    Cuadratic_UserIDMap dict3;
    Double_UserIDMap dict4;

    for (int i = 0; i < ENTRIES_SIZE; i++) {
        dict1.put(users[i].userID, users[i]);
        dict2.put(users[i].userID, users[i]);
        dict3.put(users[i].userID, users[i]);
        dict4.put(users[i].userID, users[i]);
        std::cout << i + 1 << "th entry done. " << std::endl;
    }

    const int searchCount = 10000;
    for (int i = 0; i < searchCount; i++) {
        long long id = getRandomUserID(users);
        std::cout << i+1 << "th search: " << std::endl;
        printUser(dict1.get(id));
        printUser(dict2.get(id));
        printUser(dict3.get(id));
        printUser(dict4.get(id));
    }
    */

    Linear_UsernameMap dict2;
    Cuadratic_UsernameMap dict3;

    for (int i = 0; i < ENTRIES_SIZE; i++) {
        dict2.put(users[i].username, users[i]);
        dict3.put(users[i].username, users[i]);
        std::cout << i + 1 << "th entry done. " << std::endl;
    }

    const int searchCount = 10000;
    for (int i = 0; i < searchCount; i++) {
        std::string name = getRandomUsername(users);
        std::cout << i+1 << "th search: " << std::endl;
        printUser(dict2.get(name));
        printUser(dict3.get(name));
    }
}