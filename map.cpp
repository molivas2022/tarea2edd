#include "map.h"

bool Pair::operator==(Pair pair) {
    bool cond1 = (key == pair.key);
    bool cond2 = (value == pair.value);
    return cond1 && cond2;
}

Open_UserIDMap::Open_UserIDMap() {
    table = new Node * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    _size = 0;
}

Open_UserIDMap::~Open_UserIDMap() {
    /* For each cell */
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        /* Delete every node */
        Node * ptr = table[i];

        while(ptr) {
            Node * oldptr = ptr;
            ptr = ptr->next;
            delete oldptr;
        }
    }
    /* Delete the table */
    delete[] table;
}

User Open_UserIDMap::get(long long key) {
    auto idx = hashUserID(key);

    Node * ptr = table[idx]; /* Head */

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

    Node * ptr = table[idx]; /* Head */
    /* Empty cell */
    if (!ptr) {
        table[idx] = new Node{nullptr, key, value};
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
            Node * newentry = new Node{nullptr, key, value};
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

Double_UserIDMap::Double_UserIDMap() {
    table = new Pair[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR;
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
        if (table[idx] == NULL_PAIR) {
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
        if (table[idx] == NULL_PAIR) {
            table[idx] = Pair{key, value};
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
