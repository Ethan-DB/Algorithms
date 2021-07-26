class LRUCache {
public:
    struct Node{
        int key, value;
        Node *left, *right;
        Node(int _key, int _value): key(_key), value(_value), left(nullptr), right(nullptr){}
    };
    int n;
    Node *L, *R;
    unordered_map<int, Node*> hash;
    
    LRUCache(int capacity) {
        n = capacity;
        L = new Node(-1, -1), R = new Node(-1, -1);
        L->right = R;
        R->left = L;
    }
    
    void remove(Node* p){
        p->right->left = p->left;
        p->left->right = p->right;
        // p->left->right = R;
        // R->left = p->left;
    }
    
    void insert(Node* p){
        p->right = L->right;
        L->right->left = p;
        L->right = p;
        p->left = L;
    }
    
    int get(int key) {
        if(hash.find(key) == hash.end()) return -1;
        auto p = hash[key];
        remove(p);
        insert(p);
        return p->value;
    }
    
    void put(int key, int value) {
        if(hash.find(key) != hash.end()){
            //说明这个点已经存在，只需要更新value值，并将该节点插入到链表头
            auto p = hash[key];
            p->value = value;
            remove(p);
            insert(p);
            return;
        }else{
            if(hash.size() == n){
                auto p = R->left;
                remove(p);
                hash.erase(p->key);
                delete p;
            }
            auto q = new Node(key, value);
            hash[key] = q;
            insert(q);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */