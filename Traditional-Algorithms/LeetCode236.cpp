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
 235和236题目通用化方法
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
// 235和236题目通用化方法
class Solution {
    unordered_map<TreeNode*, TreeNode*>m;
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bfs(root);
        m[root] = nullptr;   // 首先设置根节点的父亲为nullptr
        // 查询到p的路径（从p到根节点）
        vector<TreeNode*> resPath;
        while(m.find(p) != m.end()){
            resPath.push_back(p);
            p = m[p];
        }
        // Q的路径应该放到一个unordered_map中
        unordered_map<TreeNode*, bool> mq;
        while(m.find(q) != m.end()){
            mq[q] = true;
            q = m[q];
        }
        // 然后遍历resPath，看有没有包含q的路径
        for(auto& u: resPath){
            // 对于从p到根节点的路径，拿出每一个，都要判断Q的路径中是否包含这个节点（如何在O(1)时间内快速判断呢？）
            if(mq.find(u) != mq.end()){
                return u;
            }
        }
        return nullptr;
    }
    
    void bfs(TreeNode* root){
        if(!root) return;
        if(root->left) m[root->left] = root;
        if(root->right) m[root->right] = root;
        bfs(root->left);
        bfs(root->right);
        return;
    }
    
};