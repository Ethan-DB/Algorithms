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
    int kthSmallest(TreeNode* root, int k) {
        if(root == nullptr){
            return 0;
        }
        int mid = countNode(root->left);
        if(k == mid+1){
            return root->val;
        }else if(k <= mid){
            return kthSmallest(root->left, k);
        }else{
            return kthSmallest(root->right, k-1-mid);
        }
    }
    
    int countNode(TreeNode* root){
        if(root == nullptr){
            return 0;
        }
        if(root->left == nullptr && root->right == nullptr){
            return 1;
        }
        
        int leftCount = countNode(root->left);
        int rightCount = countNode(root->right);
        return 1+leftCount+rightCount;
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
//迭代中序遍历，就会得到一个排序号的数组，根据下标访问即可
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int>ans;
        stack<TreeNode*> s;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        
        return ans[k-1];
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
// 递归中序遍历
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> ans = BSTSort(root);
        return ans[k-1];
    }
    
    vector<int> BSTSort(TreeNode* root){
        TreeNode* current = root;
        vector<int> ans;
        vector<int> ans_left;
        vector<int> ans_right;
        
        if(current == nullptr){
            return {};
        }
        
        ans_left = BSTSort(current->left);
        ans.push_back(current->val);
        ans_right = BSTSort(current->right);
        
        ans_left.insert(ans_left.end(), ans.begin(), ans.end());
        ans_left.insert(ans_left.end(), ans_right.begin(), ans_right.end());
        return ans_left;
    }
};