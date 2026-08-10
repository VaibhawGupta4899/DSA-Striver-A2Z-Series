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
     * Recursively calculates the height (maximum depth) of a binary tree.
     * 
     * Base Case: An empty node (nullptr) has a height of 0.
     * Recursive Step: Height = 1 + max(left_subtree_height, right_subtree_height)
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
                   1
                 /   \
                2     7
               / \   /
              3   4 8
                   \
                    5
                     \
                      6
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

    // Calculate heights of the left and right subtrees under the root
    int h = sol.height(root->left);   // Height of left subtree (rooted at Node 2)
    int g = sol.height(root->right);  // Height of right subtree (rooted at Node 7)

    // Check if the difference between the left and right subtree heights is strictly equal to 1
    if ((h - g) == 1 || (g - h) == 1) {
        cout << true << endl;  // Outputs 1 in standard C++ stream
    } else {
        cout << false << endl; // Outputs 0 in standard C++ stream
    }

    return 0;
}