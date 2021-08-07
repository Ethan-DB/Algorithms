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

// 递归，返回值用字符串拼接起来
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        return dfs(root1) == dfs(root2);
    }
    
    string dfs(TreeNode* root){
        if(root == nullptr) return "";
        if(root != nullptr && root->left == nullptr && root->right == nullptr) 
            return to_string(root->val)+",";
        string ansLeft = dfs(root->left);
        string ansRight = dfs(root->right);
        return ansLeft + ansRight;
    }
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

// 递归，返回值以参数的形式传递，vector<int>& ans一定要引用传值，否则wrong answer
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int>ans1 = {};
        vector<int>ans2 = {};
        dfs(root1, ans1);
        dfs(root2, ans2);
        return ans1 == ans2;
    }
    
    void dfs(TreeNode* root, vector<int>& ans){
        if(root == nullptr) return;
        if(root != nullptr && root->left == nullptr && root->right == nullptr) ans.push_back(root->val);
        dfs(root->left, ans);
        dfs(root->right, ans);
    }
};