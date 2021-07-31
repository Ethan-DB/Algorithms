//解法一：作弊解法，空间复杂度O(n)，时间复杂度O(nlogn)
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode* current = head;
        vector<int> ans;
        while(current != nullptr){
            ans.push_back(current->val);
            current = current->next;
        }
        
        sort(ans.begin(), ans.end());
        
        int len = ans.size();
        head = new ListNode(0);
        current = head;
        for(int i = 0 ; i < len; i++){
            current->next = new ListNode(ans[i]);
            current = current->next;
        }
        return head->next;
    }
};
// 解法二： 实现链表插入排序，时间复杂度为O(n^2)，空间复杂度为O(1)
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummy = new ListNode(-1); //结果链表
        if(head == nullptr) return nullptr;
        
        dummy->next = new ListNode(head->val);
        
        ListNode* current = head->next;
        while(current){
            ListNode* before = dummy->next;  //从头遍历找到合适的位置
            ListNode* after = before->next;
            if(dummy->next->val >= current->val){
                //将当前head的值插入到dummy节点之后
                //在虚拟头结点后面插入数据
                ListNode* tmp = new ListNode(current->val);
                tmp->next = dummy->next;
                dummy->next = tmp;
            }else{
                //否则应该从dummy开始遍历当前节点，找到合适的位置插入
                while(before && after){
                    if(current->val >= before->val && current->val <= after->val){
                        ListNode* tmp = new ListNode(current->val);
                        tmp->next = after;
                        before->next = tmp;  
                        break;
                    }else{
                        before = after;
                        after= before->next;
                    }
                }
                //否则直接插入到before节点之后
                if(after == nullptr){
                    ListNode* tmp = new ListNode(current->val);
                    before->next = tmp;
                }
                
            }
            current = current->next;
        }
        return dummy->next;
    }
};
