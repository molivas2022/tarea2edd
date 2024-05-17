#include "map.h"

template <typename T>
bool Pair<T>::operator==(Pair<T> pair) {
    bool cond1 = (key == pair.key);
    bool cond2 = (value == pair.value);
    return cond1 && cond2;
}

Open_UserIDMap::Open_UserIDMap() {
    table = new Node<long long> * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    _size = 0;
}

Open_UserIDMap::~Open_UserIDMap() {
    /* For each cell */
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        /* Delete every node */
        Node<long long> * ptr = table[i];

        while(ptr) {
            Node<long long> * oldptr = ptr;
            ptr = ptr->next;
            delete oldptr;
        }
    }
    /* Delete the table */
    delete[] table;
}

User Open_UserIDMap::get(long long key) {
    auto idx = hashUserID(key);

    Node<long long> * ptr = table[idx]; /* Head */

    while (ptr) {
        /* Key found */
        if (ptr->key == key) {
            return ptr->value;
        }

        /* Next cycle */
        ptr = ptr->next;
    }

    /* Key not found */
    return NULL_USER;
}

User Open_UserIDMap::put(long long key, User value) {
    auto idx = hashUserID(key);

    Node<long long> * ptr = table[idx]; /* Head */
    /* Empty cell */
    if (!ptr) {
        table[idx] = new Node<long long>{nullptr, key, value};
        _size++;
        return NULL_USER;
    }

    while (true) {
        /* Repeated key */
        if (ptr->key == key) {
            User returnvalue = ptr->value;
            ptr->value = value;
            return returnvalue;
        }
        /* Key not found */
        if (!ptr->next) {
            Node<long long> * newentry = new Node<long long>{nullptr, key, value};
            _size++;
            ptr->next = newentry;
            return NULL_USER;
        }
        /* Next cycle */
        ptr = ptr->next;
    }
}

int Open_UserIDMap::size() {return _size;}

bool Open_UserIDMap::isEmpty() {return (_size == 0);}

Linear_UserIDMap::Linear_UserIDMap(){
    table = new Pair<long long>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_LLONG;
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
        Pair<long long> c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_LLONG) {
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
        if (table[i] == NULL_PAIR_LLONG) {
            table[i] = Pair<long long>{key, value};
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
    table = new Pair<long long>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_LLONG;
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
        Pair<long long> c = table[i];

        /* Empty cell: Key not found */
        if (c == NULL_PAIR_LLONG) {
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
        if (table[i] == NULL_PAIR_LLONG) {
            table[i] = Pair<long long>{key, value};
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

Double_UserIDMap::Double_UserIDMap() {
    table = new Pair<long long>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_LLONG;
    }
    _size = 0;
}

Double_UserIDMap::~Double_UserIDMap() {
    delete[] table;
}

User Double_UserIDMap::get(long long key) {
    int h1 = hashUserID(key);
    int h2 = doubleHashUserID(key);

    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        int idx = (h1 + i*h2) % HASHTABLE_SIZE;

        /* Empty cell: Key not found */
        if (table[idx] == NULL_PAIR_LLONG) {
            return NULL_USER;
        }
        /* Key found */
        else if (table[idx].key == key) {
            return table[idx].value;
        }
    }
    throw "Failed to find key in double-hashing hash table";
    exit(EXIT_FAILURE);
}
 
User Double_UserIDMap::put(long long key, User value) {
    int h1 = hashUserID(key);
    int h2 = doubleHashUserID(key);

    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        int idx = (h1 + i*h2) % HASHTABLE_SIZE;

        /* Empty cell */
        if (table[idx] == NULL_PAIR_LLONG) {
            table[idx] = Pair<long long>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Repeated key */
        else if (table[idx].key == key) {
            User returnvalue = table[idx].value;
            table[idx].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in double-hashing hash table";
    exit(EXIT_FAILURE);
}

int Double_UserIDMap::size() {return _size;}

bool Double_UserIDMap::isEmpty() {return (_size == 0);}

Open_UsernameMap::Open_UsernameMap() {
    table = new Node<std::string> * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    _size = 0;
}

Open_UsernameMap::~Open_UsernameMap() {
    /* For each cell */
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        /* Delete every node */
        Node<std::string> * ptr = table[i];

        while(ptr) {
            Node<std::string> * oldptr = ptr;
            ptr = ptr->next;
            delete oldptr;
        }
    }
    /* Delete the table */
    delete[] table;
}

User Open_UsernameMap::get(std::string key) {
    auto idx = hashUsername(key);

    Node<std::string> * ptr = table[idx]; /* Head */

    while (ptr) {
        /* Key found */
        if (ptr->key == key) {
            return ptr->value;
        }

        /* Next cycle */
        ptr = ptr->next;
    }

    /* Key not found */
    return NULL_USER;
}

User Open_UsernameMap::put(std::string key, User value) {
    auto idx = hashUsername(key);

    Node<std::string> * ptr = table[idx]; /* Head */
    /* Empty cell */
    if (!ptr) {
        table[idx] = new Node<std::string>{nullptr, key, value};
        _size++;
        return NULL_USER;
    }

    while (true) {
        /* Repeated key */
        if (ptr->key == key) {
            User returnvalue = ptr->value;
            ptr->value = value;
            return returnvalue;
        }
        /* Key not found */
        if (!ptr->next) {
            Node<std::string> * newentry = new Node<std::string>{nullptr, key, value};
            _size++;
            ptr->next = newentry;
            return NULL_USER;
        }
        /* Next cycle */
        ptr = ptr->next;
    }
}

int Open_UsernameMap::size() {return _size;}

bool Open_UsernameMap::isEmpty() {return (_size == 0);}

Linear_UsernameMap::Linear_UsernameMap(){
    table = new Pair<std::string>[HASHTABLE_SIZE];
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
        Pair<std::string> c = table[i];

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
            table[i] = Pair<std::string>{key, value};
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
    table = new Pair<std::string>[HASHTABLE_SIZE];
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
        Pair<std::string> c = table[i];

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
            table[i] = Pair<std::string>{key, value};
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

Double_UsernameMap::Double_UsernameMap() {
    table = new Pair<std::string>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_STRING;
    }
    _size = 0;
}

Double_UsernameMap::~Double_UsernameMap() {
    delete[] table;
}

User Double_UsernameMap::get(std::string key) {
    int h1 = hashUsername(key);
    int h2 = doubleHashUsername(key);

    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        int idx = (h1 + i*h2) % HASHTABLE_SIZE;

        /* Empty cell: Key not found */
        if (table[idx] == NULL_PAIR_STRING) {
            return NULL_USER;
        }
        /* Key found */
        else if (table[idx].key == key) {
            return table[idx].value;
        }
    }
    throw "Failed to find key in double-hashing hash table";
    exit(EXIT_FAILURE);
}
 
User Double_UsernameMap::put(std::string key, User value) {
    int h1 = hashUsername(key);
    int h2 = doubleHashUsername(key);

    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        int idx = (h1 + i*h2) % HASHTABLE_SIZE;

        /* Empty cell */
        if (table[idx] == NULL_PAIR_STRING) {
            table[idx] = Pair<std::string>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Repeated key */
        else if (table[idx].key == key) {
            User returnvalue = table[idx].value;
            table[idx].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in double-hashing hash table";
    exit(EXIT_FAILURE);
}

int Double_UsernameMap::size() {return _size;}

bool Double_UsernameMap::isEmpty() {return (_size == 0);}