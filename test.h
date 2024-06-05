#pragma once

#include <random>
#include <string>
#include <chrono>
#include "user.h"
#include "map.h"

/* Nombres de las implementaciones de Map */
const std::string tests[] = {
    "Separate Chaining",
    "Linear Probing",
    "Quadratic Probing",
    "Double Hashing",
    "STL"
};

/* Clase auxiliar que proporciona métodos para generar datos aleatorios */
class Random {
    std::mt19937_64 * mt;
    User * users;
    int n;
    template <typename T>
    using distr = std::uniform_int_distribution<T>;

    /* Genera un valor de tipo long long int aleatorio */
    long long generateLongLong();
    /* Genera un valor de tipo std::string aleatorio */
    std::string generateString();
public:
    Random(User * users, int n);
    ~Random();
    /* Devuelve IDs de usuario aleatorios del dataset */
    long long * generateIDSample(int sampleSize);
    /* Devuelve nombres de usuario aleatorios del dataset */
    std::string * generateUsernameSample(int sampleSize);

    /* Devuelve IDs de usuario falsos */
    long long * generateFalseIDSample(int sampleSize);
    /* Devuelve nombres de usuario falsos */
    std::string * generateFalseUsernameSample(int sampleSize);
    /* Implementación alternativa de generateFalseIDSample */
    long long * generateFalseIDSample_Fast(int sampleSize, UserIDMap& verifier);
    /* Implementación alternativa de generateFalseUsername */
    std::string * generateFalseUsernameSample_Fast(int sampleSize, UsernameMap& verifier);
};

/* Clase auxiliar que proporciona métodos para medir tiempo (en milisegundos) */
class Clock {
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _lap;
public:
    Clock();
    /* Inicia el cronometro */
    void start();
    /* Devuelve el tiempo (en milisegundos) desde el último llamado a lap() */
    /* Si no se ha llamado previamente a lap(), devuelve el tiempo desde el llamado a start() */
    double lap();
    /* Devuelve el tiempo (en milisegundos) desde el llamado a start() */
    double now();
};