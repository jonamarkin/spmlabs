#include <iostream>
#include <thread>

//Initial function call for each thread
void call_from_thread(int tid) {
    std::cout << "Launched by thread " << tid << std::endl;
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

/**
* Critical Sections: A section of code that is going to accessed by a single thread at a time.
 * In our case the critical section is the std::cout statement.
*/