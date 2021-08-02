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
//扫描一遍，产生两个链表，一个是小于X的链表，一个是大于等于X的链表，并记住小于X链表的尾指针
//最终生成新的链表
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head == nullptr) return nullptr;
        
        ListNode* lt = new ListNode(-1);
        ListNode* ltLast = lt;
        ListNode* gt = new ListNode(-1);
        ListNode* gtLast = gt;
        
        //遍历链表，拆分节点
        ListNode* current = head;
        while(current){
            if(current->val < x){
                ltLast->next = new ListNode(current->val);
                ltLast = ltLast->next;
            }else{
                gtLast->next = new ListNode(current->val);
                gtLast = gtLast->next;
            }
            current = current->next;
        }
        
        ltLast->next = gt->next;
        return lt->next;
    }
};