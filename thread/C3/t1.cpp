#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<bool> done{};
std::mutex mtx;


void thread_func(int id) {

    int runs{};
    while(!done) {
        {
            std::lock_guard<std::mutex> lock{mtx};
            runs++;
            for(int i{}; i < 5; i++){
            std::cout << id;
            }
            std::cout << std::endl;
            // STARVATION
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "Executed time = " << runs << "\n";
}

int main(void){

    int id{};

    std::thread t1{thread_func, id++};
    std::thread t2{thread_func, id++};
    std::thread t3{thread_func, id++};
    // std::thread t4{thread_func, id++};
    // std::thread t5{thread_func, id++};
    // std::thread t6{thread_func, id++};

    std::this_thread::sleep_for(std::chrono::seconds(6));
    done = true;
    t1.join();
    t2.join();
    t3.join();
    // t4.join();
    // t5.join();
    // t6.join();


    return 0;
}

/*

    Operating System Thread Scheduler:
        In a multi-threaded program, the operating system's thread scheduler is responsible for managing which threads are running at any given time.
        This scheduling is typically preemptive and based on various factors like thread priorities, time slices (quantum), and overall system load.
        The scheduler decides when to switch context from one thread to another. This decision is often opaque to the programmer and can seem unpredictable.

    Fairness and Starvation:
        In a situation where multiple threads compete for a mutex, the scheduler determines which waiting thread gets the mutex next.
        Theoretically, a fair scheduling policy would give each thread an equal opportunity to acquire the mutex. However, in practice, scheduling policies may not always be perfectly fair.
        This can lead to a situation called starvation, where one or more threads get significantly less access to a shared resource (like a mutex) compared to others. In extreme cases, a thread might seem like it's never getting a chance to run its critical section.

    Impact of Lock Holding Time:
        The length of time a thread holds a mutex can significantly impact the apparent fairness of thread scheduling.
        If a thread holds a mutex for a long time (especially if this includes operations like I/O or sleep), it reduces the frequency at which the mutex becomes available to other threads.
        This can make it seem as if one thread is dominating the mutex, especially if the scheduler happens to give that thread the mutex more often due to its timing of requests for the mutex.

    Mutex and Scheduler Interactions:
        When a thread attempts to acquire a mutex that is already held, it typically enters a wait state. The scheduler then decides when to wake up this thread to retry acquiring the mutex.
        The order in which threads are woken up or given the mutex is not guaranteed to be the order in which they requested it, leading to non-deterministic behavior in thread execution.

    Implications for Multi-threaded Programming:
        These aspects of thread scheduling underscore the importance of designing multi-threaded programs with an understanding that thread execution order is not guaranteed.
        Practices like keeping lock holding times short, avoiding long operations while holding a lock, and using higher-level constructs (like condition variables) for complex synchronization, can help create more efficient and fairer multi-threaded applications.

Understanding and working with the thread scheduler's behavior is a key part of multi-threaded programming, especially in scenarios where multiple threads compete for shared resources.

*/