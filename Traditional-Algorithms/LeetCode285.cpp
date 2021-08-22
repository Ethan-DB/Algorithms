/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 中序遍历
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*>s;
        vector<TreeNode*>res;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            res.push_back(root);
            s.pop();
            root = root->right;
        }
        int len = res.size();
        for(int i = 0; i < len; i++){
            if(res[i]->val == p->val && i != len - 1) return res[i+1];
        }
        return nullptr;
    }
};