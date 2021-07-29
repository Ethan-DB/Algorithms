class MyLinkedList {
public:
    /** Initialize your data structure here. */
    struct Node{
        int val;
        Node* prev;
        Node* next;
        
        Node(int _val): val(_val), prev(nullptr), next(nullptr){};
    }* L, *R;
    int len;
    
    //构造函数
    MyLinkedList() {
        L = new Node(-1);
        R = new Node(-1);
        
        //双向非循环链表
        L->next = R;
        R->prev = L;
        len = 0;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if(index > len-1) return -1;
        int position = 0;
        Node* current = L->next;
        while(current){
            if(position == index){
                return current->val;                
            }else{
                current = current->next;
                position++;
            }
        }
        return -1;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Node* tmp = new Node(val);
        tmp->next = L->next;
        L->next->prev = tmp;
        L->next = tmp;
        tmp->prev = L;
        len++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* tmp = new Node(val);
        tmp->prev = R->prev;
        R->prev->next = tmp;
        R->prev = tmp;
        tmp->next = R;
        len++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        //在index-1之后插入元素，索引从0开始计数
        if(index > len) return;
        if(index == 0){
            addAtHead(val);
            len++;
            return;
        }
        int position = 0;
        Node* current = L->next;
        while(current){
            if(position == index-1){
                //在current之后插入
                Node* tmp = new Node(val);
                tmp->next = current->next;
                current->next->prev = tmp;
                current->next= tmp;
                tmp->prev = current;
                break;
                
            }else{
                current = current->next;
                position++;
            }
        }
        len++;
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        //删除index位置的元素，索引从0开始计数
        if(index >= len) return;
        int position = 0;
        Node* current = L->next;
        while(current){
            if(position == index){
                //删除当前current元素
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                break;
            }else{
                current = current->next;
                position++;
            }
        }
        len--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */