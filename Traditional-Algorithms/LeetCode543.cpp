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
    int diameterOfBinaryTree(TreeNode* root) {
        int d = 0;
        dfs(root, d);
        return d;
    }
    int dfs(TreeNode* root, int& d){
        if(root == nullptr) return 0;
        int l = dfs(root->left, d);
        int r = dfs(root->right, d);
        d = max(d, l+r);
        return max(l, r) + 1;
    }
    
};