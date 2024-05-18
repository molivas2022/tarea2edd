#pragma once

#include <random>
#include <string>
#include <chrono>
#include "user.h"

class Random {
    std::mt19937_64 * mt;
    User * users;
    template <typename T>
    using distr = std::uniform_int_distribution<T>;

    long long generateLongLong();
    std::string generateString();
public:
    Random(User * users);
    ~Random();
    long long * generateIDSample(int sampleSize);
    std::string * generateUsernameSample(int sampleSize);
    long long * generateFalseIDSample(int sampleSize);
    std::string * generateFalseUsernameSample(int sampleSize);
};

/* Unit: milliseconds */
class Clock {
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _lap;
public:
    Clock();
    void start();
    double lap();
    double now();
};