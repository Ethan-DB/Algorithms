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
    bool isValidBST(TreeNode* root) {
    return dfs_valid(root, LONG_MIN, LONG_MAX);
}
    bool dfs_valid(TreeNode *root, long low, long high) {
        if (!root) return true;
        return low < root->val && root->val < high && dfs_valid(root->left, low, root->val)
            && dfs_valid(root->right, root->val, high);
    }
};



// 利用中序遍历得到的数组应该满足从小到大排序的特征
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
// 保存中序遍历数组，看是否有序即可
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*> s;
        while(root != nullptr || !s.empty()){
            while(root != nullptr){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        int len = ans.size();
        for(int i = 1; i < len; i++){
            if(ans[i] <= ans[i-1]) return false;
        }
        return true;
    }
};