#pragma once

#include <random>
#include <string>
#include <chrono>
#include "user.h"
#include "map.h"

const std::string tests[] = {
    "Separate Chaining",
    "Linear Probing",
    "Quadratic Probing",
    "Double Hashing",
    "STL"
};

class Random {
    std::mt19937_64 * mt;
    User * users;
    int n;
    template <typename T>
    using distr = std::uniform_int_distribution<T>;

    long long generateLongLong();
    std::string generateString();
public:
    Random(User * users, int n);
    ~Random();
    long long * generateIDSample(int sampleSize);
    std::string * generateUsernameSample(int sampleSize);

    long long * generateFalseIDSample(int sampleSize);
    std::string * generateFalseUsernameSample(int sampleSize);
    long long * generateFalseIDSample_Fast(int sampleSize, UserIDMap& verifier);
    std::string * generateFalseUsernameSample_Fast(int sampleSize, UsernameMap& verifier);
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