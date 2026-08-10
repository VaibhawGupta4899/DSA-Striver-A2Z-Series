#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Definition for a Binary Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a node with a given value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Finds the Lowest Common Ancestor (LCA) of two node values (p and q) in a Binary Tree.
     * 
     * Algorithm Strategy (Post-Order Traversal Depth First Search):
     * 1. Base Cases:
     *    - If current node is nullptr, return 0 (not found).
     *    - If current node matches value 'p' or 'q', return that value (found target).
     * 2. Recurse down both left and right subtrees to find 'p' and 'q'.
     * 3. Decision Logic:
     *    - If BOTH left and right recursion return non-zero values, current node is the LCA.
     *    - If only ONE returns non-zero, propagate that found node value upward.
     *    - If NEITHER returns non-zero, return 0.
     * 
     * Time Complexity:  O(N) - in the worst case, visits every node once
     * Space Complexity: O(H) - recursion stack memory proportional to tree height H
     * 
     * @param root Pointer to the current tree node
     * @param p    Value of the first target node
     * @param q    Value of the second target node
     * @return int  Value of the Lowest Common Ancestor node (or 0 if not found)
     */
    int LCA(Node* root, int p, int q) {
        // Base case: empty node
        if (root == nullptr) return 0;

        // Base case: node matches either p or q
        if (root->data == p) return p;
        if (root->data == q) return q;

        // Recursive search in left and right subtrees
        int a = LCA(root->left, p, q);
        int b = LCA(root->right, p, q);

        // If 'p' and 'q' are found in separate branches of the current node,
        // this node is the Lowest Common Ancestor
        if (a != 0 && b != 0) return root->data;

        // If target is found in only one subtree, return that result upwards
        if (a != 0) return a;
        if (b != 0) return b;

        // Neither p nor q found in this branch
        return 0;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1
                 /   \
                2     3
               / \   / \
              4   5 8   9
                 / \
                6   7
    */
    vector<int> ans;
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(8);
    root->right->right = new Node(9);
    root->left->right->left = new Node(6);
    root->left->right->right = new Node(7);

    Solution sol;
    int p, q;

    // Read values of nodes p and q to find their LCA
    // Example Input: 6 7  -> Output: 5
    // Example Input: 4 7  -> Output: 2
    cin >> p >> q;

    int x = sol.LCA(root, p, q);

    // Print LCA node data
    cout << "Lowest Common Ancestor: " << x << endl;

    return 0;
}