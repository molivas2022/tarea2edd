#include "map.h"

Open_UserIDMap::Open_UserIDMap() {
    table = new Node * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

Open_UserIDMap::~Open_UserIDMap() {
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
            ptr->next = newentry;
            return NULL_USER;
        }

        /* Next cycle */
        ptr = ptr->next;
    }
}

int Open_UserIDMap::size() {return -1;}

bool Open_UserIDMap::isEmpty() {return false;}
