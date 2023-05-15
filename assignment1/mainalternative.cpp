#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>
#include <functional>


template<typename T>
void parallel_map(std::vector<T>& v, std::function<T(T)> f, int num_workers) {
    const int chunk_size = v.size() / num_workers;

    std::vector<std::thread> threads;
    std::mutex mutex;

    auto thread_fn = [&](int start_idx) {
        for (int i = start_idx; i < start_idx + chunk_size && i < v.size(); i++) {
            v[i] = f(v[i]);
        }
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Thread " << std::this_thread::get_id() << " finished." << std::endl;
    };

    for (int i = 0; i < num_workers; i++) {
        threads.emplace_back(thread_fn, i * chunk_size);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Error: Usage: " << argv[0] << " <vector_length> <num_workers>" << std::endl;
        return 1;
    }

    try {
        int n = std::stoi(argv[1]);
        int num_workers = std::stoi(argv[2]);

        if (n <= 0 || num_workers <= 0) {
            std::cerr << "Error: Vector length and number of workers must be positive integers." << std::endl;
            return 1;
        }

        std::vector<int> v(n);
        std::iota(v.begin(), v.end(), 1);
        std::function<int(int)> f = [](int x) { return x * 2; };

        std::cout << "Sequential computation:" << std::endl;
        for (int i = 0; i < v.size(); i++) {
            v[i] = f(v[i]);
        }

        for (auto& x : v) {
            std::cout << x << " ";
        }
        std::cout << std::endl;

        std::cout << "Parallel computation:" << std::endl;
        parallel_map(v, f, num_workers);

        for (auto& x : v) {
            std::cout << x << " ";
        }
        std::cout << std::endl;

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
