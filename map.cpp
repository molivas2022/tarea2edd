#include "map.h"

bool Pair::operator==(Pair pair) {
    bool cond1 = (key == pair.key);
    bool cond2 = (value == pair.value);
    return cond1 && cond2;
}

Linear_UserIDMap::Linear_UserIDMap(){
    table = new Pair[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR;
    }
    _size = 0;
}

Linear_UserIDMap::~Linear_UserIDMap() {
    delete[] table;
}

User Linear_UserIDMap::get(long long int key){

    int i = hashUserID(key);
    
    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p) % HASHTABLE_SIZE;
        Pair c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR) {
            return NULL_USER;
        } 
        /* Key found */
        else if (c.key == key) {
            return c.value;
        }
    }
    return NULL_USER;
}

User Linear_UserIDMap::put(long long int key, User value){
    int i = hashUserID(key);
    
    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p) % HASHTABLE_SIZE;
        /* Empty cell */
        if (table[i] == NULL_PAIR) {
            table[i] = Pair{key, value};
            _size++;
            return NULL_USER;
        }
        /* Repeated key */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in double-hashing hash table";
}

int Linear_UserIDMap::size(){return _size;}

bool Linear_UserIDMap::isEmpty(){return (_size == 0);}

Cuadratic_UserIDMap::Cuadratic_UserIDMap(){
    table = new Pair[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR;
    }
    _size = 0;
}

Cuadratic_UserIDMap::~Cuadratic_UserIDMap() {
    delete[] table;
}

User Cuadratic_UserIDMap::get(long long int key){
    int i = hashUserID(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;
        Pair c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR) {
            return NULL_USER;
        }
        /* Key found */
        else if (table[i].key == key) {
            return c.value;
        }
    }

    return NULL_USER;
}

User Cuadratic_UserIDMap::put(long long int key, User value){
    int i = hashUserID(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;

        /* Empty cell */
        if (table[i] == NULL_PAIR) {
            table[i] = Pair{key, value};
            _size++;
            return NULL_USER;
        }
        /* Repeated key */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in double-hashing hash table";
}

int Cuadratic_UserIDMap::size(){return _size;}

bool Cuadratic_UserIDMap::isEmpty(){return (_size == 0);}

