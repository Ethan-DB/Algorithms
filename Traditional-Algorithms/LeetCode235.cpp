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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q){
            return root;
        }
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        if(l && r){
            return root;
        }else
            return l ? l:r;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// DFS找出每个点的遍历结果，放入到vector中，然后将其中一个点的遍历结果放入到hash表中，
// 从右向左搜索另外一个结果，比较在hash表中是否存在相同的值，返回即可
// 时间复杂度O(h)，空间复杂度O(N)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> resP;
        vector<TreeNode*> resQ;
        dfs(root, p, resP);
        dfs(root, q, resQ);
        
        unordered_map<int, TreeNode*>m;
        for(auto u : resP){
            m[u->val] = u;
        }
        
        int len = resQ.size();
        for(int i = len - 1; i >= 0; i--){
            if(m.find(resQ[i]->val) != m.end()) return resQ[i];
        }
        return nullptr;
    }
    void dfs(TreeNode* root, TreeNode* p, vector<TreeNode*>& res){
        if(root->val == p->val) {
            res.push_back(root);
            return;
        }
        res.push_back(root);
        if(p->val < root->val){
            dfs(root->left, p, res);
        }else{
            dfs(root->right, p, res);
        }
        return;
    }
};