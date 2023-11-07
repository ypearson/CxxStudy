#include <iostream>
#include <thread>

// So, within a single thread, threadLocalVar behaves like a global variable,
// but each thread has its own independent copy of it. It's not a true global
// variable in the sense that it's shared across all threads; instead, it's
// global within the scope of a single thread.

// Define a thread-local variable
thread_local int threadLocalVar = 0;

// A function that increments the thread-local variable
void IncrementThreadLocalVar() {
  // Each thread has its own copy of threadLocalVar
  threadLocalVar++;
  std::cout << "Thread " << std::this_thread::get_id()
            << " - threadLocalVar: " << threadLocalVar << std::endl;
}

// you can declare a thread_local variable inside a thread function, and it will
// be thread-local to that specific thread.  When you declare a thread_local
// variable within a thread function, that variable will have a separate
// instance for each thread that executes the function. Here's an example to
// illustrate this:

void ThreadFunction() {
  thread_local int threadLocalVar = 0;

  threadLocalVar++;  // Modify the thread-local variable
  std::cout << "Thread " << std::this_thread::get_id()
            << " - threadLocalVar: " << threadLocalVar << std::endl;
}

void print(void) { std::cout << "**" << threadLocalVar << std::endl; }

int main() {
  // Create two threads
  std::thread thread1(IncrementThreadLocalVar);
  std::thread thread2(IncrementThreadLocalVar);

  // std::thread thread1(ThreadFunction);
  // std::thread thread2(ThreadFunction);

  // Wait for both threads to finish
  thread1.join();
  thread2.join();

  // In the main thread, the threadLocalVar is not affected by the other threads
  std::cout << "Main thread - threadLocalVar: " << threadLocalVar << std::endl;

  return 0;
}
