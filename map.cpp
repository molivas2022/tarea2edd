#include "map.h"

bool Pair_int::operator==(Pair_int Pair_int) {
    bool cond1 = (key == Pair_int.key);
    bool cond2 = (value == Pair_int.value);
    return cond1 && cond2;
}

bool Pair_string::operator==(Pair_string Pair_string) {
    bool cond1 = (key == Pair_string.key);
    bool cond2 = (value == Pair_string.value);
    return cond1 && cond2;
}

Linear_UserIDMap::Linear_UserIDMap(){
    table = new Pair_int[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_INT;
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
        Pair_int c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_INT) {
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
        if (table[i] == NULL_PAIR_INT) {
            table[i] = Pair_int{key, value};
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
    table = new Pair_int[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_INT;
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
        Pair_int c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_INT) {
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
        if (table[i] == NULL_PAIR_INT) {
            table[i] = Pair_int{key, value};
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

Linear_UsernameMap::Linear_UsernameMap(){
    table = new Pair_string[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_STRING;
    }
    _size = 0;
}

Linear_UsernameMap::~Linear_UsernameMap() {
    delete[] table;
}

User Linear_UsernameMap::get(std::string key){

    int i = hashUsername(key);
    
    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p) % HASHTABLE_SIZE;
        Pair_string c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_STRING) {
            return NULL_USER;
        } 
        /* Key found */
        else if (c.key == key) {
            return c.value;
        }
    }
    return NULL_USER;
}

User Linear_UsernameMap::put(std::string key, User value){
    int i = hashUsername(key);
    
    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p) % HASHTABLE_SIZE;
        /* Empty cell */
        if (table[i] == NULL_PAIR_STRING) {
            table[i] = Pair_string{key, value};
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

int Linear_UsernameMap::size(){return _size;}

bool Linear_UsernameMap::isEmpty(){return (_size == 0);}

Cuadratic_UsernameMap::Cuadratic_UsernameMap(){
    table = new Pair_string[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_STRING;
    }
    _size = 0;
}

Cuadratic_UsernameMap::~Cuadratic_UsernameMap() {
    delete[] table;
}

User Cuadratic_UsernameMap::get(std::string key){
    int i = hashUsername(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;
        Pair_string c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_STRING) {
            return NULL_USER;
        }
        /* Key found */
        else if (table[i].key == key) {
            return c.value;
        }
    }

    return NULL_USER;
}

User Cuadratic_UsernameMap::put(std::string key, User value){
    int i = hashUsername(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;

        /* Empty cell */
        if (table[i] == NULL_PAIR_STRING) {
            table[i] = Pair_string{key, value};
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

int Cuadratic_UsernameMap::size(){return _size;}

bool Cuadratic_UsernameMap::isEmpty(){return (_size == 0);}