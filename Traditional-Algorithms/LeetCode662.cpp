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
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr) return 0;
        int max = 0;
        queue<pair<TreeNode*, unsigned long long int>> q;   // 如果使用int会发生runtime error
        q.push(pair<TreeNode*, unsigned long long int>(root, 1));
        while(!q.empty()){
            unsigned long long int l = q.front().second, r = l;
            for(unsigned long long int i = q.size(); i > 0; i--){
                TreeNode* current = q.front().first;
                r = q.front().second;
                q.pop();
                if(current->left) q.push(pair<TreeNode*, int>(current->left, r * 2));
                if(current->right) q.push(pair<TreeNode*, int>(current->right, r * 2 + 1));
            }
            if(r - l + 1 > max) max = r-l+1;
        }
        return max;
    }
};