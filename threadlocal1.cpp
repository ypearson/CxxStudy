// C++ Program to demonstrate the use of thread-local
// storage.
#include <iostream>
#include <thread>

using namespace std;

class Singleton {
 public:
  static Singleton& getInstance() {
    // Each thread will have its own instance of
    // Singleton
    thread_local Singleton instance;
    return instance;
  }

  void printMessage() {
    cout << "Hello from thread " << this_thread::get_id() << endl;
  }

 private:
  Singleton() = default;
};

void workerThread() { Singleton::getInstance().printMessage(); }

int main() {
  // Create first thread
  thread t1(workerThread);
  // Create second thread
  thread t2(workerThread);

  // Wait for the first thread to finish
  t1.join();
  // Wait for the second thread to finish
  t2.join();
  return 0;
}
