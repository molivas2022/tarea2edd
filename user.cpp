#include "user.h"

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