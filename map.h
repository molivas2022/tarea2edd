#pragma once

#include <string>
#include "user.h"
#include "hash.h"

template <typename T>
struct Pair {
    T key;
    User value;

    bool operator==(Pair<T>);
};

const Pair<long long> NULL_PAIR_LLONG{0, NULL_USER};
const Pair<std::string> NULL_PAIR_STRING{"null", NULL_USER};

/* Abstract data type */
template <typename key, typename value>
class Map {
public:
    virtual value get(key) = 0;
    virtual value put(key, value) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

/* Abstract data type */
class UserIDMap: public Map<long long int, User> {
};

/* Abstract data type */
class UsernameMap: public Map<std::string, User> {   
};

/* ADT Implementation */
class Open_UserIDMap: public UserIDMap {
    struct Node {
        Node * next = nullptr;
        long long key;
        User value;
    };
    Node ** table;
    int _size;
public:
    Open_UserIDMap();
    ~Open_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* ADT Implementation */
class Linear_UserIDMap: public UserIDMap {
    Pair<long long> * table;
    int _size;
public:
    Linear_UserIDMap();
    ~Linear_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* ADT Implementation */
class Cuadratic_UserIDMap: public UserIDMap {
    Pair<long long> * table;
    int _size;
public:
    Cuadratic_UserIDMap();
    ~Cuadratic_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* ADT Implementation */
class Double_UserIDMap: public UserIDMap {
    Pair<long long> * table;
    int _size;
public:
    Double_UserIDMap();
    ~Double_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* ADT Implementation */
class Open_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};

/* ADT Implementation */
class Linear_UsernameMap: public UsernameMap {
    Pair<std::string> * table;
    int _size;
public:
    Linear_UsernameMap();
    ~Linear_UsernameMap();
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};


/* ADT Implementation */
class Cuadratic_UsernameMap: public UsernameMap {
    Pair<std::string> * table;
    int _size;
public:
    Cuadratic_UsernameMap();
    ~Cuadratic_UsernameMap();
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};


/* ADT Implementation */
class Double_UsernameMap: public UsernameMap {
public:
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};