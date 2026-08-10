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
     * Performs an Iterative Postorder Traversal (Left -> Right -> Root) of a Binary Tree using 2 Stacks.
     * 
     * Algorithm Strategy:
     * 1. Use `st1` to traverse nodes in Root -> Right -> Left sequence.
     * 2. Push each processed node into `st2` (which acts as a reverse accumulator).
     * 3. Popping all elements from `st2` yields the exact Left -> Right -> Root (Postorder) sequence.
     * 
     * Time Complexity:  O(N) - visits every node once
     * Space Complexity: O(N) - requires 2 stacks storing up to N nodes
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values in postorder sequence
     */
    vector<int> postord(Node* root) {
        vector<int> postorder;
        if (!root) return postorder;

        // st1: Helper stack for level/branch traversal
        // st2: Accumulator stack to reverse the traversal order
        stack<Node*> st1, st2;

        st1.push(root);

        // Step 1: Traverse the tree and push nodes into st2 in Root -> Right -> Left order
        while (!st1.empty()) {
            root = st1.top();
            st1.pop();

            st2.push(root);

            // Push left child first so right child is popped first from st1
            if (root->left != nullptr) {
                st1.push(root->left);
            }
            if (root->right != nullptr) {
                st1.push(root->right);
            }
        }

        // Step 2: Extract nodes from st2 to get Left -> Right -> Root order
        while (!st2.empty()) {
            postorder.push_back(st2.top()->data);
            st2.pop();
        }

        return postorder;
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
    vector<int> ans = sol.postord(root);

    // Output resulting Postorder sequence (Expected Output: 4 6 7 5 2 3 1)
    cout << "Postorder Traversal: ";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}