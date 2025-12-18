/*
 * LeetCode Problem #111
 * Title: Minimum Depth of Binary Tree
 * Difficulty: Easy
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/
 *
 * Description:
 * 
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 * Note: A leaf is a node with no children.
 *  
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 2
 * Example 2:
 * Input: root = [2,null,3,null,4,null,5,null,6]
 * Output: 5
 *  
 * Constraints:
 * 	The number of nodes in the tree is in the range [0, 105].
 * 	-1000 <= Node.val <= 1000
 *
 * Example Test Cases:
 * [3,9,20,null,null,15,7]
 * [2,null,3,null,4,null,5,null,6]
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int explore(TreeNode* node) {
        if (node == NULL) {
            return 0;
        }

        if (node->left == NULL && node->right == NULL) {
            return 1;
        }

        if (node->left != NULL && node->right == NULL) {
            return 1 + explore(node->left);
        }

        if (node->right != NULL && node->left == NULL) {
            return 1 + explore(node->right);
        }

        return 1 + min(explore(node->left), explore(node->right));
    }

    int minDepth(TreeNode* root) {
        return explore(root);
    }
};

int main() {
    Solution sol;
    
    // Read input
    string line;
    getline(cin, line);
    
    // Parse input (modify based on problem requirements)
    vector<int> nums;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        stringstream ss(content);
        string num;
        while (getline(ss, num, ',')) {
            nums.push_back(stoi(num));
        }
    }
    
    // Call solution and output result
    // TODO: Modify based on function signature
    // cout << sol.functionName(args) << endl;
    
    return 0;
}
