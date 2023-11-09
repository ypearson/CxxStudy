#include <iostream>
#include <thread>
#include <vector>

void thread_func(void){
    std::cout << "Some work from thread:" << std::this_thread::get_id() << "\n";
}

int main(void) {

    std::vector<std::thread> threads;

    for(int i{}; i < 10; i++) {
        threads.emplace_back(thread_func);
    }

    for(auto &t : threads) {
        t.join();
    }

    return 0;
}