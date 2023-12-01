#include <iostream>
#include <thread>

class jthread{
    std::thread t;
    public:
    jthread() noexcept=default;
    ~jthread(){if(joinable()) join();}
    template<typename Callable, typename ...Args>
    explicit jthread(Callable&& func, Args&& ...args):
    t{std::forward<Callable>(func), std::forward<Args>(args)...}{}
    explicit jthread(std::thread t_) noexcept: t(std::move(t_)){}
    jthread(jthread&& other) noexcept: t(std::move(other.t)){}
    jthread& operator=(jthread&& other) noexcept {
        if(joinable()){
            join();
        }
        t = std::move(other.t);
        return *this;
    }
    void swap(jthread& other) {
        t.swap(other.t);
    }

    std::thread::id get_id() const noexcept {
        return t.get_id();
    }
    bool joinable(void) const { return joinable();}
    void join(void) { t.join(); }
    void detach(void) {
        t.detach();
    }
    std::thread& as_thread(void) noexcept {
        return t;
    }
    const std::thread& as_thread(void) const noexcept {
        return t;
    }
};



int main(void){



    return 0;
}