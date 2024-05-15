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
};

/* User function */
User * readEntries();