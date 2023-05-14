#include <iostream>
#include <thread>
#include <mutex>

//Initializes the mutex for the critical section
//Mutex stands for mutual exclusion
//It is a lock that is used to protect shared data from being accessed by multiple threads at the same time
std::mutex mtx;

//Initial function call for each thread
void call_from_thread(int tid) {
    //Locks the mutex
    mtx.lock();
    std::cout << "Launched by thread " << tid << std::endl;
    //Unlocks the mutex
    mtx.unlock();
}

int main() {
    std::thread t[10];

    //Launch a group of threads
    for (int i = 0; i < 10; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }

    std::cout << "Launched from the main\n";

    //Join the threads with the main thread
    //Wait for all threads to finish
    for (int i = 0; i < 10; ++i) {
        t[i].join();
    }

    return 0;
}

