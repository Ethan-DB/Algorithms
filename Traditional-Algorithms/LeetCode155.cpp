//采用数组+两个小顶堆的方式实现
class MinStack {
public:
    /** initialize your data structure here. */
    const static int N = 3e4+10;
    int arr[N];
    int len = 0;
    priority_queue<int, vector<int>,greater<int>> q;
    priority_queue<int, vector<int>,greater<int>> d;
    
    MinStack() {
        
    }
    
    void push(int val) {
        arr[len] = val;
        len++;
        q.push(val);
    }
    
    void pop() {
        auto h = arr[len-1];
        len--;
        d.push(h);
        while(q.top() == d.top()){
            q.pop();
            d.pop();
            if(q.size() == len) break;
        }
    }
    
    int top() {
        return arr[len-1];
    }
    
    int getMin() {
        return q.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
 
 
 //采用两个数组实现
class MinStack {
public:
    /** initialize your data structure here. */
    const static int N = 3e4+10;
    int arr1[N];
    int arr2[N];
    int len = 0;
    
    MinStack() {
        
    }
    
    void push(int val) {
        arr1[len] = val;
        if(len == 0) arr2[len] = val;
        else{
            if(val < arr2[len-1]) arr2[len] = val;
            else arr2[len] = arr2[len-1];
        }
        len++;
    }
    
    void pop() {
        if(len > 0) len--;
    }
    
    int top() {
        return arr1[len-1];
    }
    
    int getMin() {
        return arr2[len-1];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
 
 
 // 两个STL stack实现
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> s;
    stack<int> min;
    MinStack() {
        
    }
    
    void push(int val) {
        s.push(val);
        if(min.empty()){
            min.push(val);
        }else{
            if(val < min.top()) min.push(val);
            else min.push(min.top());
        }
        
    }
    
    void pop() {
        s.pop();
        min.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */