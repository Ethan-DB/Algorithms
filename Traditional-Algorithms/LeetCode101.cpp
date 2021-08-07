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

// 层次遍历，reverse之后的结果和原先的数组相等
// 如果有一个孩子为空，另一个不为空，则将空孩子对应的val推入0
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root){   //代码中不能发现的边界情况
            if(root->left == nullptr && root->right != nullptr) return false;
            if(root->left != nullptr && root->right == nullptr) return false;
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            vector<int>ans;
            for(int i = q.size(); i > 0; i--){
                TreeNode* tmp = q.front();
                q.pop();
                if(tmp == nullptr) ans.push_back(0);   // 这一步和其他的层次遍历不同，
                else ans.push_back(tmp->val);
               
                if(tmp != nullptr) {
                    q.push(tmp->left);   // 可能将空值写入
                    q.push(tmp->right);
                }
                   
            }
            auto t = ans;
            reverse(ans.begin(), ans.end());
            if(t != ans) return false;
        }
        return true;
    }
};