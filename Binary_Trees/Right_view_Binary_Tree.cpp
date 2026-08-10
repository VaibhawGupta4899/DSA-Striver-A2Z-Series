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
     * Computes the Right View of a Binary Tree using BFS with Right-First Exploration.
     * 
     * Definition:
     * The Right View of a binary tree contains the set of nodes visible when the tree 
     * is viewed from the right side (i.e., the rightmost node at each depth level).
     * 
     * Algorithm Strategy (Level-Order BFS with Priority to Right Child):
     * 1. Perform BFS using a queue storing pairs of (Node*, level_depth).
     * 2. Push the `right` child before the `left` child for every dequeued node.
     * 3. For each level depth `x`, the first node encountered is guaranteed to be 
     *    the rightmost node at that level.
     * 4. Record `m[x] = node->data` if level `x` has not been visited yet.
     * 5. Extract values from `m` ordered by level key into the result vector.
     * 
     * Time Complexity:  O(N log N) due to std::map insertion (or O(N) if using vector)
     * Space Complexity: O(N)       for queue and map storage
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values visible in the Right View
     */
    vector<int> rightView(Node* root) {
        vector<int> ans;
        if (root == nullptr) return ans;

        // Map stores (level_depth -> rightmost_node_value)
        map<int, int> m;
        
        // Queue stores (Node*, level_depth)
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            Node* currNode = p.first;
            int level = p.second;

            // Record the first node seen at this level depth
            if (m.count(level) == 0) {
                m[level] = currNode->data;
            }

            // Push RIGHT child first, then LEFT child
            if (currNode->right != nullptr) q.push({currNode->right, level + 1});
            if (currNode->left != nullptr)  q.push({currNode->left, level + 1});
        }

        // Collect elements sorted by level depth key
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

    cout << "Right View of Binary Tree: ";
    for (int x : view) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}