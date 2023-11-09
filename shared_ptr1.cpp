#include <iostream>
#include <memory>

class Car{
    public:
        Car(int x):id{x}{std::cout << "Count = " << ++cnt << "\n";}
        ~Car(){std::cout << "Boom " << id << "\n";}
        void beep(void) {
            std::cout << id << " : " << "Beep\n";
        }
    private:
    inline static int cnt{0};
    int id;
};

int main(void) {

    std::unique_ptr<Car> car1 = std::make_unique<Car>(0);
    std::unique_ptr<Car> car2 = std::make_unique<Car>(1);

    car1->beep();

    std::unique_ptr<Car> moved_car = std::move(car2);
    moved_car->beep();


    std::shared_ptr<Car> shared = std::make_shared<Car>(2);
    std::cout << "Is Unique = " << shared.unique() << "\n";
    std::shared_ptr<Car> shared1 = shared;
    std::shared_ptr<Car> shared2 = shared;

    std::cout << "Use Count = " << shared.use_count() << "\n";
    std::cout << "Is Unique = " << shared.unique() << "\n";

    shared->beep();
    shared1->beep();
    shared2->beep();

    std::cout << shared2.use_count() << "\n";
    
    return 0;
}