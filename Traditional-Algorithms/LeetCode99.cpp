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
// 中序遍历，保存成pair，根据指针修改对应的值
// 时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    void recoverTree(TreeNode* root) {
        stack<pair<TreeNode*, int>>s;
        vector<pair<TreeNode*, int>>res;
        while(root || !s.empty()){
            while(root){
                s.push(pair<TreeNode*, int>(root, root->val));
                root = root->left;
            }
            auto tmp = s.top();
            root = tmp.first;
            res.push_back(tmp);
            s.pop();
            root = root->right;
        }
        int len = res.size();
        vector<int>v;
        for(auto u: res){
            v.push_back(u.second);
        }
        sort(v.begin(), v.end());
        for(int i = 0; i < len; i++){
            res[i].first->val = v[i];
        }
        return;
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
// 中序遍历，相比上一个方法，这里实际上只需要从左往右找到中序遍历结果的第一个违反中序遍历结果的节点，记为left
// 然后遍历中序遍历的结果，从右往左遍历，将第一个小于left->val的节点拿出来，记为right，此时只需要交换这两个值就是最少的
// 交换次数
class Solution {
public:
    void recoverTree(TreeNode* root) {
        stack<pair<TreeNode*, int>>s;
        vector<pair<TreeNode*, int>>res;
        while(root || !s.empty()){
            while(root){
                s.push(pair<TreeNode*, int>(root, root->val));
                root = root->left;
            }
            auto tmp = s.top();
            root = tmp.first;
            res.push_back(tmp);
            s.pop();
            root = root->right;
        }
        
        // 分别找到left和right
        int len = res.size();
        TreeNode* left;
        TreeNode* right;
        for(int i = 0; i < len; i++){
            if(res[i].second > res[i+1].second) {
                left = res[i].first;
                break;
            }
        }
        for(int i = len - 1; i >= 0; i--){
            if(res[i].second < left->val){
                right = res[i].first;
                break;
            } 
        }
        
        // 只用一次交换left和right的值
        int tmp = left->val;
        left->val = right->val;
        right->val = tmp;
        return;
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
// 中序遍历，相比上一个方法，这里实际上只需要从左往右找到中序遍历结果的第一个违反中序遍历结果的节点，记为left
// 然后遍历中序遍历的结果，从右往左遍历，将第一个小于left->val的节点拿出来，记为right，此时只需要交换这两个值就是最少的
// 交换次数
// 如果不考虑栈空间，该算法就为O(1)空间复杂度，时间复杂度为O(n)
class Solution {
    TreeNode* left, *right, *prev;
public:
    void recoverTree(TreeNode* root) {
        stack<pair<TreeNode*, int>>s;
        while(root || !s.empty()){
            while(root){
                s.push(pair<TreeNode*, int>(root, root->val));
                root = root->left;
            }
            auto tmp = s.top();
            root = tmp.first;
            if(!left && prev && prev->val >= root->val) left = prev;  // 左边找的是违反中序遍历的那个大的值
            if(left && prev->val >= root->val) right = root; // 右边找到的违反中序遍历的那个小的值，所以right = root->val
            prev = root;
            s.pop();
            root = root->right;
        }
        // 交换
        int tmp = left->val;
        left->val = right->val;
        right->val = tmp;
        return;
    }
};