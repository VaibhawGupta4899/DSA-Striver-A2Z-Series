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
     * Converts a binary tree so that every non-leaf node satisfies the
     * Children Sum Property: Node Value = Left Child Value + Right Child Value.
     * 
     * Algorithm Strategy (Two-Pass in Single Traversal):
     * 1. Top-Down Pass: If the sum of children is less than the current node's value,
     *    increment the children's values to match the current node's value (preventing value loss).
     * 2. Recurse down both left and right subtrees.
     * 3. Bottom-Up Pass: On backtracking, recompute node value as the exact sum 
     *    of its updated left and right children.
     * 
     * Time Complexity:  O(N) - visits each node once
     * Space Complexity: O(H) - recursion stack proportional to tree height H
     * 
     * @param root Pointer to the root of the binary tree
     */
    void MAXX(Node* root) {
        if (root == nullptr) return;

        // Base case: Leaf nodes don't need modifications
        if (root->left == nullptr && root->right == nullptr) return;

        // Calculate current children sum
        int l = 0, r = 0;
        if (root->left != nullptr) l = root->left->data;
        if (root->right != nullptr) r = root->right->data;

        // Top-Down: If parent value is greater than sum of children,
        // update children values to parent's value to avoid shrinking values lower down
        if (l + r < root->data) {
            if (root->left != nullptr) root->left->data = root->data;
            if (root->right != nullptr) root->right->data = root->data;
        }

        // Recursive calls for left and right subtrees
        MAXX(root->left);
        MAXX(root->right);

        // Bottom-Up: Recalculate node's value based on newly computed children values
        int x = 0, y = 0;
        if (root->left != nullptr) x = root->left->data;
        if (root->right != nullptr) y = root->right->data;

        // Update root data to match the exact sum of its children
        if (root->left != nullptr || root->right != nullptr) {
            root->data = x + y;
        }
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
    
    // Execute Children Sum Property transformation
    sol.MAXX(root);

    return 0;
}