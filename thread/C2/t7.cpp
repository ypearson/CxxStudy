#include <iostream>
#include <thread>



int main(void) {


    std::cout << "Number of threads that can run truly concurrently = " << std::thread::hardware_concurrency() << "\n";


    return 0;
}