#include "FacilityManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

bool FacilityManager::loadFacilities(const string& filename) {
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string facilityID;
        string facilityName;
        string category;
        string buildingName;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, building);

        Facility facility(id, name, category, building);

        facilities.push_back(facility);
    }

    file.close();

    return true;
}

void FacilityManager::searchByID(const string& id) {

    Facility* result = facilityTable.searchByID(id);

    if(result)
    {
        cout << "Facility Found" << endl;

        cout << "ID: "
             << result->facilityID
             << endl;

        cout << "Name: "
             << result->facilityName
             << endl;

        cout << "Building: "
             << result->buildingName
             << endl;

        cout << "Category: "
             << result->category
             << endl;
    }
    else
    {
        cout << "Facility not found." << endl;
    }
}

void searchByName(const string& name) {

    bool found = false;

    for(const Facility& facility : facilities)
    {
        if(facility.facilityName == name)
        {
            displayFacility(facility);
            found = true;
        }
    }

    if(!found)
    {
        cout << "No facility found." << endl;
    }
}

void searchByCategory(const string& category){

    bool found = false;

    for(const Facility& facility : facilities) {
        if(facility.category == category)
        {
            displayFacility(facility);
            found = true;
        }
    }

    if(!found) {
        cout << "No facilities found." << endl;
    }
}

void categoryReport() {

    map<string, int> report;

    for(const Facility& facility : facilities)
    {
        report[facility.category]++;
    }

    cout << "\n===== CATEGORY REPORT =====\n";

    for(const auto& item : report)
    {
        cout << item.first
             << ": "
             << item.second
             << endl;
    }
}

void FacilityManager::displayAllFacilities() {

    for(const Facility& facility : facilities) {
        cout << "\nID: "
             << facility.facilityID
             << endl;

        cout << "Name: "
             << facility.facilityName
             << endl;

        cout << "Building: "
             << facility.buildingName
             << endl;

        cout << "Category: "
             << facility.category
             << endl;
    }
}
