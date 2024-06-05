#include "test.h"

#include <iostream>
#include <random>
#include <string>

#include "hash.h"
#include "map.h"

/* Fuente: Modificación del código encontrado en: https://stackoverflow.com/a/22883968 */
Random::Random(User * users, int n) {
    std::random_device rd;
    mt = new std::mt19937_64(rd());
    this-> n = n;

    this->users = users;
}

Random::~Random() {
    delete mt; /* liberación de memoria */
}

long long Random::generateLongLong() {
    distr<long long> d;
    return d(*mt); /* genera long long aleatorio */
}

std::string Random::generateString() {
    distr<int> i(8,32); /* tamaño de string entre 8 y 32 */
    int size = i(*mt);

    distr<char> c(65,90); /* cada caracter se una letra aleatoria */
    std::string str;
    for (int i = 0; i < size; i++) {
        str.push_back(c(*mt));
    }
    return str;
}

long long * Random::generateIDSample(int sampleSize) {
    long long * llongs = new long long[sampleSize];
    distr<int> d(0, n-1); /* escoge una entrada aleatoria */

    for (int i = 0; i < sampleSize; i++) {
        llongs[i] = users[d(*mt)].userID; /* y accede a su ID */
    }
    return llongs;
}

std::string * Random::generateUsernameSample(int sampleSize) {
    std::string * strings = new std::string[sampleSize];
    distr<int> d(0, n-1); /* escoge una entrada aleatoria */

    for (int i = 0; i < sampleSize; i++) {
        strings[i] = users[d(*mt)].username; /* y accede a su username */
    }
    return strings;
}

long long * Random::generateFalseIDSample(int sampleSize) {
    long long * llongs = new long long[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        long long candidate;
        while (true) {
            candidate = generateLongLong(); /* genera un long long aleatorio */
            for (int i = 0; i < n; i++) {
                if (candidate == users[i].userID) { /* y verifica que no sea el ID de un usuario */
                    continue;
                }
            }
            break;
        }
        llongs[i] = candidate;
    }
    return llongs;
}

long long * Random::generateFalseIDSample_Fast(int sampleSize, UserIDMap& verifier) {
    long long * llongs = new long long[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        long long candidate;
        while (true) {
            candidate = generateLongLong(); /* genera un long long aleatorio */
            if (!(verifier.get(candidate) == NULL_USER)) { /* y verifica que no sea el ID de un usuario */
                continue;
            }
            break;
        }
        llongs[i] = candidate;
    }
    return llongs;
}

std::string * Random::generateFalseUsernameSample(int sampleSize) {
    std::string * strings = new std::string[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        std::string candidate;
        while (true) {
            candidate = generateString(); /* genera un string aleatorio */
            for (int i = 0; i < n; i++) {
                if (candidate == users[i].username) { /* y verifica que no sea el username de un usuario */
                    continue;
                }
            }
            break;
        }
        strings[i] = candidate;
    }
    return strings;
}

std::string * Random::generateFalseUsernameSample_Fast(int sampleSize, UsernameMap& verifier) {
    std::string * strings = new std::string[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        std::string candidate;
        while (true) {
            candidate = generateString(); /* genera un string aleatorio */
            if (!(verifier.get(candidate) == NULL_USER)) { /* y verifica que no sea el username de un usuario */
                continue;
            }
            break;
        }
        strings[i] = candidate;
    }
    return strings;
}

Clock::Clock() {
    start();
}

void Clock::start() {
    using namespace std::chrono;
    _start = high_resolution_clock::now(); /* inicializa el cronometro */
    _lap = high_resolution_clock::now();
}

double Clock::lap() {
    using namespace std::chrono;
    high_resolution_clock::time_point _lastlap = _lap; /* llamado anterior a lap() */
    _lap = high_resolution_clock::now(); /* nuevo llamado a lap() */
    return duration_cast<nanoseconds>(_lap - _lastlap).count() * 1e-6; /* diferencia en milisegundos */
}

double Clock::now() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now() - _start).count() * 1e-6; /* diferencia en milisegundos */
}