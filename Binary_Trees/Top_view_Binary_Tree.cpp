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
     * Helper Function: Recursively traverses to the leftmost node first 
     * and collects values during recursion unwinding (bottom-up order).
     * 
     * @param root Pointer to current tree node
     * @param ans  Reference vector to store collected values
     */
    void leftall(Node* root, vector<int>& ans) {
        if (root == nullptr) return;

        // Recurse down left child first
        leftall(root->left, ans);

        // Collect node data during unwinding phase (bottom-up)
        ans.push_back(root->data);
    }

    /**
     * Helper Function: Recursively traverses along the right child path 
     * and collects values top-down.
     * 
     * @param root Pointer to current tree node
     * @param ans  Reference vector to store collected values
     */
    void rightall(Node* root, vector<int>& ans) {
        if (root == nullptr) return;

        // Collect node data first (top-down)
        ans.push_back(root->data);

        // Recurse down right child
        rightall(root->right, ans);
    }

    /**
     * Computes the Outer Boundary Path (Left Spine bottom-up + Right Spine top-down).
     * 
     * Strategy:
     * 1. Traverse left child pointers to the deepest left child, then collect nodes 
     *    bottom-up ending at `root` (`leftall`).
     * 2. Traverse right child pointers starting from `root->right` top-down (`rightall`).
     * 
     * Time Complexity:  O(H) - visits only nodes along the height boundaries (H = height of tree)
     * Space Complexity: O(H) - recursion call stack space proportional to tree height H
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> Sequence of left boundary (bottom-up) + right boundary (top-down)
     */
    vector<int> balc(Node* root) {
        if (root == nullptr) return {};

        vector<int> ans;

        // Step 1: Collect left spine from deepest left child up to root
        leftall(root, ans);

        // Step 2: Collect right spine from root's right child downwards
        rightall(root->right, ans);

        return ans;
    }  
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1
                 /   \
                2     3
               / \     \
              4   5     7
                 /
                6
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;

    // Compute Left Spine (bottom-up) + Right Spine (top-down)
    // Expected Output: 4 2 1 3 7
    vector<int> s = sol.balc(root);

    cout << "Outer Boundary Path: ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << endl; 

    return 0;
}