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
     * Helper function: Recursively checks if two subtrees are mirror images of each other.
     * 
     * Conditions for symmetry between two nodes (rtl and rtr):
     * 1. Both nodes are nullptr (Base case: symmetric).
     * 2. Both nodes exist and share identical data values.
     * 3. Left child of left node matches Right child of right node.
     * 4. Right child of left node matches Left child of right node.
     * 
     * @param rtl Pointer to a node in the left sub-branch
     * @param rtr Pointer to a node in the right sub-branch
     * @return true if subtrees are symmetric, false otherwise
     */
    bool check(Node* rtl, Node* rtr) {
        // Base case: if either is nullptr, both must be nullptr to be symmetric
        if (rtl == nullptr || rtr == nullptr) return rtl == rtr;

        // Data mismatch means subtrees are not mirror images
        if (rtl->data != rtr->data) return false;

        // Mirror check: left-to-right and right-to-left
        return check(rtl->left, rtr->right) && check(rtl->right, rtr->left);
    }

    /**
     * Checks whether a Binary Tree is Symmetric (a mirror image around its root).
     * 
     * Time Complexity:  O(N) - visits every node once in worst case.
     * Space Complexity: O(H) - call stack proportional to tree height H.
     * 
     * @param root Pointer to the root of the binary tree
     * @return true if tree is symmetric, false otherwise
     */
    bool balc(Node* root) {
        // An empty tree is symmetric; otherwise compare left and right subtrees
        return root == nullptr || check(root->left, root->right);
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

    // Output: 1 (true) for symmetric tree, 0 (false) otherwise
    cout << s << endl; 

    return 0;
}