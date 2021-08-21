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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr){
            root = new TreeNode(val);
            return root;
        }
        
        if(val > root->val){
            root->right = insertIntoBST(root->right,val);
        }else{
            root->left = insertIntoBST(root->left,val);
        }
        return root;
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
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        insertNode(root, val);
        return root;
    }
    void insertNode(TreeNode*& root, int val){
        if(!root){
            root = new TreeNode(val);
            return;
        }
        if(val < root->val) insertNode(root->left, val);
        else insertNode(root->right, val);
    }
};