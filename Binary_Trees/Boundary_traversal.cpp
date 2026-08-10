#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Definition of a Binary Tree Node
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
     * Helper function: Traverses non-leaf nodes in post-order (bottom-up).
     * Used to collect the right boundary nodes in reverse order.
     * 
     * @param root Pointer to the current node
     * @param ans  Reference to the output vector storing boundary values
     */
    void rever(Node* root, vector<int>& ans) {
        if (root == nullptr) return;
        
        // Skip leaf nodes to prevent duplicate inclusion
        if (root->left == nullptr && root->right == nullptr) return;

        rever(root->left, ans);
        rever(root->right, ans);
        
        // Add non-leaf node data in bottom-up sequence
        ans.push_back(root->data);
    }

    /**
     * Helper function: Performs a modified post-order traversal to collect all leaf nodes.
     * Traverses the tree left-to-right and appends only leaf nodes.
     * 
     * @param root Pointer to the current node
     * @param ans  Reference to the output vector storing boundary values
     */
    void postorder(Node* root, vector<int>& ans) {
        if (root == nullptr) return;

        postorder(root->left, ans);
        postorder(root->right, ans);

        // Append to result only if the node is a leaf
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(root->data);
        }
    }

    /**
     * Computes the Boundary Traversal of a Binary Tree in anti-clockwise order:
     * 1. Left boundary (top-down, excluding leaf nodes).
     * 2. All leaf nodes (left-to-right).
     * 3. Right boundary (bottom-up, excluding leaf nodes).
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> Array containing the boundary traversal values
     */
    vector<int> balc(Node* root) {
        if (root == nullptr) return {};

        Node* nod1 = root;
        Node* nod2 = root->right;
        vector<int> ans;

        // Base case: Single node tree
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(root->data);
        }

        // Step 1: Collect Left Boundary (top-down, excluding leaves)
        while (!(root->left == nullptr && root->right == nullptr)) {
            ans.push_back(root->data);
            if (root->left) root = root->left;
            else if (root->right) root = root->right;
        }

        // Step 2: Collect all Leaf Nodes (left-to-right)
        postorder(nod1, ans);

        // Step 3: Collect Right Boundary (bottom-up, excluding leaves)
        rever(nod2, ans);

        return ans;
    }  
};

int main() {
    /*
        Constructing the following Binary Tree:
                      1
                    /   \
                   2     7
                  /       \
                 3         8
                  \       /
                   4     9
                  / \   / \
                 5   6 10 11
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(7);
    root->left->left = new Node(3);
    root->left->left->right = new Node(4);
    root->left->left->right->left = new Node(5);
    root->left->left->right->right = new Node(6);
    root->right->right = new Node(8);
    root->right->right->left = new Node(9);
    root->right->right->left->left = new Node(10);
    root->right->right->left->right = new Node(11);

    Solution sol;
    vector<int> s = sol.balc(root);

    // Output the resulting boundary traversal values
    cout << "Boundary Traversal: ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << endl; 

    return 0;
}