#include <iostream>
#include <thread>
#include <memory>

void thread_func1(void) {
    std::cout << "thread_func1\n";
}

void thread_func2(int x) {
    std::cout <<"thread_func2 = " << x << "\n";
}

struct Point{
    Point(int x,int y):x{x},y{y}{};
    int x;
    int y;
};

void thread_func3(Point &pt) {
// void thread_func3(const Point &pt) {
// void thread_func3(Point &&pt) {
    std:: cout << "thread_func3 = " << pt.x << "," << pt.y << "\n";
}

class SomeClass{

    public:
        void operator()(int x){
            std::cout << "Callable function = " << x << "\n";
        }
};

class BigObj{
    public:
    BigObj(int x):x{x}{}
    ~BigObj(){std::cout << "~BigObj\n";}
    int x{};
};

// Transfer ownership, can't be copied so its moved to parameter
void thread_func4(std::unique_ptr<BigObj> ptr){
    std::cout << "Big Object\n";
    ptr->x++;
    std::cout << "ptr->x = " << ptr->x << "\n";
    std::cout << "Big Object going out of scope!\n";
}

int main(void) {

    std::thread t1{thread_func1};
    if(t1.joinable()) {
        t1.join();
    }

    std::thread t2{thread_func2, 5};
    t2.join();

    Point pt{3,4};
    // *** Copied arguements as rvalues
    // std::thread t3{thread_func3,pt}; 
    std::thread t3{thread_func3,std::ref(pt)}; 
    t3.join();

    std::thread t4{SomeClass{},99};
    t4.join();

    std::thread t5{[]{std::cout << "Lambda!\n";}};
    t5.detach();

    std::unique_ptr uptr = std::make_unique<BigObj>(343);
    std::thread t6{thread_func4, std::move(uptr)};
    if(!uptr) {
        std::cout << "unique ptr is null\n";
    }
    t6.join();
    std::cout << "Joined!\n";

    return 0;
}
