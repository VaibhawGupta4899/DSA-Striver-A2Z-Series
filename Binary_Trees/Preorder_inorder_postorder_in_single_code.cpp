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
     * Computes Preorder, Inorder, and Postorder Traversals in a SINGLE PASS using 1 Stack.
     * 
     * Strategy (State-Based Stack Traversal):
     * - Push pair `(root, 1)` onto stack.
     * - While stack is not empty, inspect the top element `(node, state)`:
     *   - State == 1: Record node in PREORDER vector. Increment state to 2, push back to stack, push left child (state 1).
     *   - State == 2: Record node in INORDER vector. Increment state to 3, push back to stack, push right child (state 1).
     *   - State == 3: Record node in POSTORDER vector. Pop node permanently (do not re-push).
     * 
     * Time Complexity:  O(N) - each node is processed exactly 3 times
     * Space Complexity: O(H) - auxiliary stack space proportional to tree height H
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<vector<int>> List containing three vectors: [0] = Preorder, [1] = Inorder, [2] = Postorder
     */
    vector<vector<int>> preInPostTraversal(Node* root) {
        vector<vector<int>> ans;
        vector<int> pre, in, post;

        if (root == nullptr) return ans;

        // Stack stores pairs of (Node*, State Counter: 1, 2, or 3)
        stack<pair<Node*, int>> st;
        st.push({root, 1});

        while (!st.empty()) {
            auto it = st.top();
            st.pop();

            // State 1: Preorder step -> advance state to 2 & explore left subtree
            if (it.second == 1) {
                pre.push_back(it.first->data);
                it.second++;
                st.push(it);

                if (it.first->left != nullptr) {
                    st.push({it.first->left, 1});
                }
            }
            // State 2: Inorder step -> advance state to 3 & explore right subtree
            else if (it.second == 2) {
                in.push_back(it.first->data);
                it.second++;
                st.push(it);

                if (it.first->right != nullptr) {
                    st.push({it.first->right, 1});
                }
            }
            // State 3: Postorder step -> record value & pop permanently
            else {
                post.push_back(it.first->data);
            }
        }

        ans.push_back(pre);
        ans.push_back(in);
        ans.push_back(post);

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
    vector<vector<int>> ans = sol.preInPostTraversal(root);

    vector<int> Pre = ans[0];
    vector<int> In = ans[1];
    vector<int> Post = ans[2];

    // Output Preorder sequence (Expected Output: 1 2 3 4 5 6 7 8)
    cout << "Preorder Traversal:  ";
    for (int x : Pre) cout << x << " ";
    cout << endl;

    // Output Inorder sequence (Expected Output: 3 2 4 5 6 1 8 7)
    cout << "Inorder Traversal:   ";
    for (int x : In) cout << x << " ";
    cout << endl;

    // Output Postorder sequence (Expected Output: 3 6 5 4 2 8 7 1)
    cout << "Postorder Traversal: ";
    for (int x : Post) cout << x << " ";
    cout << endl;

    return 0;
}