#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include "Facility.h"

using namespace std;

class HashTable {

private:

    int tableSize;
    vector<list<Facility>> table;
    int hashFunction(const string& key);

public:

    HashTable(int size = 101);
    void insert(const Facility& facility);
    Facility* searchByID(const string& id);
};

#endif