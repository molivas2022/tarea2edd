#pragma once

#include <string>
#include "user.h"
#include "hash.h"

/* Estructura auxiliar, almacena un par clave-valor */
template <typename T>
struct Pair {
    T key;
    User value;

    /* Dos pares clave valor son iguales si y solo si coinciden la clave y el valor */
    bool operator==(Pair<T>);
};

/* Par clave-valor nulo para claves númericas */
const Pair<long long> NULL_PAIR_LLONG{0, NULL_USER};
/* Par clave-valor nulo para claves alfabéticas */
const Pair<std::string> NULL_PAIR_STRING{"null", NULL_USER};

/* Estructura auxiliar, nodo de una lista enlazada, almacena un par clave-valor */
template <typename T>
struct Node {
    Node * next = nullptr;
    T key;
    User value;
};

/* Tipo de dato abstracto: Mapa */
/* Almacena pares clave-valor. No permite repetición de una misma clave */
template <typename key, typename value>
class Map {
public:
    /* Devuelve el valor asociado a una clave. Devuelve el nulo en caso de no existir la clave */
    virtual value get(key) = 0;
    /* Agrega un par clave-valor */
    /* Devuelve el valor anterior asociado a la clave */
    /* Devuelve el nulo en caso de no existir la clave anteriormente */
    virtual value put(key, value) = 0;
    /* Devuelve el tamaño del Mapa, es decir, cuantos pares clave-valor hay almacenados */
    virtual int size() = 0;
    /* Devuelve verdadero si y solo si el tamaño del Mapa es cero */
    virtual bool isEmpty() = 0;
};

/* Mapa de clave númerica y valor un struct User */
class UserIDMap: public Map<long long int, User> {
};

/* Mapa de clave alfabética y valor un struct User */
class UsernameMap: public Map<std::string, User> {   
};

/* Implementación de Map de encadenamiento separado para claves númericas */
class Chaining_UserIDMap: public UserIDMap {
    Node<long long> ** table;
    int _size;
public:
    Chaining_UserIDMap();
    ~Chaining_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* Implementación de Map con lineal probing para claves númericas */
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

/* Implementación de Map con quadratic probing para claves númericas */
class Quadratic_UserIDMap: public UserIDMap {
    Pair<long long> * table;
    int _size;
public:
    Quadratic_UserIDMap();
    ~Quadratic_UserIDMap();
    User get(long long int) override;
    User put(long long int, User) override;
    int size() override;
    bool isEmpty() override;
};

/* Implementación de Map con double hashing para claves númericas */
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

/* Implementación de Map de encadenamiento separado para claves alfabéticas */
class Chaining_UsernameMap: public UsernameMap {
    Node<std::string> ** table;
    int _size;
public:
    Chaining_UsernameMap();
    ~Chaining_UsernameMap();
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};

/* Implementación de Map con linear probing para claves alfabéticas */
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

/* Implementación de Map con quadratic probing para claves alfabéticas */
class Quadratic_UsernameMap: public UsernameMap {
    Pair<std::string> * table;
    int _size;
public:
    Quadratic_UsernameMap();
    ~Quadratic_UsernameMap();
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};

/* Implementación de Map con double hashing para claves alfabéticas */
class Double_UsernameMap: public UsernameMap {
    Pair<std::string> * table;
    int _size;
public:
    Double_UsernameMap();
    ~Double_UsernameMap();
    User get(std::string) override;
    User put(std::string, User) override;
    int size() override;
    bool isEmpty() override;
};