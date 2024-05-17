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
        user.userID = std::stoll(token);

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