

#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

using namespace std;

class CampusGraph {
private:
    vector<string> buildings;
    vector<vector<int>> adjacency;
    int connectionCount = 0;

    int findBuilding(const string& name) const;

public:
    //Campus data.
    void loadBuildings(const string& filename);
    void loadConnections(const string& filename);

    //Display graph.
    void displayGraph() const;
    void displayGraphStats() const;

    void bfsReachable(const string& start) const;
};

#endif
