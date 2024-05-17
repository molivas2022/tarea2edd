#pragma once

#include <string>

#define ENTRIES_SIZE 21070

/* Data type */
struct User {
    std::string university;
    long long int userID;
    std::string username;
    int tweetCount;
    int friendCount;
    int followerCount;
    std::string creationDate;
    
    bool operator==(User);
};

/* Null value */
const User NULL_USER{std::string("null"), 0, std::string("null"), 0, 0, 0, std::string("null")};

/* User functions */
bool equals(User, User);

User * readEntries();