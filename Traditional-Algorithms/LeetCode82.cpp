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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) return nullptr;
        
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;
        while(head){
            if(head != nullptr && head->next == nullptr) {
                current->next = head;
                return dummy->next; 
            }
            if(head->next && head->val != head->next->val){
                current->next = new ListNode(head->val);
                current = current->next;
                head = head->next;
            }else{
                //计算需要跳跃的步长
                ListNode* tmp;
                if(head->next)  tmp = head->next;
                while(tmp && tmp->val == head->val){
                    tmp = tmp->next;
                }
                head = tmp;
            }
        }
        return dummy->next;        
    }
};


// 对上面方法写法进行优化，简化一些不必要的判断
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) return nullptr;
        
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;
        while(head && head->next){
            if(head->next && head->val != head->next->val){
                current->next = new ListNode(head->val);
                current = current->next;
                head = head->next;
            }else{
                //计算需要跳跃的步长
                ListNode* tmp = head->next;
                while(tmp && tmp->val == head->val){
                    tmp = tmp->next;
                }
                head = tmp;
            }
        }
        current->next = head;
        return dummy->next;        
    }
};