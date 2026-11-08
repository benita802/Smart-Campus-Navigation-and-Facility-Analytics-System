
#include "../include/DepartmentTree.h"

#include <iostream>

using namespace std;

int main() {

    DepartmentTree tree;

    tree.loadDepartments("data/departments.txt");

    cout << "\n--- PREORDER TRAVERSAL ---\n";
    tree.preorderTraversal(tree.getRoot());

    cout << "\n--- POSTORDER TRAVERSAL ---\n";
    tree.postorderTraversal(tree.getRoot());

    cout << "\n--- LEVEL-ORDER TRAVERSAL ---\n";
    tree.levelOrderTraversal();

    cout << "\n--- DEPARTMENT STATISTICS ---\n";

    cout << "Total departments: "
         << tree.countDepartments() << endl;

    cout << "Leaf departments: "
         << tree.countLeaves(tree.getRoot()) << endl;

    cout << "Tree height: "
         << tree.getHeight(tree.getRoot()) << endl;

    return 0;
}
