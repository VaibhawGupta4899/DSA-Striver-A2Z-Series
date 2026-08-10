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
     * Finds the path from the root node to a target node with value `k` using DFS Backtracking.
     * 
     * Strategy (Backtracking DFS):
     * 1. If current node is null, return false (path not found on this branch).
     * 2. Push current node's value into `ans` vector assuming it might be on the path.
     * 3. Base Case: If current node matches target `k`, path is complete; return true.
     * 4. Recursively check left and right subtrees:
     *    - If target node exists in either child branch, return true up the stack.
     * 5. Backtrack Step: If target node is not found in either subtree, pop current node 
     *    from `ans` and return false.
     * 
     * Time Complexity:  O(N) - in the worst case visits all nodes once
     * Space Complexity: O(H) - recursion stack and path array proportional to tree height H
     * 
     * @param root Pointer to current tree node
     * @param ans  Reference vector storing the path elements from root to target
     * @param k    Target integer value to search for
     * @return bool True if node exists and path is constructed, False otherwise
     */
    bool path(Node* root, vector<int>& ans, int k) {
        if (root == nullptr) return false;

        // Add current node to potential path
        ans.push_back(root->data);

        // Found target node
        if (root->data == k) return true;

        // Search left and right subtrees
        bool l = path(root->left, ans, k);
        bool r = path(root->right, ans, k);

        // If target is found in left or right branch, retain path and return true
        if (l || r) return true;

        // Backtrack: target not present in subtrees of this node
        ans.pop_back();
        return false;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1
                 /   \
                2     3
               / \
              4   5
                 / \
                6   7
    */
    vector<int> ans;
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);
    root->left->right->right = new Node(7);

    Solution sol;
    int k;

    // Read target node value
    // Example Input: 7  -> Output: 1 2 5 7
    // Example Input: 4  -> Output: 1 2 4
    // Example Input: 9  -> Output: Node not found
    cin >> k;

    bool found = sol.path(root, ans, k);

    if (found) {
        cout << "Path from Root to Node " << k << ": ";
        for (int x : ans) {
            cout << x << " ";
        }
        cout << endl;
    } else {
        cout << "Node not found" << endl;
    }

    return 0;
}