#include <iostream>
#include <memory>

class Foo {
 public:
  // Foo is not copyable.
  Foo(const Foo&) = delete;
  Foo& operator=(const Foo&) = delete;

 private:
  Foo() {
    // Constructor implementation here, if needed.
  }

  // Only FooFactory can create Foo instances.
  friend class FooFactory;
};

class FooFactory {
 public:
  static std::unique_ptr<Foo> Create() {
    return std::unique_ptr<Foo>(new Foo{});
  }
};

int main() {
  // Using the factory to create an instance of Foo.
  std::unique_ptr<Foo> fooPtr = FooFactory::Create();

  return 0;
}
