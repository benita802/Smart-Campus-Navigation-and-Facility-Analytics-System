
#include "../include/CampusGraph.h"

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cctype>

using namespace std;

//Remove whitespace around name.
static string trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\r\n");

    if (first == string::npos) return "";

    size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

//Comparison.
static string normalize(const string& value) {
    string result = trim(value);

    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    return result;
}

//Search building by name.
int CampusGraph::findBuilding(const string& name) const {
    string target = normalize(name);

    for (int i = 0; i < static_cast<int>(buildings.size()); i++) {
        if (normalize(buildings[i]) == target)
            return i;
    }

    return -1;
}

//Buildings and reject invalid records.
void CampusGraph::loadBuildings(const string& filename) {
    ifstream file(filename);
    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        lineNumber++;
        string name = trim(line);

        if (name.empty() || name[0] == '#')
            continue;

        string reason;

        if (name.find('|') != string::npos)
            reason = "Invalid field count";
        else if (findBuilding(name) != -1)
            reason = "Duplicate building";

        if (!reason.empty()) {
            rejected++;
            cout << "Warning: " << filename << " line " << lineNumber << ": " << reason << endl;
            continue;
        }

        buildings.push_back(name);
        adjacency.push_back({});
        accepted++;
    }

    cout << filename << ": " << accepted << " accepted, " << rejected << " rejected\n";
}

//Undirected building connections.
void CampusGraph::loadConnections(const string& filename) {
    ifstream file(filename);
    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        lineNumber++;
        string record = trim(line);

        if (record.empty() || record[0] == '#')
            continue;

        size_t separator = record.find('|');
        string reason;
        int a = -1;
        int b = -1;

        if (separator == string::npos ||
            record.find('|', separator + 1) != string::npos) {
            reason = "Invalid field count";
        } else {
            string first = trim(record.substr(0, separator));
            string second = trim(record.substr(separator + 1));

            if (first.empty() || second.empty()) {
                reason = "Empty building name";
            } else {
                a = findBuilding(first);
                b = findBuilding(second);

                if (a == -1 || b == -1)
                    reason = "Unknown building";
                else if (a == b)
                    reason = "Self-connection";
                else if (find(adjacency[a].begin(), adjacency[a].end(), b) != adjacency[a].end())
                    reason = "Duplicate connection";
            }
        }

        if (!reason.empty()) {
            rejected++;
            cout << "Warning: " << filename << " line " << lineNumber << ": " << reason << endl;
            continue;
        }

        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
        connectionCount++;
        accepted++;
    }

    cout << filename << ": " << accepted << " accepted, " << rejected << " rejected\n";
}

//Display building and neighbors.
void CampusGraph::displayGraph() const {
    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(buildings.size()); i++) {
        cout << buildings[i] << ": ";

        if (adjacency[i].empty()) {
            cout << "(no connections)";
        } else {
            for (int j = 0; j < static_cast<int>(adjacency[i].size()); j++) {
                if (j > 0) cout << ", ";
                cout << buildings[adjacency[i][j]];
            }
        }

        cout << endl;
    }
}

//Graph stats.
void CampusGraph::displayGraphStats() const {
    cout << "Total buildings: " << buildings.size() << endl;
    cout << "Total connections: " << connectionCount << endl;

    for (int i = 0; i < static_cast<int>(buildings.size()); i++) {
        cout << buildings[i] << " - Degree: " << adjacency[i].size() << endl;
    }
}

//BFS.
void CampusGraph::bfsReachable(const string& start) const {
    int startIndex = findBuilding(start);

    if (startIndex == -1) {
        cout << "Error: Unknown building: " << trim(start) << endl;
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), -1);
    queue<int> q;

    visited[startIndex] = true;
    distance[startIndex] = 0;
    q.push(startIndex);

    int reachable = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << buildings[current] << " (distance " << distance[current] << ")\n";

        reachable++;

        for (int neighbor : adjacency[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }

    cout << "Reachable: " << reachable << " of " << buildings.size() << " buildings" << endl;
}

