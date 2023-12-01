#include <iostream>
#include <vector>
#include <thread>
#include <cstring> // Include for strerror

std::vector<int> getAffinity(std::thread& th) {
    std::vector<int> cores;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);

    int rc = pthread_getaffinity_np(th.native_handle(), sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
        std::cerr << "Error getting thread affinity: " << strerror(rc) << "\n";
        return cores; // Return an empty vector in case of error
    }

    int num_cores = std::thread::hardware_concurrency();
    for (int i = 0; i < num_cores; ++i) {
        if (CPU_ISSET(i, &cpuset)) {
            cores.push_back(i);
        }
    }

    return cores;
}


void setAffinity(std::thread& th, unsigned int core_id) {

    // Check if core_id is out of bounds
    if (core_id >= std::thread::hardware_concurrency()) {
        std::cerr << "Error: core_id is out of bounds\n";
        return;
    }

    // Check if the thread is joinable (active)
    if (!th.joinable()) {
        std::cerr << "Error: Thread is not joinable\n";
        return;
    }

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    int rc = pthread_setaffinity_np(th.native_handle(), sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
        // pthread_setaffinity_np returns non-zero error number on failure
        std::cerr << "Error setting thread affinity: " << strerror(rc) << "\n";
    }
}


void thread_func(int param) {
    std::cout << "Thread function: " << param << "\n";
    int core_id = sched_getcpu();
    std::cout << "Thread " << param << " running on core [" << core_id << "] of " << std::thread::hardware_concurrency() <<"\n";
}

std::thread getThread(void) {
    static int id{};
    return std::thread{thread_func, id++};
}

int main(void) {

    std::thread t1{getThread()};
    setAffinity(t1, 15);
    std::thread t2{getThread()};
    std::thread t3{getThread()};

    std::thread thread_L_value = getThread();
    std::thread t4{std::move(thread_L_value)};

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}