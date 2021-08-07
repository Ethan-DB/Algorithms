//迭代方法
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
    void flatten(TreeNode* root) {
        while(root){
            //如果root同时存在左孩子和右孩子，那么找到左孩子的最右孩子，然后将根节点的右孩子接到左孩子的最右孩子上
            if(root->left && root->right){
                TreeNode* t = root->left;
                while(t->right){
                    t = t->right;
                }
                t->right = root->right;
            }
            
            //此时，root的右孩子已经不存在，如果root的左孩子存在，那么接到root的右孩子上
            if(root->left){
                root->right = root->left;
            }
			
			//将root的左孩子设置为nullptr
            root->left = nullptr;
			
			//迭代root->right孩子，因为此时左孩子已经为nullptr
            root = root->right;
        }
    }
};


// 递归方法
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
    TreeNode* prev;
    void flatten(TreeNode* root) {
        if(root == nullptr) return;
        flatten(root->right);
        flatten(root->left);
        
        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
};