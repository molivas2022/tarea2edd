#pragma once

#include <string>
#include "iterator.h"
#include "user.h"

/* Abstract data type */
template <typename key, typename value>
class Map {
public:
    virtual value get(key) = 0;
    virtual value put(key, value) = 0;
    virtual value remove(key) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
    virtual Iterator<key> keys() = 0;
    virtual Iterator<value> values() = 0;
};

/* Abstract data type */
class UserIDMap: public Map<long long int, User> {
};

/* Abstract data type */
class UsernameMap: public Map<std::string, User> {   
};

/* ADT Implementation */
class Open_UserIDMap: public UserIDMap {
public:
    User get(long long int) override;
    User put(long long int, User) override;
    User remove(long long int) override;
    int size() override;
    bool isEmpty() override;
    Iterator<long long int> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Linear_UserIDMap: public UserIDMap {
public:
    User get(long long int) override;
    User put(long long int, User) override;
    User remove(long long int) override;
    int size() override;
    bool isEmpty() override;
    Iterator<long long int> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Cuadratic_UserIDMap: public UserIDMap {
public:
    User get(long long int) override;
    User put(long long int, User) override;
    User remove(long long int) override;
    int size() override;
    bool isEmpty() override;
    Iterator<long long int> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Double_UserIDMap: public UserIDMap {
public:
    User get(long long int) override;
    User put(long long int, User) override;
    User remove(long long int) override;
    int size() override;
    bool isEmpty() override;
    Iterator<long long int> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Open_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    User remove(std::string) override;
    int size() override;
    bool isEmpty() override;
    Iterator<std::string> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Linear_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    User remove(std::string) override;
    int size() override;
    bool isEmpty() override;
    Iterator<std::string> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Cuadratic_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    User remove(std::string) override;
    int size() override;
    bool isEmpty() override;
    Iterator<std::string> keys() override;
    Iterator<User> values() override;
};

/* ADT Implementation */
class Double_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    User remove(std::string) override;
    int size() override;
    bool isEmpty() override;
    Iterator<std::string> keys() override;
    Iterator<User> values() override;
};