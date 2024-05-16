#include <iostream>
#include <random>

#include "hash.h"

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

int main() {
    Random r;

    for(int n=0; n<5; n++) {
        auto i = r.generate();
        std::cout << "Key: " << i << " \tHash: " << hashUserID(i) << " \tDoubleHash: " << doubleHashUserID(i) << std::endl;
    }
}