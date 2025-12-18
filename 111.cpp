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

// Data structure definition(s)
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
class Solution {
public:
    int minDepth(TreeNode* root) {
        
    }
};

int main() {
    Solution sol;
    
    // Read input - tree format: [3,9,20,null,null,15,7]
    string line;
    getline(cin, line);
    
    // Parse array with null support
    vector<string> values;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string val;
            while (getline(ss, val, ',')) {
                // Trim whitespace
                size_t s = val.find_first_not_of(" \t");
                size_t e = val.find_last_not_of(" \t");
                if (s != string::npos && e != string::npos) {
                    values.push_back(val.substr(s, e - s + 1));
                }
            }
        }
    }
    
    // Build tree (level-order)
    TreeNode* root = nullptr;
    if (!values.empty() && values[0] != "null") {
        root = new TreeNode(stoi(values[0]));
        queue<TreeNode*> q;
        q.push(root);
        
        size_t i = 1;
        while (!q.empty() && i < values.size()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Left child
            if (i < values.size() && values[i] != "null") {
                node->left = new TreeNode(stoi(values[i]));
                q.push(node->left);
            }
            i++;
            
            // Right child
            if (i < values.size() && values[i] != "null") {
                node->right = new TreeNode(stoi(values[i]));
                q.push(node->right);
            }
            i++;
        }
    }
    
    // Call solution
    // TODO: Modify based on function signature
    // int result = sol.functionName(root);
    // cout << result << endl;
    
    return 0;
}
