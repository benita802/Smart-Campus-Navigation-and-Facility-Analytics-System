#include "../include/DepartmentTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

//Constructor
DepartmentTree::DepartmentTree(){
    root = nullptr;
}

//find & add department to the tree

void DepartmentTree::addDepartment(const string& name, const string& parentName){
    //Create first department aka the root
    if (parentName == "NONE"){
        if (root == nullptr){
            root = new DepartmentNode(name);
        }
        return;
    }
    //find parent node/department
    queue<DepartmentNode*> q;
    
    if (root != nullptr){
        q.push(root);

    }

    while (!q.empty()){
        DepartmentNode* current = q.front();
        q.pop();

        if (current->name == parentName){
            DepartmentNode* newNode = new DepartmentNode(name);
            newNode->parent = current;
            current->children.push_back(newNode);
            return;
        }
        for (DepartmentNode* child : current->children){
            q.push(child);
        }
    }

    cout << "Error: Parent department not found: "<< parentName<< endl;

}

// Load departments from a file
void DepartmentTree::loadDepartments(const string& filename){
    ifstream file(filename);

    if (!file.is_open()){
        cout<< " Error: Could not open departments file." << endl;
        return;
    }

    string line;

    while (getline(file, line)){
        if (line.empty() || line[0] == '#'){
            continue;
        }

        stringstream ss(line);

        string departmentName;
        string parentName;

        getline(ss, departmentName, '|');
        getline(ss, parentName);
        addDepartment(departmentName, parentName);

    }
    file.close();
}

// preorder root ->children
void DepartmentTree::preorderTraversal(DepartmentNode* node) const{
    if (node == nullptr) {
        return;

    }
    cout << node->name<<endl;
    for (DepartmentNode* child : node->children){
        preorderTraversal(child);
    }
}

//Postorder: children ->root

void DepartmentTree::postorderTraversal(DepartmentNode* node) const{
    if (node == nullptr){
        return;
    }

    for (DepartmentNode* child : node->children){
        postorderTraversal(child);
    }

    cout << node->name<< endl;

    
}

// Level-order: Visit one level at a time
void DepartmentTree::levelOrderTraversal() const {

    if (root == nullptr) {
        return;
    }

    queue<DepartmentNode*> q;

    q.push(root);

    while (!q.empty()) {

        DepartmentNode* current = q.front();
        q.pop();

        cout << current->name << endl;

        for (DepartmentNode* child : current->children) {
            q.push(child);
        }
    }
}

// Count all departments
int DepartmentTree::countDepartments() const {

    if (root == nullptr) {
        return 0;
    }

    int count = 1;

    for (DepartmentNode* child : root->children) {
        // Count each subtree.
        DepartmentTree* unused = nullptr;
        (void)unused;
    }

    // Use level-order traversal to count every node.
    queue<DepartmentNode*> q;
    q.push(root);

    while (!q.empty()) {
        DepartmentNode* current = q.front();
        q.pop();

        for (DepartmentNode* child : current->children) {
            count++;
            q.push(child);
        }
    }

    return count;
}

// Count departments with no children (leaf nodes)
int DepartmentTree::countLeaves(DepartmentNode* node) const {

    if (node == nullptr) {
        return 0;
    }

    if (node->children.empty()) {
        return 1;
    }

    int count = 0;

    for (DepartmentNode* child : node->children) {
        count += countLeaves(child);
    }

    return count;
}

// Calculate tree height
int DepartmentTree::getHeight(DepartmentNode* node) const {

    if (node == nullptr) {
        return -1;
    }

    int maxHeight = -1;

    for (DepartmentNode* child : node->children) {
        int childHeight = getHeight(child);

        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
    }

    return maxHeight + 1;
}

// Return the root
DepartmentNode* DepartmentTree::getRoot() const {
    return root;
}