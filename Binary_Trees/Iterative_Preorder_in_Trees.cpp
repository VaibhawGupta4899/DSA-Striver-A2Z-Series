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
     * Performs an Iterative Preorder Traversal (Root -> Left -> Right) of a Binary Tree using a Stack.
     * 
     * Strategy:
     * 1. Push the root node onto the explicit stack.
     * 2. While the stack is not empty, pop the top node and record its value.
     * 3. Push the RIGHT child first, then the LEFT child onto the stack.
     *    (Because a stack is LIFO - Last-In, First-Out - pushing the right child first 
     *     ensures that the left child is popped and processed next).
     * 
     * Time Complexity:  O(N) - visits each node once
     * Space Complexity: O(H) - stack memory proportional to tree height H
     * 
     * @param root Pointer to the root node of the binary tree
     * @return vector<int> List of node values in preorder sequence
     */
    vector<int> preord(Node* root) {
        vector<int> preorder;
        if (!root) return preorder;

        // Explicit stack to simulate call stack recursion
        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            root = st.top();
            st.pop();

            // Process current root value
            preorder.push_back(root->data);

            // Push right child first so left child is processed first (LIFO)
            if (root->right) st.push(root->right);
            if (root->left) st.push(root->left);
        }

        return preorder;
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
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Solution sol;
    vector<int> ans = sol.preord(root);

    // Output resulting Preorder sequence (Expected Output: 1 2 4 5 3)
    cout << "Preorder Traversal: ";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}