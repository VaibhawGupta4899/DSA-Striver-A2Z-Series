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
     * Helper Function: Preorder-like DFS traversal prioritizing the right child first.
     * 
     * Strategy:
     * 1. Track current recursion depth with `level`.
     * 2. Compare `level` with `ans.size()`. When `level == ans.size()`, it indicates 
     *    we are encountering this depth level for the VERY FIRST time.
     * 3. Because we recurse into the `right` subtree before the `left` subtree, 
     *    the first node visited at any depth level is guaranteed to be the rightmost node.
     * 4. Recurse left afterwards to cover levels that have no right descendants.
     * 
     * @param root  Pointer to current tree node
     * @param ans   Reference vector to store right view values
     * @param level Current tree depth (starts at 0)
     */
    void rightViewDFS(Node* root, vector<int>& ans, int level) {
        if (root == nullptr) return;

        // First node visited at this level depth -> add to output
        if (level == ans.size()) {
            ans.push_back(root->data);
        }

        // Recurse RIGHT subtree first, then LEFT subtree
        rightViewDFS(root->right, ans, level + 1);
        rightViewDFS(root->left, ans, level + 1);
    }

    /**
     * Computes the Right View of a Binary Tree using Optimal Recursive DFS.
     * 
     * Definition:
     * The Right View contains the set of nodes visible when looking at the tree 
     * from the right side (the rightmost node at each depth level).
     * 
     * Time Complexity:  O(N) - visits each node at most once
     * Space Complexity: O(H) - recursion call stack space proportional to tree height H
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values visible from the right side
     */
    vector<int> rightView(Node* root) {
        vector<int> ans;
        rightViewDFS(root, ans, 0);
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

    // Compute Right View (Expected Output: 1 3 7 6)
    vector<int> view = sol.rightView(root);

    cout << "Right View of Binary Tree (DFS): ";
    for (int x : view) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}