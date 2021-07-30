//condition variable
class FooBar {
private:
    int n;
    bool flag;
    mutex m;
    condition_variable cv;
public:
    FooBar(int n) {
        this->n = n;
        flag = false;
    }

    void foo(function<void()> printFoo) {
        unique_lock<mutex> lock(m);
        for (int i = 0; i < n; i++) { 
            cv.wait(lock, [this] {return (flag == false)?true:false;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            flag = true;
            cv.notify_one();
        }
        
    }

    void bar(function<void()> printBar) {
        unique_lock<mutex> lock(m);
        for (int i = 0; i < n; i++) {
            cv.wait(lock, [this] {return (flag == true)?true:false;});
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            flag = false;
            cv.notify_one();
        }
    }
};

//mutex
class FooBar {
private:
    int n;
    mutex m1, m2;
public:
    FooBar(int n) {
        this->n = n;
        m2.lock();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            m1.lock();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            m2.unlock();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            m2.lock();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            m1.unlock();
        }
    }
};