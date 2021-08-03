// 中序遍历，递归版本
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
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode* current = root;
        vector<int> ans;
        vector<int> ans_left;
        if(current == nullptr){
            return {};
        }
        if(current->left != nullptr){
            ans_left = inorderTraversal(current->left);
        }
        
        ans.push_back(current->val);
        ans_left.insert(ans_left.end(), ans.begin(),ans.end());
        vector<int> ans_right;
        if(current->right != nullptr){
             ans_right = inorderTraversal(current->right);
        }
        ans_left.insert(ans_left.end(), ans_right.begin(), ans_right.end());
        return ans_left;
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
// 中序遍历，迭代版本，左根右
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr) return vector<int>{};
        vector<int> res;
        stack<TreeNode*> s;
        while(root != nullptr || !s.empty()){
            while(root != nullptr){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};