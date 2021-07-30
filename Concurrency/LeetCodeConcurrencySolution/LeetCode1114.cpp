//mutex
class Foo {
public:
    mutex m1, m2, m3;
public:
    Foo() {
        m1.lock();
        m2.lock();
    }
    ~Foo(){
        m1.unlock();
        m2.unlock();
        m3.unlock();
    }

    void first(function<void()> printFirst) {
        m3.lock();
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        m1.unlock();
    }

    void second(function<void()> printSecond) {
        m1.lock();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        m2.unlock();
    }

    void third(function<void()> printThird) {
        m2.lock();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};



//condition variable
class Foo {
public:
    condition_variable cv;
    int i;
    mutex m;
public:
    Foo() {
        i = 1;
    }
    
    void first(function<void()> printFirst) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]{return (i==1)?true:false;});
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        i++;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]{return (i==2)?true:false;});
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        i++;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this]{return (i==3)?true:false;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

class Foo {
public:
    condition_variable cv;
    int i;
    mutex m;
public:
    Foo() {
        i = 1;
    }
    
    void first(function<void()> printFirst) { 
        unique_lock<mutex> lock(m);
        cv.wait(lock, [&]{return (i==1)?true:false;});
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        i++;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [&]{return (i==2)?true:false;});
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        i++;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [&]{return (i==3)?true:false;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

//lock_guard 是 mutex高级版本 
class Foo {
public:
    mutex m1, m2, m3;
public:
    Foo() {
        m2.lock();
        m3.lock();
    } //构造函数，当你构造类的变量的时候，就会默认先执行这个函数
    //线程之间的同步，如果我不指定线程的启动顺序，那么整个执行过程就是乱序的，所以我要通过mutex来指定线程
    //的启动顺序
    void first(function<void()> printFirst) {
        lock_guard<mutex> l(m1);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        m2.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> l(m2);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        m3.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> l(m3);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};


//lock guard + defer_lock
class Foo {
public:
    mutex m1, m2, m3;
public:
    Foo() {
        m2.lock();
        m3.lock();
    } //构造函数，当你构造类的变量的时候，就会默认先执行这个函数
    //线程之间的同步，如果我不指定线程的启动顺序，那么整个执行过程就是乱序的，所以我要通过mutex来指定线程
    //的启动顺序
    void first(function<void()> printFirst) {
        lock_guard<mutex> l(m1,std::defer_lock);
        l.lock();
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        m2.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> l(m2);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        m3.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> l(m3);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};