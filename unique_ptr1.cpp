#include <iostream>
#include <memory>

class MyClass {
 public:
  MyClass(int value) : value_(value) {
    std::cout << "MyClass constructed with value: " << value << std::endl;
  }

  void PrintValue() { std::cout << "Value: " << value_ << std::endl; }

 private:
  int value_;
};

int main() {
  // Creating a unique_ptr to dynamically allocate a MyClass object
  std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);

  // Access and use the object through the unique_ptr
  uniquePtr->PrintValue();

  // When uniquePtr goes out of scope, the MyClass object is automatically
  // deleted.
  return 0;
}
