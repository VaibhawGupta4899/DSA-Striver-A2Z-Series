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

    // Constructor to initialize node value and child pointers
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Performs an Iterative Postorder Traversal (Left -> Right -> Root) using a SINGLE STACK.
     * 
     * Strategy:
     * 1. Traverse left as far as possible, pushing nodes onto the stack.
     * 2. When a nullptr is reached, peek at the top node's right child:
     *    a. If a right child exists, shift focus to it and repeat step 1.
     *    b. If no right child exists (or it was just processed), pop and process the node.
     * 3. Backtrack up right children by continuously popping parents whose right children
     *    matches the node just popped.
     * 
     * Time Complexity:  O(N) - visits each node once
     * Space Complexity: O(H) - single stack proportional to tree height H
     * 
     * @param root Pointer to the root node of the binary tree
     * @return vector<int> List of node values in postorder sequence
     */
    vector<int> postord(Node* root) {
        vector<int> ans;
        if (root == nullptr) return ans;

        stack<Node*> st;

        while (root != nullptr || !st.empty()) {
            // Step 1: Traverse left subtree completely, saving ancestors on stack
            if (root != nullptr) {
                st.push(root);
                root = root->left;
            } 
            // Step 2: Left branch exhausted; inspect right subtree or process current node
            else {
                Node* temp = st.top()->right;

                // Case A: No right child exists -> process the top node
                if (temp == nullptr) {
                    temp = st.top();
                    st.pop();
                    ans.push_back(temp->data);

                    // Backtrack: If the node just popped was the right child of the top element,
                    // it means the right subtree is complete, so pop and process the parent.
                    while (!st.empty() && temp == st.top()->right) {
                        temp = st.top();
                        st.pop();
                        ans.push_back(temp->data);
                    }
                } 
                // Case B: Right child exists -> move to explore the right subtree
                else {
                    root = temp;
                }
            }
        }
        return ans;
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
    vector<int> ans = sol.postord(root);

    // Output resulting Postorder sequence (Expected Output: 3 6 5 4 2 8 7 1)
    cout << "Postorder Traversal (Single Stack): ";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}