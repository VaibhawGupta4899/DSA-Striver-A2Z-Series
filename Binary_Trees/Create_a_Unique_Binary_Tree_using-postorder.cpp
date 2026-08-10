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
     * Recursive helper function to construct a binary tree using index ranges.
     * 
     * Key Logic:
     * 1. The first element of current preorder range (pr[prS]) is always the subtree root.
     * 2. Find the root's position in the inorder traversal (inRoot) using inMap.
     * 3. Nodes to the left of inRoot belong to the left subtree; nodes to the right belong to the right subtree.
     * 4. Calculate left subtree size (numsLeft) to split the preorder vector correctly.
     * 
     * @param pr      Preorder traversal vector
     * @param prS     Start index of current subtree in preorder
     * @param prE     End index of current subtree in preorder
     * @param in      Inorder traversal vector
     * @param inS     Start index of current subtree in inorder
     * @param inE     End index of current subtree in inorder
     * @param inMap   Map storing (node value -> inorder index) for O(1) lookup
     * @return        Pointer to the constructed subtree root
     */
    TreeNode* BuildTree(vector<int> &pr, int prS, int prE, vector<int> &in, int inS, int inE, map<int, int> inMap) {
        // Base case: Invalid range indicates empty subtree
        if (prS > prE || inS > inE) return nullptr;

        // Step 1: Create root node from the first element of preorder
        TreeNode* root = new TreeNode(pr[prS]);

        // Step 2: Locate root index in inorder array
        int inRoot = inMap[root->val];

        // Step 3: Count nodes in the left subtree
        int numsLeft = inRoot - inS;

        // Step 4: Recursively build left and right subtrees
        // Left Subtree: 
        //   Preorder range -> [prS + 1, prS + numsLeft]
        //   Inorder range  -> [inS, inRoot - 1]
        root->left = BuildTree(pr, prS + 1, prS + numsLeft, in, inS, inRoot - 1, inMap);

        // Right Subtree:
        //   Preorder range -> [prS + numsLeft + 1, prE]
        //   Inorder range  -> [inRoot + 1, inE]
        root->right = BuildTree(pr, prS + numsLeft + 1, prE, in, inRoot + 1, inE, inMap);

        return root;
    }

    /**
     * Constructs a Binary Tree given its Preorder and Inorder traversals.
     * 
     * Time Complexity:  O(N log N) with std::map (or O(N) if pass-by-reference with std::unordered_map)
     * Space Complexity: O(N) for hash map storage and recursion call stack
     * 
     * @param pr Vector containing preorder traversal values
     * @param in Vector containing inorder traversal values
     * @return   Pointer to the root of the constructed binary tree
     */
    TreeNode* CreateBT(vector<int> &pr, vector<int> &in) {
        map<int, int> inMap;
        int n = in.size();
        int m = pr.size();

        // Hash map mapping each value in inorder traversal to its index
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
        Input format:
        Line 1: Size of preorder array (x)
        Line 2: Elements of preorder array
        Line 3: Size of inorder array (y)
        Line 4: Elements of inorder array
    */
    int x, y;

    cin >> x;
    vector<int> preord(x);
    for (int i = 0; i < x; i++) cin >> preord[i];

    cin >> y;
    vector<int> inord(y);
    for (int i = 0; i < y; i++) cin >> inord[i];

    Solution ans;
    TreeNode* root = ans.CreateBT(preord, inord);

    return 0;
}