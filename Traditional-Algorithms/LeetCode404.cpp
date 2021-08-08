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
    int sumOfLeftLeaves(TreeNode* root) {
        return dfs(root, false);
    }
    int dfs(TreeNode* root, bool isLeft){ //isLeft用来表明是左孩子还是右孩子
        if(root == nullptr) return 0;
        if(root != nullptr && root->left == nullptr && root->right == nullptr){
            if(isLeft) return root->val;  // 如果是左孩子，返回其值
            else return 0;  //如果不是左孩子，返回值置零
        } 
        int ansLeft = dfs(root->left, true);
        int ansRight = dfs(root->right, false);
        return ansLeft+ansRight;
    }
};