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
// 两次扫描，第一次扫描确定链表的长度以及最后一个元素的位置
// 第二次扫描找到拆分点
// 接着从拆分点重新连接即可
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
// 两次扫描，第一次扫描确定链表的长度以及最后一个元素的位置
// 第二次扫描找到拆分点
// 接着从拆分点重新连接即可
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        
        ListNode* current = head;
        ListNode* last;
        int len = 0;
        while(current->next){
            len++;
            current = current->next;
        }
        last=current;
        len++;
        
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
        // current = dummy->next;
        // while(current && current->next){
        //     current = current->next;
        // }
        // if(current) current->next = head;
        
        last->next = head; //尾结点在第一次扫描过程中已经确定，因此上述遍历操作无需执行。
        return dummy->next;
    }
};