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
     * Helper function: Maps child nodes to their respective parent nodes using Level-Order Traversal (BFS).
     * 
     * @param root Pointer to the root of the tree
     * @param parentMap Reference to unordered_map storing child-to-parent relationships
     */
    void markParents(Node* root, unordered_map<Node*, Node*>& parentMap) {
        parentMap[root] = nullptr;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left) {
                q.push(current->left);
                parentMap[current->left] = current;
            }
            if (current->right) {
                q.push(current->right);
                parentMap[current->right] = current;
            }
        }
    }

    /**
     * Helper function: Finds and returns the pointer to the node with value equal to target `target`.
     * 
     * @param root   Pointer to the root of the tree
     * @param target Integer value to locate
     * @return Node* Pointer to the matching node, or nullptr if not found
     */
    Node* findTargetNode(Node* root, int target) {
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->data == target) return current;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    /**
     * Finds all nodes at distance `k` from a given `target` node in a Binary Tree.
     * 
     * Strategy (Radial BFS with Parent Pointers):
     * 1. Build child-to-parent mappings using BFS so nodes can traverse upward to parent nodes.
     * 2. Locate the pointer to the `target` node.
     * 3. Perform a radial BFS outward starting from the `target` node across 3 directions:
     *    - Left child
     *    - Right child
     *    - Parent node
     * 4. Stop when `dist == k`. The remaining nodes in the queue are at exact distance `k`.
     * 
     * Time Complexity:  O(N) - visits each node a constant number of times across BFS passes
     * Space Complexity: O(N) - stores node pointers in parent map, visited map, and BFS queue
     * 
     * @param root   Pointer to the root of the tree
     * @param k      Target radial distance
     * @param target Value of the starting node
     * @return vector<int> List of node values at distance `k`
     */
    vector<int> distanceK(Node* root, int k, int target) {
        if (root == nullptr) return {};

        // Step 1: Map parents for upward radial traversal
        unordered_map<Node*, Node*> parentMap;
        markParents(root, parentMap);

        // Step 2: Locate target node pointer
        Node* targetNode = findTargetNode(root, target);
        if (!targetNode) return {};

        // Step 3: Radial BFS starting from target node
        queue<Node*> q;
        unordered_map<Node*, bool> visited;

        q.push(targetNode);
        visited[targetNode] = true;
        int currentDistance = 0;

        while (!q.empty()) {
            int levelSize = q.size();

            // When reaching target distance k, break and collect queue contents
            if (currentDistance == k) break;

            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();

                // Explore Left Child
                if (current->left && !visited[current->left]) {
                    q.push(current->left);
                    visited[current->left] = true;
                }

                // Explore Right Child
                if (current->right && !visited[current->right]) {
                    q.push(current->right);
                    visited[current->right] = true;
                }

                // Explore Parent
                if (parentMap[current] && !visited[parentMap[current]]) {
                    q.push(parentMap[current]);
                    visited[parentMap[current]] = true;
                }
            }
            currentDistance++;
        }

        // Step 4: Extract all node values at distance k
        vector<int> result;
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            result.push_back(current->data);
        }

        return result;
    }
};

int main() {
    /*
        Constructing the following Binary Tree:
                    3
                 /     \
                5       1
               / \     / \
              6   2   0   8
                 / \
                7   4
    */
    Node* root = new Node(3);
    root->left = new Node(5);
    root->right = new Node(1);
    root->left->left = new Node(6);
    root->left->right = new Node(2);
    root->right->left = new Node(0);
    root->right->right = new Node(8);
    root->left->right->left = new Node(7);
    root->left->right->right = new Node(4);

    Solution sol;
    int k, target;

    // Read distance k and target node value
    // Example Input: 2 5
    // Expected Output: 7 4 1
    cin >> k >> target;

    vector<int> nodesAtDistK = sol.distanceK(root, k, target);

    cout << "Nodes at distance " << k << " from target node " << target << ": ";
    for (int val : nodesAtDistK) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}