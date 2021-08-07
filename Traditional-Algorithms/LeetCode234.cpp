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



