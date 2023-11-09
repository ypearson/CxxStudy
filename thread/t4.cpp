#include <iostream>
#include <thread>

// 1. Default-constructed Thread: A thread object that has been default-constructed and
// not yet associated with a runnable task is not joinable. It doesn't represent an actual 
// thread of execution.
// std::thread t; // t is not joinable here

// 2. Moved-from Thread: If a thread object has been moved from, such as by transferring its 
// responsibilities to another thread object, it is no longer joinable. The original thread 
// object no longer represents the thread of execution.

// std::thread t1(someFunction);
// std::thread t2 = std::move(t1); // t1 is not joinable after this move

// 3. Thread that has Finished Execution: Once a thread has completed its execution and
// returned from its associated function, it is no longer joinable.

// std::thread t(someFunction);
// t.join(); // After join, t is not joinable

// 4. Thread that has been Detached: If a thread has been detached using the std::thread::detach() 
// method, it is not joinable. The thread continues to execute independently in the background,
// and the thread object no longer has any association with it.

// std::thread t(someFunction);
// t.detach(); // t is not joinable after being detached

class ScopedThread{

    public:
    ScopedThread(std::thread _t):t{std::move(_t)}{
        if(!t.joinable()) {
            throw std::logic_error("Need to be a joinable thread!");
        }
    }
    ~ScopedThread(void) {
        t.join();
    }
    ScopedThread(const ScopedThread& other)=delete;
    ScopedThread &operator=(const ScopedThread& other)=delete;

    private:
    std::thread t;
};

void thread_func(void){
    std::cout << "thread_func\n";
}

int main(void){

    // std::thread t1; // Not joinable
    
    std::thread t1{thread_func};

    ScopedThread st{std::move(t1)};

    return 0;
}