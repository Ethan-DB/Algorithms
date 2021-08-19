// 利用额外的O(n)空间
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
    bool isPalindrome(ListNode* head) {
        if(head == nullptr) return true;
        ListNode* current = head;
        vector<int>ans;
        while(current){
            ans.push_back(current->val);
            current = current->next;
        }
        vector<int>reverseAns = ans;
        reverse(ans.begin(), ans.end());
        return ans == reverseAns;
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

// 快慢指针知道中间节点，将链表后半部分插入到一个新的链表中，此时只需要一个dummy指针，插入时每次都是插入到dummy之后，保证倒序
// 然后两个指针分别遍历原来的链表和新链表，只要相等就next，最后比较结束时，两者是否一样长
// 时间复杂度为O(n),空间复杂度为O(1)
class Solution {
public:
    ListNode* dummy = new ListNode(-1);
public:
    bool isPalindrome(ListNode* head) {
        // 首先快慢指针找到中点
        int len = 0;
        ListNode* t = head;
        while(t){
            len++;
            t = t->next;
        }
        if(len == 1) return true;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next){
            
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* current;
        if(len % 2 != 0){
            // 此时需要将slow->next在内的所有点倒序插入到一个新的链表中
            current = slow->next;
            while(current){
                insertElement(current->val);
                current = current->next;
            }
            slow->next = nullptr;
        }else{
            // 此时需要将包含slow在内的点全部插入到新的链表中，偶数个节点
            current = slow;
            while(current){
                insertElement(current->val);
                current = current->next;
            }
        }
        // 处理中点
        current = head;
        while(current && current->next != slow){
            current = current->next;
        }
        if(current) current->next = nullptr;

        // 比较两个链表
        ListNode* t1 = head;
        ListNode* t2 = dummy->next;
        while(t1 && t2){
            if(t1->val != t2->val) return false;
            t1 = t1->next;
            t2 = t2->next;
        }
        if(t1 == nullptr && t2 == nullptr) return true;
        return false;
    }
    
    // 完成倒序插入
    void insertElement(int u){
        ListNode* tmp = new ListNode(u);
        tmp->next = dummy->next;
        dummy->next = tmp;
    } 
};
