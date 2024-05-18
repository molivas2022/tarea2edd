#include "user.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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


User * readEntries() {
    /* Open the CSV file */
    std::ifstream file{ENTRIES_PATH};
    if (!file.is_open()) {
        std::cerr << "Error opening the .csv file" << std::endl;
        return nullptr;
    }

    User * users = new User[ENTRIES_SIZE];

    /* Read the file line by line */
    std::string line;
    std::getline(file, line); /* Skip the first line */
    for (int i = 0; i < ENTRIES_SIZE; i++) {
        std::getline(file, line);
        std::istringstream ss(line);
        std::string token;
        User user;

        std::getline(ss, token, ',');
        user.university = token;

        std::getline(ss, token, ',');
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

        users[i] = user;
    }

    file.close();
    return users;
}