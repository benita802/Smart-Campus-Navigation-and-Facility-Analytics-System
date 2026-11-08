#include "HashTable.h"

using namespace std;

HashTable::HashTable(int size) {

    tableSize = size;
    table.resize(tableSize);
}

int HashTable::hashFunction(const string& key)
{
    unsigned int hash = 0;

    for(char c : key)
    {
        hash = hash * 31 + c;
    }

    return hash % tableSize;
}

void HashTable::insert(const Facility& facility)
{
    int index = hashFunction(facility.facilityID);

    table[index].push_back(facility);
}

Facility* HashTable::searchByID(const string& id)
{
    int index = hashFunction(id);

    for(auto& facility : table[index])
    {
        if(facility.facilityID == id)
        {
            return &facility;
        }
    }

    return nullptr;
}