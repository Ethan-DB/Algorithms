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

// 中序遍历(左根右) + unordered_map
// 空间复杂度O(n), 时间复杂度O(n)
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        vector<int>inorderRes;
        stack<TreeNode*> s;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            inorderRes.push_back(root->val);
            root = root->right;
        }
        // 在利用一个unordered_map存储次数，输出最大值
        unordered_map<int, int> m;
        for(auto u: inorderRes){
            if(m.find(u) != m.end()){
                m[u]++;
            }else{
                m[u] = 1;
            }
        }
        int max = -1;
        for(auto & u : m){
            if(u.second > max) max = u.second;
        }
        vector<int>res;
        for(auto & u: m){
            if(u.second == max) res.push_back(u.first);
        }
        return res;
        
    }
    
};