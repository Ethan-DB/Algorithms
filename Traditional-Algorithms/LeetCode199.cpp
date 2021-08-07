// 层次遍历，也可称为BFS
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
// 输出每一层的最后一个元素
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) return {};
        queue<TreeNode*>q;
        vector<int>ans;
        q.push(root);
        
        while(!q.empty()){
            vector<int>oneLevel;
            for(int i = q.size(); i > 0; i--){
                TreeNode* tmp = q.front(); 
                oneLevel.push_back(tmp->val);
                q.pop();
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
            }
            ans.push_back(oneLevel[oneLevel.size()-1]);
        }
        return ans;
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
// 输出每一层的最后一个元素
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) return {};
        queue<TreeNode*>q;
        vector<int>ans;
        q.push(root);
        
        while(!q.empty()){
            for(int i = q.size(); i > 0; i--){
                TreeNode* tmp = q.front(); 
                q.pop();
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
                if(i == 1) ans.push_back(tmp->val);
            }
        }
        return ans;
    }
};