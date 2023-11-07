#include <iostream>

class Complex {
 private:
  double real, imag;

 public:
  // Implicit conversion constructor: Convert double to Complex
  Complex(double r, double i) : real(r), imag(i) {}

  // explicit Complex(double r, double i) : real(r), imag(i) {}

  void display() const {
    std::cout << "(" << real << ", " << imag << "i)" << std::endl;
  }
};

void printComplex(const Complex& c) { c.display(); }

int main() {
  double num = 5.0;

  // Here, the double is implicitly converted to a Complex number
  printComplex({1, 2});
}
