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
    // Vectors to store structural traversals of left and right subtrees
    vector<int> left;
    vector<int> right;

    /**
     * Traverses the right subtree in a mirrored post-order fashion:
     * - Visit Right child
     * - Record Node Data
     * - Visit Left child
     * - Record Node Data
     * Pushes -1 for nullptr to preserve tree structure.
     * 
     * @param root Pointer to node in right subtree
     */
    void rightone(Node* root) {
        if (root == nullptr) {
            right.push_back(-1); // Null marker to preserve structural representation
            return; 
        }
        rightone(root->right);
        right.push_back(root->data);
        rightone(root->left);
        right.push_back(root->data);
    }

    /**
     * Traverses the left subtree in a standard post-order fashion:
     * - Visit Left child
     * - Record Node Data
     * - Visit Right child
     * - Record Node Data
     * Pushes -1 for nullptr to preserve tree structure.
     * 
     * @param root Pointer to node in left subtree
     */
    void leftone(Node* root) {
        if (root == nullptr) {
            left.push_back(-1); // Null marker to preserve structural representation
            return;
        }
        leftone(root->left);
        left.push_back(root->data);
        leftone(root->right);
        left.push_back(root->data);
    }

    /**
     * Checks whether a Binary Tree is Symmetric (a mirror image of itself around its center).
     * 
     * Strategy:
     * 1. Check quick root base cases.
     * 2. Traverse the left subtree (Left->Root->Right sequence) and right subtree (Right->Root->Left sequence).
     * 3. Compare the generated traversal vectors for identical length and values.
     * 
     * @param root Pointer to the root of the tree
     * @return true if the tree is symmetric, false otherwise
     */
    bool balc(Node* root) {
        if (root == nullptr) return true;
        if (root->right == nullptr && root->left == nullptr) return true;
        
        // Asymmetric if only one child exists at the root
        if (root->left == nullptr || root->right == nullptr) return false;

        // Collect mirrored traversals for both subtrees
        leftone(root->left);
        rightone(root->right);

        // Subtrees must produce traversals of identical size
        if (left.size() != right.size()) return false;

        // Element-wise comparison of the symmetric traversals
        for (int i = 0; i < left.size(); i++) {
            if (left[i] != right[i]) return false;
        }

        return true;
    }
};

int main() {
    /*
        Constructing a Symmetric Binary Tree:
                   1
                 /   \
                2     2
               / \   / \
              3   4 4   3
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(4);
    root->right->right = new Node(3);

    Solution sol;
    bool s = sol.balc(root);

    // Prints 1 (true) for symmetric tree, 0 (false) otherwise
    cout << s << endl; 

    return 0;
}