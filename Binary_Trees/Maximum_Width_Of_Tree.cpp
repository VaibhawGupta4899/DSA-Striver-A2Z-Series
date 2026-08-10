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
     * Calculates the Maximum Width of a Binary Tree.
     * 
     * The width of a level is defined as the length between the leftmost and 
     * rightmost non-null nodes, including any null nodes between them.
     * 
     * Strategy (BFS Level-Order Traversal with 0-Based Heap Indexing):
     * 1. Assign index 0 to the root.
     * 2. For a parent at index `c`:
     *    - Left child index  = 2 * c + 1
     *    - Right child index = 2 * c + 2
     * 3. Normalization: To prevent integer overflow on deep/skewed trees, subtract 
     *    the level's minimum index (`mmin`) from all indices at that level.
     * 4. Width at current level = `last_index - first_index + 1`.
     * 
     * Time Complexity:  O(N) - visits every node once
     * Space Complexity: O(N) - queue stores nodes per level (up to N/2 nodes)
     * 
     * @param root Pointer to the root node of the binary tree
     * @return int Maximum width among all levels
     */
    int MAXX(Node* root) {
        int m = 0; // Tracks the overall maximum width
        if (root == nullptr) return m;

        // Queue stores pair: <Node*, Index at current level>
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            int n = q.size();
            
            // Normalize indices using the first node's index to avoid integer overflow
            int mmin = q.front().second;
            int first = 0, last = 0;

            for (int i = 0; i < n; i++) {
                // Normalized index for current node
                int c = q.front().second - mmin;
                Node* x = q.front().first;
                q.pop();

                // Track indices of the first and last node at this level
                if (i == 0) first = c;
                if (i == n - 1) last = c;

                // Push left child with index (2 * c + 1)
                if (x->left != nullptr) {
                    q.push({x->left, 2 * c + 1});
                }

                // Push right child with index (2 * c + 2)
                if (x->right != nullptr) {
                    q.push({x->right, 2 * c + 2});
                }
            } 

            // Update global maximum width
            m = max(m, last - first + 1);
        }

        return m;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1              (Width = 1)
                 /   \
                2     3          (Width = 2)
               / \   / \
              4   5 8   9        (Width = 4)
                 / \
                6   7            (Width = 2)
    */
    vector<int> ans;
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(8);
    root->right->right = new Node(9);
    root->left->right->left = new Node(6);
    root->left->right->right = new Node(7);

    Solution sol;

    // Compute and print maximum width (Expected Output: 4)
    int x = sol.MAXX(root);
    cout << "Maximum Width of Binary Tree: " << x << endl;

    return 0;
}