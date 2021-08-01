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

//交换这两个点的本质是交换对应位置的val，指针并不需要交换

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* current = head;
        ListNode* last;
        int len = 0;
        while(current->next){
            len++;
            current = current->next;
        }
        
        last = current;
        len++;
        if(k == 1 || k == len){
            //说明当前交换首尾指针
            int tmp = head->val;
            head->val = last->val;
            last->val = tmp;
            return head;
        }
        
        //交换中间节点
        
        int first = k;
        int second = len - k + 1;
        ListNode* firstP;
        ListNode* secondP;
        
        current = head;
        len = 0;
        while(current){
            len++;
            if(len == first) firstP = current;
            if(len == second) secondP = current;
            current = current->next;
        }
        
        int tmp = firstP->val;
        firstP->val = secondP->val;
        secondP->val = tmp;
        
        return head;
        
        
    }
};