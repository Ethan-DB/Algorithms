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


//解法二简化版代码
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
        if(head == nullptr) return nullptr;  
        ListNode* dummy = new ListNode(INT_MIN); //结果链表
        dummy->next = new ListNode(head->val); 
        head = head->next;
        while(head){
            ListNode* before = dummy;  //从头遍历找到合适的位置
            ListNode* after = before->next;
            
            while(after){
                if(head->val <= after->val){
                    ListNode* tmp = new ListNode(head->val);
                    tmp->next = after;
                    before->next = tmp;  
                    break;
                }else{
                    before = after;
                    after = before->next;
                }
            }
            //否则直接插入到before节点之后
            if(after == nullptr){
                ListNode* tmp = new ListNode(head->val);
                before->next = tmp;
            }
                
            head = head->next;
        }
        return dummy->next;
    }
};


// 解法三的简化代码
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
    ListNode* before;//从头遍历找到合适的位置
    ListNode* insertionSortList(ListNode* head) {
        if(head == nullptr) return nullptr;  
        ListNode* dummy = new ListNode(INT_MIN, new ListNode(head->val)); //结果链表
        head = head->next;
        while(head){
            before = dummy;
            while(before->next){
                if(head->val <= before->next->val){
                    before->next = new ListNode(head->val, before->next);  
                    break;
                }
                before = before->next;
            }
            //否则直接插入到before节点之后
            if(before->next == nullptr){
                before->next = new ListNode(head->val);
            }
                
            head = head->next;
        }
        return dummy->next;
    }
};


//解法四：链表插入排序的终极解法，分别对直接在（1）链表头部（第199行if语句）；（2）链表尾部插入做了优化（第208行if语句）。
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
    ListNode* before;//从头遍历找到合适的位置
    ListNode* last;  //记录最后一个指针
    int maxElement;  //记录一下最大值
    ListNode* insertionSortList(ListNode* head) {
        if(head == nullptr) return nullptr;  
        ListNode* dummy = new ListNode(INT_MIN, new ListNode(head->val)); //结果链表
        head = head->next;
        while(head){
            before = dummy;
            
            //直接在头部插入
            if(head->val <= dummy->next->val){
                ListNode* tmp = new ListNode(head->val, dummy->next);
                dummy->next = tmp;
                head = head->next;
                continue;
            }
            
            //浪费一些空间记录尾部指针，并且用max记录当前的最大值，如果新插入值head->val大于当前
            //最大值，则直接在尾部插入，这样子也免去了下面超长while的遍历过程，从而节省时间
            if(head->val > maxElement && last){
                //直接在最后位置插入
                ListNode* tmp = new ListNode(head->val);
                last->next = tmp;
                last = tmp;
                maxElement = head->val;
                head = head->next;
                continue;
            }
            
            //正常情况，这些值基本都在当前已排好序的链表中间插入，到底插入到哪里，需要遍历查找
            while(before->next){
                if(head->val <= before->next->val){
                    before->next = new ListNode(head->val, before->next);  
                    break;
                }
                before = before->next;
            }
            
            //说明上述while循环遍历到排好序链表的最后，则记录last指针，并且记录最大值
            if(before->next == nullptr){
                last = new ListNode(head->val);
                before->next = last;
                maxElement = head->val;
                 
            }
                
            head = head->next;
        }
        return dummy->next;
    }
};