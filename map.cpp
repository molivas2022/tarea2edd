#include "map.h"

#include <stdexcept>

/* Implementación de comparación para pares clave-valor */
/* Son iguales si y solo si coinciden la clave y el valor */
template <typename T>
bool Pair<T>::operator==(Pair<T> pair) {
    bool cond1 = (key == pair.key);
    bool cond2 = (value == pair.value);
    return cond1 && cond2;
}

/* Implementación de Map de encadenamiento separado para claves númericas */
Chaining_UserIDMap::Chaining_UserIDMap() {
    table = new Node<long long> * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    _size = 0;
}
Chaining_UserIDMap::~Chaining_UserIDMap() {
    /* Para cada bucket */
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        /* Elimina cada nodo */
        Node<long long> * ptr = table[i];

        while(ptr) {
            Node<long long> * oldptr = ptr;
            ptr = ptr->next;
            delete oldptr;
        }
    }
    /* Elimina la tabla */
    delete[] table;
}
User Chaining_UserIDMap::get(long long key) {
    auto idx = hashUserID(key);

    Node<long long> * ptr = table[idx]; /* Raiz */

    while (ptr) {
        /* Clave encontrada */
        if (ptr->key == key) {
            return ptr->value;
        }

        /* Siguiente nodo */
        ptr = ptr->next;
    }

    /* Clave no encontrada */
    return NULL_USER;
}
User Chaining_UserIDMap::put(long long key, User value) {
    auto idx = hashUserID(key);

    Node<long long> * ptr = table[idx]; /* Raiz */
    /* Bucket vacio */
    if (!ptr) {
        table[idx] = new Node<long long>{nullptr, key, value};
        _size++;
        return NULL_USER;
    }

    while (true) {
        /* Clave repetida */
        if (ptr->key == key) {
            User returnvalue = ptr->value;
            ptr->value = value;
            return returnvalue;
        }
        /* Clave no encontrada */
        if (!ptr->next) {
            Node<long long> * newentry = new Node<long long>{nullptr, key, value};
            _size++;
            ptr->next = newentry;
            return NULL_USER;
        }
        /* Siguiente nodo */
        ptr = ptr->next;
    }
}
int Chaining_UserIDMap::size() {return _size;}
bool Chaining_UserIDMap::isEmpty() {return (_size == 0);}

/* Implementación de Map con lineal probing para claves númericas */
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

        /* Bucket vacio: clave no encontrada */
        if (c == NULL_PAIR_LLONG) {
            return NULL_USER;
        } 
        /* Clave encontrada */
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
        /* Bucket vacio */
        if (table[i] == NULL_PAIR_LLONG) {
            table[i] = Pair<long long>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in lineal-probing hash table";
}
int Linear_UserIDMap::size(){return _size;}
bool Linear_UserIDMap::isEmpty(){return (_size == 0);}

