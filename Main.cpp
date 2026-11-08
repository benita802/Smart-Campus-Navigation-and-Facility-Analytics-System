#include <iostream>
#include "FacilityManager.h"

using namespace std;

int main()
{
    FacilityManager manager;

    if(!manager.loadFacilities("facilities.txt"))
    {
        cout << "File could not be loaded.\n";
        return 1;
    }

    manager.displayAllFacilities();

    manager.searchByID("F004");

    manager.searchByCategory("Computer Lab");

    manager.categoryReport();

    return 0;
}