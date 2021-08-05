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
// 遍历二叉树，排序遍历结果，时间复杂度为O(nlogn)，空间复杂度为O(n)
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*> s;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        sort(ans.begin(), ans.end());
        
        for(int i = 1; i < ans.size(); ++i){
            if(ans[i] != ans[0]) return ans[i];
        }
        return -1;
    }
};