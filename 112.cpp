#include <./stdc++11.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool hasPathSum(TreeNode* root, int targetSum) {
    bool left = false, right = false;

    if (root == NULL)  {
        return false;
    } 

    if (root->left == NULL && root->right == NULL) {
        return targetSum - root->val == 0;
    }

    if (root->left != NULL) {
        left = hasPathSum(root->left, targetSum - root->val);
    }

    if (root->right != NULL) {
        right = hasPathSum(root->right, targetSum - root->val);
    }

    return left || right;
}

int main () {


    return 0;
}