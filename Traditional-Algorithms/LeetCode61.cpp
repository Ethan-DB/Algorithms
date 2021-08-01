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
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        
        ListNode* current = head;
        int len = 0;
        while(current){
            len++;
            current = current->next;
        }
        
        //计算到需要交换的前一个位置
        int before = len - (k % len);
        
        //很难找到的边界条件
        if(before == len){
            return head;
        }
        
        ListNode* beforeP;
        len = 0;
        current = head;
        while(current){
            len++;
            if(len == before) {
                beforeP = current;
                break;
            }
            current = current->next;
        }
        ListNode* dummy = new ListNode(-1, beforeP->next);
        beforeP->next = nullptr;
        
        //拼接head指针
        current = dummy->next;
        while(current && current->next){
            current = current->next;
        }
        if(current) current->next = head;
        return dummy->next;
    }
};