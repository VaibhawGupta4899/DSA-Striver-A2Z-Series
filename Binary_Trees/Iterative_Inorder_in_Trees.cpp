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

    // Constructor to initialize node value and pointers
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Performs an Iterative Inorder Traversal (Left -> Root -> Right) of a Binary Tree using an explicit Stack.
     * 
     * Strategy:
     * 1. Go as far left as possible, pushing all traversed nodes onto the stack.
     * 2. When a nullptr is reached (no more left children), pop the top node from the stack.
     * 3. Process/store the popped node's value.
     * 4. Move to the popped node's right child and repeat.
     * 
     * Time Complexity:  O(N) - visits each node once
     * Space Complexity: O(H) - where H is the height of the tree (stack depth)
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values in inorder sequence
     */
    vector<int> inord(Node* root) {
        vector<int> inorder;
        if (!root) return inorder;

        stack<Node*> st;

        while (true) {
            // Step 1: Traverse left subtree completely, saving ancestors on stack
            if (root != NULL) {
                st.push(root);
                root = root->left;
            } 
            // Step 2: Left path exhausted; pop from stack and process
            else {
                // If stack is empty and current node is NULL, traversal is complete
                if (st.empty()) break;

                root = st.top();
                st.pop();

                // Process/record the node value (Root step in Left-Root-Right)
                inorder.push_back(root->data);

                // Step 3: Shift focus to the right subtree
                root = root->right;
            }
        }

        return inorder;
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
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);
    root->left->right->right = new Node(7);

    Solution sol;
    vector<int> ans = sol.inord(root);

    // Print resulting Inorder sequence (Expected Output: 4 2 6 5 7 1 3)
    cout << "Inorder Traversal: ";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}