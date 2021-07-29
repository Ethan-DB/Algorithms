/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    var dummy *ListNode
    tmp := ListNode{-1, nil}
    dummy = &tmp
    current := dummy
    for;l1 != nil && l2 != nil;{
        if l1.Val < l2.Val{
            current.Next = &ListNode{l1.Val, nil}
            l1 = l1.Next
        }else{
            current.Next = &ListNode{l2.Val, nil}
            l2 = l2.Next
        }
        current = current.Next
    }
    if l1 != nil{
        current.Next = l1
    }
    if l2 != nil{
        current.Next = l2
    }
    return dummy.Next
}


//简化版代码
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode { 
    dummy := &ListNode{-1, nil}
    current := dummy
    for;l1 != nil && l2 != nil;{
        if l1.Val < l2.Val{
            current.Next = &ListNode{l1.Val, nil}
            l1 = l1.Next
        }else{
            current.Next = &ListNode{l2.Val, nil}
            l2 = l2.Next
        }
        current = current.Next
    }
    if l1 != nil{
        current.Next = l1
    }
    if l2 != nil{
        current.Next = l2
    }
    return dummy.Next
}