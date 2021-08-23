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

/*
 与235题不同，此题是binary tree，想要找到从跟节点到任意节点的路径，需要使用stack，并且增加visited变量，
 这里考察的知识点是树与图的遍历中的深度优先遍历
*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> sP;
        stack<TreeNode*> sQ;
        dfs(root, p, sP);
        dfs(root, q, sQ);
        
        unordered_map<TreeNode*, int> m;
        while(!sP.empty()){
            m[sP.top()] = sP.top()->val;
            sP.pop();
        }
        
        while(!sQ.empty()){
            if(m.find(sQ.top()) != m.end()){
                // 说明找到了匹配的结果
                return sQ.top();
            }
            sQ.pop();
        }
        return nullptr;
        
    }
    bool dfs(TreeNode* root, TreeNode* p, stack<TreeNode*>& res){
        if(!root) return false;
        res.push(root);
        if(root->val == p->val) return true;
        bool visited = false;
        if(root->left) visited = dfs(root->left, p, res);
        if(!visited && root->right) visited = dfs(root->right, p, res);
        if(!visited) res.pop();
        return visited;
    }
};