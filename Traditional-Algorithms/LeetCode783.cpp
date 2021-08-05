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
    int minDiffInBST(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*> s;
        int diff = INT_MAX;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            ans.push_back(root->val);
            s.pop();
            root = root->right;
        }
        for(int i = 0; i < ans.size() - 1; i++){
            if(ans[i+1] - ans[i] < diff) diff = ans[i+1] - ans[i];
        }
        return diff;
    }
};