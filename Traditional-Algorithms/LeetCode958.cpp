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
    bool isCompleteTree(TreeNode* root) {
        queue<pair<TreeNode*, int>>q;
        q.push(pair<TreeNode*, int>(root, 1));
        int level = 0;
        while(!q.empty()){
            vector<int>ans;
            int r;
            for(int i = 0, n = q.size(); i < n; i++){
                TreeNode* current = q.front().first;
                r = q.front().second;
                ans.push_back(r);
                q.pop();
                if(current->left) q.push(pair<TreeNode*, int>(current->left, r * 2));
                if(current->right) q.push(pair<TreeNode*, int>(current->right, r * 2 + 1));
            }
            int count = (1 << level);
            int len = ans.size();
            if(count == len){
                //代表该层节点是满的
                level++;
                continue;
            }else{
                //代表该层节点不满
                if(!q.empty()) return false;   //q非空表示该层节点不是叶子节点，，complete 规定非叶子节点一定要满，因此直接返回false
                else{
                    //该层为叶子节点
                    if(ans[0] % 2 != 0) return false;   //不满足最左原则
                    else if(ans[0] != 1 << level){ // ans[0]既是偶数，也必须以1 << level开头，如果不满足，则一定不符合最左原则
                        return false;
                    }else{
                        //则需要判断ans数组中每个节点的数目应该是加1的规则
                        for(int i = 1; i < len; i++){
                            if(ans[i] != ans[i - 1] + 1) return false;
                            else continue;
                        }
                        return true;
                    }
                }
                level++;
            }
        }
        return true;
    }
};