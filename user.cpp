#include "user.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/* Implementación del operador igualdad para struct User */
/* Dos struct User son iguales si y solo si todos sus campos son iguales */
bool User::operator==(User user) {
    bool cond = (university == user.university);
    cond = cond && (userID == user.userID);
    cond = cond && (username == user.username);
    cond = cond && (tweetCount == user.tweetCount);
    cond = cond && (friendCount == user.friendCount);
    cond = cond && (followerCount == user.followerCount);
    cond = cond && (creationDate == user.creationDate);
    return cond;
}

/* Imprime los datos de un usuario */
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

User * readEntries(int n) {
    /* Abrimos el archivo CSV */
    std::ifstream file{ENTRIES_PATH};
    if (!file.is_open()) {
        std::cerr << "Error opening the .csv file" << std::endl;
        return nullptr;
    }

    /* Alocamos memoria */
    User * users = new User[n];

    /* Leemos el archivo linea por linea */
    std::string line;
    std::getline(file, line); /* Saltamos la primera linea */
    for (int i = 0; i < n; i++) {
        std::getline(file, line);
        std::istringstream ss(line);
        std::string token;
        User user; /* Estructura para guardar los campos de la entrada */

        std::getline(ss, token, ',');
        user.university = token;

        std::getline(ss, token, ',');
        /* Pasamos a double para leer notación cientifica, luego casteamos a long long */
        user.userID = static_cast<long long>(std::stod(token));

        std::getline(ss, token, ',');
        user.username = token;

        std::getline(ss, token, ',');
        user.tweetCount = std::stoi(token);

        std::getline(ss, token, ',');
        user.friendCount = std::stoi(token);

        std::getline(ss, token, ',');
        user.followerCount = std::stoi(token);

        std::getline(ss, token, ',');
        user.creationDate = token;

        /* Ingresamos la estructura al array de entradas */
        users[i] = user;
    }

    file.close();
    return users; /* Devolvemos la lectura del dataset */
}

long long* readUserIDs(int n) {
    /* Abrimos el archivo CSV */
    std::ifstream file{ENTRIES_PATH};
    if (!file.is_open()) {
        std::cerr << "Error opening the .csv file" << std::endl;
        return nullptr;
    }

    /* Alocamos memoria */
    long long* userIDs = new long long[n];

    /* Leemos el archivo linea por linea */
    std::string line;
    std::getline(file, line); /* Saltamos la primera linea */
    
    for (int i = 0; i < n; ++i) {
        if (!std::getline(file, line)) { /* En caso de qué falte información */
            std::cerr << "Not enough data in the .csv file" << std::endl;
            break;
        }

        std::istringstream ss(line);
        std::string token;

        /* Nos saltamos el campo de universidad */
        std::getline(ss, token, ',');

        /* Leemos el ID del usuario */
        std::getline(ss, token, ',');
        userIDs[i] = static_cast<long long>(std::stod(token));

        /* Dejamos de leer */
    }

    file.close();
    return userIDs; /* Devolvemos la lectura del dataset */
}

std::string* readUsernames(int n) {
    /* Abrimos el archivo CSV */
    std::ifstream file{ENTRIES_PATH};
    if (!file.is_open()) {
        std::cerr << "Error opening the .csv file" << std::endl;
        return nullptr;
    }

    /* Alocamos memoria */
    std::string* usernames = new std::string[n];

    /* Leemos el archivo linea por linea */
    std::string line;
    std::getline(file, line); /* Saltamos la primera linea */
    
    for (int i = 0; i < n; ++i) {
        if (!std::getline(file, line)) { /* En caso de qué falte información */
            std::cerr << "Not enough data in the .csv file" << std::endl;
            break;
        }

        std::istringstream ss(line);
        std::string token;

        /* Nos saltamos los campos de universidad e ID */
        std::getline(ss, token, ',');
        std::getline(ss, token, ',');

        /* Leemos el nombre del usuario */
        std::getline(ss, token, ',');
        usernames[i] = token;

        /* Dejamos de leer */
    }

    file.close();
    return usernames; /* Devolvemos la lectura del dataset */
}
