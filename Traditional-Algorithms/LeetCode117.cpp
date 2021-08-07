// 层次遍历
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root == nullptr) return nullptr;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            vector<Node*> oneLevel;  // 使用了额外的空间
            for(int i = q.size(); i > 0; i--){
                Node* tmp = q.front();
                q.pop();
                oneLevel.push_back(tmp);
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
            }
            //在oneLevel数组的向量中加边
            for(int i = 0; i < oneLevel.size() - 1; i++){
                oneLevel[i]->next = oneLevel[i+1];
            }
            oneLevel[oneLevel.size()-1]->next = nullptr;
        }
        return root;
    }
};


//层次遍历，少用了oneLevel空间
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root == nullptr) return nullptr;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* current = new Node(0);
            for(int i = q.size(); i > 0;){
                current->next = q.front();
                current = current->next;
                q.pop();
                if(current->left) q.push(current->left);
                if(current->right) q.push(current->right);
                i = i - 1;
                if(i > 0){
                    Node* tmp = q.front();
                    q.pop();
                    current->next = tmp;
                    if(tmp->left) q.push(tmp->left);
                    if(tmp->right) q.push(tmp->right);
                    current = current->next;
                    i = i - 1;
                }else{
                    current->next = nullptr;
                }
            }
        }
        return root;
    }
};