/* Implementación de Map con quadratic probing para claves númericas */
Quadratic_UserIDMap::Quadratic_UserIDMap(){
    table = new Pair<long long>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_LLONG;
    }
    _size = 0;
}
Quadratic_UserIDMap::~Quadratic_UserIDMap() {
    delete[] table;
}
User Quadratic_UserIDMap::get(long long int key){
    int i = hashUserID(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;
        Pair<long long> c = table[i];

        /* Bucket vacio: Clave no encontrada */
        if (c == NULL_PAIR_LLONG) {
            return NULL_USER;
        }
        /* Clave encontrada */
        else if (table[i].key == key) {
            return c.value;
        }
    }

    return NULL_USER;
}
User Quadratic_UserIDMap::put(long long int key, User value){
    int i = hashUserID(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;

        /* Bucket vacio */
        if (table[i] == NULL_PAIR_LLONG) {
            table[i] = Pair<long long>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in quadratic-probing hash table";
}
int Quadratic_UserIDMap::size(){return _size;}
bool Quadratic_UserIDMap::isEmpty(){return (_size == 0);}

/* Implementación de Map con double hashing para claves númericas */
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

        /* Bucket vacio: Clave no encontrada */
        if (table[idx] == NULL_PAIR_LLONG) {
            return NULL_USER;
        }
        /* Clave encontrada */
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

        /* Bucket vacio */
        if (table[idx] == NULL_PAIR_LLONG) {
            table[idx] = Pair<long long>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
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

/* Implementación de Map de encadenamiento separado para claves alfabéticas */
Chaining_UsernameMap::Chaining_UsernameMap() {
    table = new Node<std::string> * [HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    _size = 0;
}
Chaining_UsernameMap::~Chaining_UsernameMap() {
    /* Por cada bucket */
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        /* Elimina cada nodo */
        Node<std::string> * ptr = table[i];

        while(ptr) {
            Node<std::string> * oldptr = ptr;
            ptr = ptr->next;
            delete oldptr;
        }
    }
    /* Elimina la tabla */
    delete[] table;
}
User Chaining_UsernameMap::get(std::string key) {
    auto idx = hashUsername(key);

    Node<std::string> * ptr = table[idx]; /* Raiz */

    while (ptr) {
        /* Clave encontrada */
        if (ptr->key == key) {
            return ptr->value;
        }

        /* Siguiente nodo */
        ptr = ptr->next;
    }

    /* Clave no encontrada */
    return NULL_USER;
}
User Chaining_UsernameMap::put(std::string key, User value) {
    auto idx = hashUsername(key);

    Node<std::string> * ptr = table[idx]; /* Raiz */
    /* Bucket vacio */
    if (!ptr) {
        table[idx] = new Node<std::string>{nullptr, key, value};
        _size++;
        return NULL_USER;
    }

    while (true) {
        /* Clave repetida */
        if (ptr->key == key) {
            User returnvalue = ptr->value;
            ptr->value = value;
            return returnvalue;
        }
        /* Clave no encontrada */
        if (!ptr->next) {
            Node<std::string> * newentry = new Node<std::string>{nullptr, key, value};
            _size++;
            ptr->next = newentry;
            return NULL_USER;
        }
        /* Siguiente nodo */
        ptr = ptr->next;
    }
}
int Chaining_UsernameMap::size() {return _size;}
bool Chaining_UsernameMap::isEmpty() {return (_size == 0);}

/* Implementación de Map con linear probing para claves alfabéticas */
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

        /* Bucket vacio: Clave no encontrada */
        if (c == NULL_PAIR_STRING) {
            return NULL_USER;
        } 
        /* Clave encontrada */
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
        /* Bucket vacio */
        if (table[i] == NULL_PAIR_STRING) {
            table[i] = Pair<std::string>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in linear-probing hash table";
}
int Linear_UsernameMap::size(){return _size;}
bool Linear_UsernameMap::isEmpty(){return (_size == 0);}

/* Implementación de Map con quadratic probing para claves alfabéticas */
Quadratic_UsernameMap::Quadratic_UsernameMap(){
    table = new Pair<std::string>[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table[i] = NULL_PAIR_STRING;
    }
    _size = 0;
}
Quadratic_UsernameMap::~Quadratic_UsernameMap() {
    delete[] table;
}
User Quadratic_UsernameMap::get(std::string key){
    int i = hashUsername(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;
        Pair<std::string> c = table[i];

        /* Bucket vacio: Clave no encontrada */
        if (c == NULL_PAIR_STRING) {
            return NULL_USER;
        }
        /* Clave encontrada */
        else if (table[i].key == key) {
            return c.value;
        }
    }

    return NULL_USER;
}
User Quadratic_UsernameMap::put(std::string key, User value){
    int i = hashUsername(key);

    for (int p = 0; p < HASHTABLE_SIZE; p++) {
        i = (i + p + 2*p*p) % HASHTABLE_SIZE;

        /* Bucket vacio */
        if (table[i] == NULL_PAIR_STRING) {
            table[i] = Pair<std::string>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
        else if (table[i].key == key) {
            User returnvalue = table[i].value;
            table[i].value = value;
            return returnvalue;
        }
    }
    throw "Failed to insert new key in quadratic-probing hash table";
}
int Quadratic_UsernameMap::size(){return _size;}
bool Quadratic_UsernameMap::isEmpty(){return (_size == 0);}

/* Implementación de Map con double hashing para claves alfabéticas */
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

        /* Bucket vacio: Clave no encontrada */
        if (table[idx] == NULL_PAIR_STRING) {
            return NULL_USER;
        }
        /* Clave encontrada */
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

        /* Bucket vacio */
        if (table[idx] == NULL_PAIR_STRING) {
            table[idx] = Pair<std::string>{key, value};
            _size++;
            return NULL_USER;
        }
        /* Clave repetida */
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