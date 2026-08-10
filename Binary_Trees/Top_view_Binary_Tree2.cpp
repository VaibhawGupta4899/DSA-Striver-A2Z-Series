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
     * Computes the Top View of a Binary Tree using BFS with Vertical Coordinates (Horizontal Distance).
     * 
     * Definition:
     * The Top View contains the set of nodes visible when looking at the tree 
     * from the top. For each vertical column (horizontal distance `x`), only the 
     * top-most (first encountered during BFS) node is visible.
     * 
     * Algorithm Strategy (Level-Order BFS + Map):
     * 1. Assign the root a horizontal distance `x = 0`.
     * 2. Perform BFS using a queue storing pairs `(Node*, x)`:
     *    - Left child gets horizontal distance `x - 1`.
     *    - Right child gets horizontal distance `x + 1`.
     * 3. Use `map<int, int>` to store `(horizontal_distance -> node_value)`:
     *    - Since BFS processes top-to-bottom, level-by-level, the first node 
     *      recorded at distance `x` (`m.count(x) == 0`) is guaranteed to be the top-most node.
     * 4. Collect values ordered from leftmost column to rightmost column.
     * 
     * Time Complexity:  O(N log N) - N nodes inserted into std::map (O(log N) per insert)
     * Space Complexity: O(N)       - queue and map storage proportional to tree size
     * 
     * @param root Pointer to the root of the binary tree
     * @return vector<int> List of node values visible in the Top View (left-to-right order)
     */
    vector<int> topView(Node* root) {
        vector<int> ans;
        if (root == nullptr) return ans;

        // Map stores (Horizontal Distance 'x' -> First Node Value seen at 'x')
        map<int, int> m;

        // Queue stores (Node*, Horizontal Distance 'x')
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            Node* currNode = p.first;
            int x = p.second;

            // Record node value ONLY if this horizontal distance hasn't been visited yet
            if (m.count(x) == 0) {
                m[x] = currNode->data;
            }

            // Traverse left child (x - 1) and right child (x + 1)
            if (currNode->left != nullptr)  q.push({currNode->left, x - 1});
            if (currNode->right != nullptr) q.push({currNode->right, x + 1});
        }

        // Extract values sorted by horizontal distance key
        for (auto z : m) {
            ans.push_back(z.second);
        }

        return ans;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                   1          (hd = 0)
                 /   \
        (hd=-1) 2     3       (hd = 1)
               / \     \
        (hd=-2) 4   5     7   (hd = 2)
                 /  (hd=0)
          (hd=-1) 6

        Horizontal Distances (hd):
        hd = -2: Node 4
        hd = -1: Node 2 (top-most)
        hd =  0: Node 1 (top-most)
        hd =  1: Node 3
        hd =  2: Node 7
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;

    // Compute Top View (Expected Output: 4 2 1 3 7)
    vector<int> s = sol.topView(root);

    cout << "Top View of Binary Tree: ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << endl; 

    return 0;
}