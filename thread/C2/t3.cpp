#include <iostream>
#include <thread>


void thread_func(void){
    std::cout << "thread_func = " << std::this_thread::get_id() << "\n";
}

std::thread get_thread(void) {
    return std::thread{thread_func};
}

int main(void){

    auto t1 = get_thread();
    auto t2 = get_thread();
    auto t3 = get_thread();

    t1.join();
    t2.join();
    t3.join();

    return 0;
}