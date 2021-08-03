// 先序遍历，递归版本
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        TreeNode* current = root;
        vector<int> ans;
        if(current == nullptr){
            return {};
        }
        ans.push_back(current->val);
        vector<int> ans_left = preorderTraversal(current->left);
        vector<int> ans_right = preorderTraversal(current->right);
        
        ans.insert(ans.end(),ans_left.begin(),ans_left.end());
        ans.insert(ans.end(),ans_right.begin(),ans_right.end());
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

//先序遍历，根左右，迭代版本
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int> ans;
        stack<TreeNode*> s;
        
        while(root || !s.empty()){
            while(root){
                s.push(root);
                ans.push_back(root->val);
                root = root->left;
            }
            root = s.top();
            s.pop();
            root = root->right;
        }
        return ans;
    }
};