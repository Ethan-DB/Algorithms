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

// 两遍扫描，
// 第一遍扫描求出长度
// 第二遍扫描求出整数
class Solution {
public:
    int getDecimalValue(ListNode* head) {
        if(head == nullptr) return 0;
        ListNode* current = head;
        int len = 0;
        while(current){
            len++;
            current = current->next;
        }
        
        current = head;
        int sum = 0;
        int shift = 1;
        while(current){
            sum += current->val * (1 << (len-shift));
            shift++;
            current = current->next;
        }
        return sum;
    }
};