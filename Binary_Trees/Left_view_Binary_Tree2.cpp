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
     * Helper function: Recursively computes the Left View of a Binary Tree using Preorder DFS.
     * 
     * Strategy:
     * - Track the current tree depth (`lev`).
     * - Whenever `lev == ans.size()`, we are encountering the first (leftmost) node at this level.
     * - Recurse down `left` child first, then `right` child.
     * 
     * Note: If you swap the recursive calls to visit `root->right` before `root->left`,
     * this exact same algorithm computes the Right View of the Binary Tree instead.
     * 
     * @param root Pointer to the current tree node
     * @param ans  Reference to vector storing the leftmost node values
     * @param lev  Current depth/level in the binary tree (starts at 0)
     */
    void righttrv(Node* root, vector<int>& ans, int lev) {
        if (root == nullptr) return;

        // First time reaching depth 'lev', add the leftmost node value
        if (lev == ans.size()) {
            ans.push_back(root->data);
        }

        // Traverse left child first to ensure left side is captured for each level
        righttrv(root->left, ans, lev + 1);
        righttrv(root->right, ans, lev + 1);
    }

    /**
     * Wrapper function to compute the Left View of a Binary Tree.
     * 
     * Time Complexity:  O(N) - visits each node at most once
     * Space Complexity: O(H) - where H is the height of the tree (recursion stack)
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values visible from the left side
     */
    vector<int> balc(Node* root) {
        vector<int> ans;
        righttrv(root, ans, 0);
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
    vector<int> s = sol.balc(root);

    // Output resulting Left View sequence (Expected Output: 1 2 4 6)
    cout << "Left View: ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << endl; 

    return 0;
}