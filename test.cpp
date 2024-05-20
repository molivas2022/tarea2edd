#include "test.h"

#include <iostream>
#include <random>
#include <string>

#include "hash.h"
#include "map.h"

/* Fuente: Modificación del código encontrado en: https://stackoverflow.com/a/22883968 */
Random::Random(User * users) {
    std::random_device rd;
    mt = new std::mt19937_64(rd());

    this->users = users;
}

Random::~Random() {
    delete mt;
}

long long Random::generateLongLong() {
    distr<long long> d;
    return d(*mt);
}

std::string Random::generateString() {
    distr<int> i(8,32);
    int size = i(*mt);

    distr<char> c(65,90);
    std::string str;
    for (int i = 0; i < size; i++) {
        str.push_back(c(*mt));
    }
    return str;
}

long long * Random::generateIDSample(int sampleSize) {
    long long * llongs = new long long[sampleSize];
    distr<int> d(0, ENTRIES_SIZE-1);

    for (int i = 0; i < sampleSize; i++) {
        llongs[i] = users[d(*mt)].userID;
    }
    return llongs;
}

std::string * Random::generateUsernameSample(int sampleSize) {
    std::string * strings = new std::string[sampleSize];
    distr<int> d(0, ENTRIES_SIZE-1);

    for (int i = 0; i < sampleSize; i++) {
        strings[i] = users[d(*mt)].username;
    }
    return strings;
}

long long * Random::generateFalseIDSample(int sampleSize) {
    long long * llongs = new long long[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        long long candidate;
        while (true) {
            candidate = generateLongLong();
            for (int i = 0; i < ENTRIES_SIZE; i++) {
                if (candidate == users[i].userID) {
                    continue;
                }
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
            candidate = generateString();
            for (int i = 0; i < ENTRIES_SIZE; i++) {
                if (candidate == users[i].username) {
                    continue;
                }
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
    _start = high_resolution_clock::now();
    _lap = high_resolution_clock::now();
}

double Clock::lap() {
    using namespace std::chrono;
    high_resolution_clock::time_point _lastlap = _lap;
    _lap = high_resolution_clock::now();
    return duration_cast<nanoseconds>(_lap - _lastlap).count() * 1e-6;
}

double Clock::now() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now() - _start).count() * 1e-6;
}