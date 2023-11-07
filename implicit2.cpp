#include <iostream>
#include <string>

class MyString {
  std::string data;

 public:
  explicit MyString(const char* s) : data(s) {}
  const std::string& get() const { return data; }
};

void foo(MyString s) { std::cout << s.get() << std::endl; }

int main() {
  // foo("Hello");  // Error: No implicit conversion allowed
  foo(MyString("Hello"));  // Explicitly constructs MyString from const char*
}
