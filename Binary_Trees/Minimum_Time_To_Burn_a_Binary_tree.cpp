#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Definition for a Binary Tree Node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize a node with a given value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * Helper function: Maps child nodes to their respective parent nodes using Level-Order Traversal (BFS).
     * 
     * @param root Pointer to the root of the tree
     * @param m    Reference to map storing child-to-parent relationships
     */
    void storeback(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& m) {
        m[root] = nullptr;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* x = q.front();
            q.pop();

            if (x->left) {
                q.push(x->left);
                m[x->left] = x;
            }
            if (x->right) {
                q.push(x->right);
                m[x->right] = x;
            }
        }
    }

    /**
     * Helper function: Finds and returns the pointer to the node with value equal to target `t`.
     * 
     * @param root   Pointer to the root of the tree
     * @param target Integer value to locate
     * @return TreeNode* Pointer to the matching node, or nullptr if not found
     */
    TreeNode* findNode(TreeNode* root, int target) {
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* h = q.front();
            q.pop();

            if (h->val == target) return h;
            if (h->left) q.push(h->left);
            if (h->right) q.push(h->right);
        }
        return nullptr;
    }

    /**
     * Calculates the minimum time required to burn the entire binary tree starting from node `t`.
     * 
     * Strategy (3-Directional BFS):
     * 1. Build parent mappings (`child -> parent`) so nodes can spread fire upwards.
     * 2. Locate the starting target node `x`.
     * 3. Perform a standard BFS starting from `x` burning outward in 3 possible directions at each second:
     *    - Left child
     *    - Right child
     *    - Parent node
     * 4. Increment time level-by-level until all accessible nodes are burned.
     * 
     * Time Complexity:  O(N) - visits each node a constant number of times across BFS passes
     * Space Complexity: O(N) - stores node pointers in queue and unordered maps
     * 
     * @param root Pointer to the tree root
     * @param t    Value of the target node where the fire starts
     * @return int Minimum time in seconds to burn the entire tree
     */
    int burn(TreeNode* root, int t) {
        if (root == nullptr) return -1;

        // Step 1: Map parents for upward traversal
        unordered_map<TreeNode*, TreeNode*> m;
        storeback(root, m);

        // Step 2: Find target node reference
        TreeNode* x = findNode(root, t);
        if (!x) return -1; // Target node not present in tree

        // Step 3: Perform BFS outward from target node
        queue<TreeNode*> q;
        unordered_map<TreeNode*, bool> vis;

        q.push(x);
        vis[x] = true;
        int time = 0;

        while (!q.empty()) {
            int n = q.size();

            for (int i = 0; i < n; i++) {
                TreeNode* z = q.front();
                q.pop();

                // Spread fire to left child
                if (z->left && !vis[z->left]) {
                    q.push(z->left);
                    vis[z->left] = true;
                }

                // Spread fire to right child
                if (z->right && !vis[z->right]) {
                    q.push(z->right);
                    vis[z->right] = true;
                }

                // Spread fire upward to parent
                if (m[z] && !vis[m[z]]) {
                    q.push(m[z]);
                    vis[m[z]] = true;
                }
            }
            time++;
        }

        // Subtract 1 because `time` increments once more when processing the final level
        return time - 1;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1
                 /   \
                2     3
               /     / \
              4     5   6
               \
                7
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->left->right = new TreeNode(7);

    Solution sol;
    int t;

    // Read target node value (e.g., Input: 2 -> Expected Output: 4)
    cin >> t;

    int a = sol.burn(root, t);
    cout << "Time to burn tree: " << a << " units" << endl;

    return 0;
}