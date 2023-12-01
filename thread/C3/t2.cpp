#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <atomic>
#include <chrono>

std::mutex mtx;
std::stack<int> stk;

std::atomic<bool> done{};

int web_service(void) {
    static int var{};
    return ++var;
}

class WebServiceApi{
    int data{};
    public:
    int get_data(void){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return ++data;
    }
};


void thread_func_producer(std::)


// void thread_func_producer(void) {
//     while(!done) {
//         stk.push(++var);
        
//     }
// }

// void thread_func_consumer(void) {
//     while(!done) {
//         if(!stk.empty()) {
//             int var = stk.top();
//             stk.pop();
//         }
//         some_work(var);
//     }
// }

int main(void){

    return 0;
}