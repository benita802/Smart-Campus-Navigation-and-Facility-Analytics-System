
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

using namespace std;

struct DepartmentNode {
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;

    DepartmentNode(string departmentName) {
        name = departmentName;
        parent = nullptr;
    }
};

class DepartmentTree {
private:
    DepartmentNode* root;

public:
    DepartmentTree();

    void addDepartment(const string& name, const string& parentName);
    void loadDepartments(const string& filename);

    void preorderTraversal(DepartmentNode* node) const;
    void postorderTraversal(DepartmentNode* node) const;
    void levelOrderTraversal() const;

    int countDepartments() const;
    int countLeaves(DepartmentNode* node) const;
    int getHeight(DepartmentNode* node) const;

    DepartmentNode* getRoot() const;
};

#endif // DEPARTMENTTREE_H

