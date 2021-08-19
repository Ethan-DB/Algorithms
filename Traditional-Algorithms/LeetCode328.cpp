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
 // 时间复杂度为O(n)，空间复杂度为O(1)
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head) return nullptr;
        ListNode* dummy = new ListNode(-1), *current = dummy;
        ListNode* t = head;
        while(t){
            current->next = t->next;
            if(t->next) t->next = t->next->next;
            current = current->next;
            t = t->next;
        }
        current = head;
        while(current->next){
            current = current->next;
        }
        current->next = dummy->next;
        return head;
    }
};