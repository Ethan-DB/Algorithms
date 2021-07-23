/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1), *cur = dummy;
        while(l1 && l2){
            if(l1->val < l2->val)  cur->next = new ListNode(l1->val), l1 = l1->next;
            else cur->next = new ListNode(l2->val), l2 = l2->next;
            cur = cur->next;
        }
        while(l1){
            cur->next = new ListNode(l1->val);
            cur = cur->next, l1 = l1->next;
        }
        while(l2){
            cur->next = new ListNode(l2->val);
            cur = cur->next, l2 = l2->next;
        }
        return dummy->next;
    }
};


// 优化版本
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1), *cur = dummy;
        while(l1 && l2){
            if(l1->val < l2->val)  cur->next = l1, l1 = l1->next;
            else cur->next = l2, l2 = l2->next;
            cur = cur->next;
        }
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return dummy->next;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct cmp{
    bool operator()(ListNode* a, ListNode* b){
        return (a->val) > (b->val);
    }
};

// 使用优先队列(小顶堆实现)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> q;
        if(l1 != nullptr) q.push(l1);
        if(l2 != nullptr) q.push(l2);
        
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;
        
        while(!q.empty()){
            ListNode* tmp = q.top();
            q.pop();
            current->next = tmp;
            if(tmp->next != nullptr){
                q.push(tmp->next);
            }
            current = current->next;
        }
        return dummy->next;
    }
};