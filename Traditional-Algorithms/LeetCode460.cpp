/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    stack<Node*> s;
    Node* L, *R;
    Solution(){
        L = new Node(-1);
        R = new Node(-1);
        L->next = R;
        R->prev = L;
    }
    void insertElement(int val){
        //在双向链表的尾部插入一个节点
        Node* tmp = new Node(val);
        R->prev->next = tmp;
        tmp->prev = R->prev;
        tmp->next = R;
        R->prev = tmp;
    }
    Node* flatten(Node* head) {
        if(head == nullptr) return nullptr;
        Node* current = head;
        while(current){
            insertElement(current->val);
            if(current->child == nullptr){
                if(current->next != nullptr){
                    current = current->next;
                }else{
                    //也就说没有next了
                    if(!s.empty()){
                        current = s.top();
                        s.pop();
                    }else{
                        //否则说明栈中也没有任何元素，此时返回结果
                        R->prev->next= nullptr;
                        delete R;
                        L->next->prev = nullptr;  //如果不加这个条件，结果错误，因为L->next指向虚拟头结点L，由于返回的结果是L->next表示这个结果双链表，所以要将该指针置空
                        return L->next;
                    }
                }
            }else{
                //当前节点存在孩子节点
                if(current->next) s.push(current->next);
                current = current->child;
            }
        }
        return nullptr;
    }
};