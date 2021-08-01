//解法一：使用hash table来判断是否有重复，时间复杂度为O(n)，空间复杂度为O(n)，算法题一般只卡时间，很少卡空间，所以这里O(n)的空间复杂度也能AC
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_map<ListNode*, bool> m;
        ListNode* current = headA;
        while(current){
            m[current] = true;
            current = current->next;
        }
        
        current = headB;
        while(current){
            if(m.find(current) != m.end()){
                //说明找到了第一个交点
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};


/** 
	解法二：假设链表A = a * c ,链表B = b * c ，其中*表示交点，c表示它们相交的公共部分
	AB = a * c b * c
	BA = b * c a * c
	我们可以看到，这两个链表在第二个*之前，走过了相同的步长，也就是说如果相遇，二者指针一定会相同
	如果没有交点，那么就是
	A = a B = b
	AB = ab
	BA = ba
	经过相同的步长，最终两者会走到nullptr指针，结束这个过程
*/
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        
        if(p1 == nullptr || p2 == nullptr) return nullptr;
        
        while(p1 != nullptr && p2!= nullptr && p1 != p2){
            p1 = p1->next;
            p2 = p2->next;
            if(p1 == p2) break;
            
            if(p1 == nullptr) p1 = headB;  // 这里代表构成AB链表
            if(p2 == nullptr) p2 = headA;  //这里代表组成BA链表
        }
        
        return p1;
    }
};