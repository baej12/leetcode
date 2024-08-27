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

vector<int> solution;

void recurse(TreeNode * root) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        recurse(root->left);
    }

    solution.push_back(root->val);

    if (root->right != NULL) {
        recurse(root->right);
    }
}

vector<int> inorderTraversal(TreeNode* root) {
    recurse(root);
    return solution;
}

int main() {
    return 0;
}