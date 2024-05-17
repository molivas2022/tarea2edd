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

/* Función auxiliar */
void printUser(User user) {
    std::cout << "[User]" << " \t";
    std::cout << "University: " << user.university << " \t";
    std::cout << "UserID: " << user.userID << " \t";
    std::cout << "Username: " << user.username << " \t";
    std::cout << "Tweets Count: " << user.tweetCount << " \t";
    std::cout << "Friends Count: " << user.friendCount << " \t";
    std::cout << "Followers Count: " << user.followerCount << " \t";
    std::cout << "Creation Date: " << user.creationDate << std::endl;
}

int main() {
    Random r;

    /*
    for(int n=0; n<5; n++) {
        auto i = r.generate();
        std::cout << "Key: " << i << " \tHash: " << hashUserID(i) << " \tDoubleHash: " << doubleHashUserID(i) << std::endl;
    }
    */

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
}