/* Compiler doesnt auto pick linked pthread library 
sudo g++ -std=c++17 -pthread -o main lockVariable.cpp
./main
*/

#include <iostream>
#include <thread>

int lock = 0;

// Context switch happens bcoz Lock is not atomic and result comes random
// So never assume Scheduling and speed, Priority can be switched in between by CPU

class thread_object { // Auto. Callable in c++ - operator overloading
public:
    void operator()(int& x) {
        for (int i = 0; i<100000; ++i) {
            while (lock != 0); // wait if lock alreday acquired 
            // else set acquired & perform critical section
            lock = 1;
            x += 1; // Its Critical - bcoz x is shared b/w all threads - So Lock is applied
            // std::cout<<x<<std::endl;
            lock =0;
        }
    }
};

int main() {
    int x = 0;
    thread_object obj;
    std::thread t1(obj, std::ref(x)); // Process 1
    std::thread t2(obj, std::ref(x)); // Process 2

    // wait for all threads to execute so apply join
    t1.join();
    t2.join();

    std::cout<<"Final value of x: "<<x<<std::endl;
    return 0;
}