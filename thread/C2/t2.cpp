#include <thread>
#include <iostream>
#include <atomic>

// Atomicity: std::atomic types guarantee atomicity of operations. This means that when 
// one thread writes to an std::atomic<bool> variable, and another thread reads from it, 
// the read operation will see either the complete value before the write or the complete 
// value after the write, nothing in between. With a plain bool, a write operation could 
// be interleaved with a read operation on some architectures, leading to undefined behavior.

std::atomic<bool> done{};

void thread_funcA(void) {
    while(!done){
        std::cout << "A Thread function: " << std::this_thread::get_id() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }
}

void thread_funcB(void) {
    while(!done){
        std::cout << "B Thread function: " << std::this_thread::get_id() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }
}

int main(void) {

    std::thread t1{thread_funcA};
    std::thread t2{thread_funcB};
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // Threads are moved, not copied
    // Thread t2 is terminated before its moved
    t2 = std::move(t1); // --> ***This will terminate the program***

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    done = true;

    if(t1.joinable()){
        t1.join();
    }

    if(t2.joinable()){
        t2.join();
    }
}