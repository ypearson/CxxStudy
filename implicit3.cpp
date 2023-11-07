#include <iostream>

class Meters {
 private:
  double meters;

 public:
  Meters(double m) : meters(m) {}

  // Implicit conversion operator to double
  operator double() const { return meters; }
  double get() const { return meters; }

  // explicit operator double() const {
  //     return meters;
  // }
};

void printDistance(double distance) {
  std::cout << "Distance: " << distance << " meters" << std::endl;
}

void printDistanceM(const Meters &m) { printDistance(m); }

int main() {
  Meters m(5.0);

  // Here, the Meters object is implicitly converted to double
  printDistance(m);  // Outputs: Distance: 5 meters

  printDistanceM(5.2);

  // printDistance(static_cast<double>(m));
}
