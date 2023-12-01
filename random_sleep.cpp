#include <chrono>
#include <random>
#include <thread>

void random_sleep(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> range(50,1000);
    int sleep_time_ms = range(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
