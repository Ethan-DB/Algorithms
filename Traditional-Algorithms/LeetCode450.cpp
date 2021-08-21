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
 // BST删除操作，分为三种情况：
 // (1)如果删除的节点为根节点（这里有一个技巧，变量使用引用，能避免去找它的父亲节点），直接将其赋值为nullptr即可删除
 // (2)如果删除的节点不存在左子树，那么应该将右子树提上来即可（root=root->right）,如果当前删除的节点不存在右子树，将其左子树提上来即可（root = root->left）
 // (3)如果要删除的节点存在左右子树，应该找到当前节点的后续节点（它的后续节点一定是其右孩子的最左节点），然后用后继节点的val代替根节点的val，相当于删除了root的val，然后再递归删除后继节点的val
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        del(root, key);
        return root;
    }
    void del(TreeNode*& root, int key){
        if(!root) return;
        if(root->val == key){
            if(!root->left && !root->right){
                //说明当前节点为叶子节点，直接删除即可
                root = nullptr;
                return;
            }else if(!root->left){
                //否则，左子树不存在，右子树存在
                root = root->right;
                return;
            }else if(!root->right){
                // 说明当前右子树不存在，左子树存在
                root = root->left;
                return;
            }else{
                // 左右子树都存在，找到其后续
                TreeNode* next = root->right;
                while(next->left) next = next->left;
                root->val = next->val;
                del(root->right, next->val);
            }
        }
        else if(key < root->val) del(root->left, key);
        else del(root->right, key);
        return;
    }
};