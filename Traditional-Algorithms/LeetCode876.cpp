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
    ListNode* middleNode(ListNode* head) {
        vector<ListNode*> ans;
        ListNode* current = head;
        while(current != nullptr){
            ans.push_back(current);
            current = current->next;
        }
        return ans[ans.size()/2];
    }
};

//快慢指针
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
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        int flag = 0;
        while(fast->next != nullptr && fast->next->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(fast->next == nullptr){
            return slow;
        }
        return slow->next;
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

// 快慢指针：首先思考，什么是中点？如果有两个指针，一个指针每次走两个，一个指针每次走一步
// 当快指针走到结束点时，慢指针刚刚好走过快指针一般的路程，此时找到的就是中点
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if(head == nullptr) return nullptr;
        ListNode* slow = head;   // 慢指针
        ListNode* fast = head; // 快指针
        
        while(fast && fast->next){
            slow = slow->next;  //慢指针每次走一步
            fast = fast->next->next;  //快指针每次走两步
        }
        return slow;
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
// 两遍扫描算法：第一遍找到链表的总长度，然后计算出中间位置，第二遍扫描在中间位置返回结果
// 从示例中看出，奇数和偶数的处理方法不一样
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* current = head;
        int len = 0;
        while(current){
            len++;
            current = current->next;
        }
        
        int middle = (len / 2) + 1;
        
        current = head;
        len = 0;
        while(current){
            len++;
            if(len == middle) return current;
            current = current->next;
        }
        return nullptr;
    }
};