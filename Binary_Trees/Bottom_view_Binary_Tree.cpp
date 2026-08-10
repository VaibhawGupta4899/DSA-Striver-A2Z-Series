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

    // Constructor to initialize a node with a specific value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Computes the Bottom View of a Binary Tree using Breadth-First Search (BFS).
     * 
     * Strategy:
     * - Perform a level-order traversal (BFS) using a queue.
     * - Track the vertical distance (HD - Horizontal Distance) for each node:
     *     - Root is at HD = 0
     *     - Left child is at HD - 1
     *     - Right child is at HD + 1
     * - Use an ordered map (m[HD] = node->data) to continuously overwrite 
     *   and keep the last visited node at each vertical distance.
     * 
     * @param root Pointer to the root node of the binary tree
     * @return vector<int> Nodes visible from the bottom view, ordered left to right
     */
    vector<int> balc(Node* root) {
        vector<int> ans;
        if (root == nullptr) return ans;

        // Map to store (Horizontal Distance -> Last Node Value at that distance)
        // std::map automatically keeps keys sorted (leftmost to rightmost HD)
        map<int, int> m;

        // Queue for BFS: stores pairs of (Node*, Horizontal Distance)
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            Node* currNode = p.first;
            int x = p.second; // Current Horizontal Distance

            // Overwrite the entry at HD = x with the latest node's value.
            // Since BFS visits top-to-bottom, the final value remaining in map[x] 
            // will be the bottom-most node at horizontal distance x.
            m[x] = currNode->data;

            // Enqueue left child with HD = x - 1
            if (currNode->left != nullptr) {
                q.push({currNode->left, x - 1});
            }

            // Enqueue right child with HD = x + 1
            if (currNode->right != nullptr) {
                q.push({currNode->right, x + 1});
            }
        }

        // Extract nodes from map in ascending order of horizontal distance
        for (auto z : m) {
            ans.push_back(z.second);
        }

        return ans;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1
                 /   \
                2     3
               / \   / \
              4   5 6   7
                 / \
                8   9
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->right->left = new Node(8);
    root->left->right->right = new Node(9);

    Solution sol;
    vector<int> s = sol.balc(root);

    // Print bottom view output
    cout << "Bottom View: ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << endl; 

    return 0;
}