#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>

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
     * Finds the left height (depth following only left children) of a subtree.
     */
    int getLeftHeight(TreeNode* node) {
        int height = 0;
        while (node != nullptr) {
            height++;
            node = node->left;
        }
        return height;
    }

    /**
     * Finds the right height (depth following only right children) of a subtree.
     */
    int getRightHeight(TreeNode* node) {
        int height = 0;
        while (node != nullptr) {
            height++;
            node = node->right;
        }
        return height;
    }

    /**
     * Counts the total number of nodes in a Complete Binary Tree.
     * 
     * Strategy (Optimized O(log^2 N) Complete Binary Tree Property):
     * 1. Calculate left height (`lh`) and right height (`rh`) of the current subtree.
     * 2. If `lh == rh`, the subtree is a Perfect Binary Tree. The total node count 
     *    is directly given by the formula: 2^lh - 1  (or (1 << lh) - 1).
     * 3. If `lh != rh`, recursively calculate node count as:
     *    1 (root) + countNodes(root->left) + countNodes(root->right).
     * 
     * Time Complexity:  O(log^2 N) - tree height is log(N), and we calculate heights log(N) times
     * Space Complexity: O(log N)   - recursion stack depth equal to tree height
     * 
     * @param root Pointer to the root of the complete binary tree
     * @return int Total number of nodes in the tree
     */
    int numberofnodes(TreeNode* root) {
        if (root == nullptr) return 0;

        int lh = getLeftHeight(root);
        int rh = getRightHeight(root);

        // If left and right heights are equal, it's a Perfect Binary Tree
        if (lh == rh) {
            return (1 << lh) - 1; // 2^lh - 1
        }

        // Otherwise, recursively count root + left subtree + right subtree
        return 1 + numberofnodes(root->left) + numberofnodes(root->right);
    }
};

int main() {
    /*
        Constructing the following Complete Binary Tree:
                        1
                     /     \
                    2       3
                  /   \    / \
                 4     5  6   7
                / \   / \
               8   9 10 11
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(11);

    Solution sol;
    int totalNodes = sol.numberofnodes(root);

    // Output total count (Expected Output: 11)
    cout << "Total number of nodes in Complete Binary Tree: " << totalNodes << endl;

    return 0;
}