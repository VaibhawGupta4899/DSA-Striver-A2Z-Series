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
     * Recursively calculates the Height (Maximum Depth) of a Binary Tree.
     * 
     * Strategy (Depth-First Search):
     * 1. Base Case: An empty node (nullptr) has a height of 0.
     * 2. Recurse down the left and right subtrees to compute their respective heights.
     * 3. Height at current node = 1 + maximum(height of left subtree, height of right subtree).
     * 
     * Time Complexity:  O(N) - visits each node in the tree once
     * Space Complexity: O(H) - call stack memory proportional to tree height H
     * 
     * @param root Pointer to the root node of the binary tree
     * @return int Maximum depth of the tree from the given node
     */
    int height(Node* root) {
        if (root == nullptr) return 0;

        int l = height(root->left);
        int r = height(root->right);

        return 1 + max(l, r);
    }  
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1              (Level 1)
                 /   \
                2     7           (Level 2)
               / \   /
              3   4 8             (Level 3)
                   \
                    5             (Level 4)
                     \
                      6           (Level 5)
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(7);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    root->left->right->right = new Node(5);
    root->left->right->right->right = new Node(6);
    root->right->left = new Node(8);

    Solution sol;

    // Compute and print total height of the tree (Expected Output: 5)
    int h = sol.height(root);
    cout << "Height of Binary Tree: " << h << endl;

    return 0;
}