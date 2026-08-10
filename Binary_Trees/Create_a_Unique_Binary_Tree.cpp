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
     * Recursive helper function to construct a binary tree from preorder and inorder traversals.
     * 
     * Core Algorithm:
     * 1. The first element in the current preorder range `pr[prS]` is the root node.
     * 2. Find the root's index (`inRoot`) in the inorder traversal array using `inMap`.
     * 3. Nodes before `inRoot` in the inorder array form the left subtree; nodes after form the right subtree.
     * 4. Calculate `numsLeft` (number of nodes in the left subtree) to split the preorder range correctly.
     * 
     * @param pr     Preorder traversal array
     * @param prS    Start index for current subtree in preorder
     * @param prE    End index for current subtree in preorder
     * @param in     Inorder traversal array
     * @param inS    Start index for current subtree in inorder
     * @param inE    End index for current subtree in inorder
     * @param inMap  Hash map mapping each node value to its index in the inorder array
     * @return       Pointer to the root of the constructed subtree
     */
    TreeNode* BuildTree(vector<int> &pr, int prS, int prE, vector<int> &in, int inS, int inE, map<int, int> inMap) {
        // Base Case: If bounds overlap incorrectly, subtree is empty
        if (prS > prE || inS > inE) return nullptr;

        // Step 1: Create root node from current preorder start index
        TreeNode* root = new TreeNode(pr[prS]);

        // Step 2: Locate root node in the inorder traversal
        int inRoot = inMap[root->val];

        // Step 3: Count total elements in left subtree
        int numsLeft = inRoot - inS;

        // Step 4: Recursively build Left Subtree
        // - Preorder range: [prS + 1  TO  prS + numsLeft]
        // - Inorder range:  [inS      TO  inRoot - 1]
        root->left = BuildTree(pr, prS + 1, prS + numsLeft, in, inS, inRoot - 1, inMap);

        // Step 5: Recursively build Right Subtree
        // - Preorder range: [prS + numsLeft + 1  TO  prE]
        // - Inorder range:  [inRoot + 1         TO  inE]
        root->right = BuildTree(pr, prS + numsLeft + 1, prE, in, inRoot + 1, inE, inMap);

        return root;
    }

    /**
     * Entry point to build a Binary Tree given its Preorder and Inorder traversals.
     * 
     * Time Complexity:  O(N log N) with std::map lookup (can be O(N) with std::unordered_map)
     * Space Complexity: O(N) for map storage and recursion call stack
     * 
     * @param pr Vector containing preorder traversal values
     * @param in Vector containing inorder traversal values
     * @return   Pointer to the root of the constructed binary tree
     */
    TreeNode* CreateBT(vector<int> &pr, vector<int> &in) {
        map<int, int> inMap;
        int n = in.size();
        int m = pr.size();

        // Map each value in inorder array to its corresponding index for O(1)/O(log N) lookup
        for (int i = 0; i < n; i++) {
            inMap[in[i]] = i;
        }

        // Initiate recursive tree construction
        TreeNode* root = BuildTree(pr, 0, m - 1, in, 0, n - 1, inMap);
        return root;
    }
};

int main() {
    /*
        Input Format:
        Line 1: Size of preorder array (x)
        Line 2: Elements of preorder array
        Line 3: Size of inorder array (y)
        Line 4: Elements of inorder array
    */
    int x, y;

    // Read preorder array input
    cin >> x;
    vector<int> preord(x);
    for (int i = 0; i < x; i++) cin >> preord[i];

    // Read inorder array input
    cin >> y;
    vector<int> inord(y);
    for (int i = 0; i < y; i++) cin >> inord[i];

    Solution ans;
    TreeNode* root = ans.CreateBT(preord, inord);

    return 0;
}