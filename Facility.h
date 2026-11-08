#ifndef FACILITY_H
#define FACILITY_H

#include <string>

using namespace std;

struct Facility {

    string facilityID;
    string facilityName;
    string category;
    string buildingName;

    Facility()
    {
        facilityID = "";
        facilityName = "";
        category = "";
        buildingName = "";
    }

    Facility(string id, string facility, string cat, string building)
    {
        facilityID = id;
        facilityname = facility;
        category = cat;
        buildingName = building;
    }
};

#endif