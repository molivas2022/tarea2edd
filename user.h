#pragma once

#include <string>

#define ENTRIES_SIZE 21070 /* Número de entradas en el dataset */
#define ENTRIES_PATH "universities_followers.csv" /* archivo .csv del dataset */

/* Estructura para almacenar la información de una entrada (usuario) */
struct User {
    std::string university;
    long long int userID;
    std::string username;
    int tweetCount;
    int friendCount;
    int followerCount;
    std::string creationDate;
    
    /* Dos struct User son iguales si y solo si todos sus campos son iguales */
    bool operator==(User);
};

/* Valor nulo */
const User NULL_USER{std::string("null"), 0, std::string("null"), 0, 0, 0, std::string("null")};

/* Funciones */

/* Función auxiliar que imprime los datos de un usuario */
void printUser(User);
/* Lee las primeras n entradas del dataset */
User* readEntries(int n);
/* Lee los IDs de las primeras n entradas del dataset */
long long* readUserIDs(int n);
/* Lee los nombres de usuario de las primeras n entradas del dataset */
std::string* readUsernames(int n);