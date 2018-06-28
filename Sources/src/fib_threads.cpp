/* Problem solution: Use threads */

#include <iostream>
#include <thread>
#include <future>
#include <ctime>

int main(int argc, const char* argv[]) {
    (void)argc;
    (void)argv;
    
    auto fibonacci_task = [](const int &number) -> uint64_t{
        // NOTE: random getter to disable modern CPU branch-prediction and OS scheduler optimization
        // this (may) make a run-time duration non deterministic in a micro-seconds scale.
        // In order to get more random values Pseudo-random number generation such as
        // `mt19937` or `minstd_rand` should be used
        {
            std::srand(std::time(nullptr));
            volatile auto x = std::rand();
            (void) x;
        }

        // NOTE: iterative algorithm
        uint64_t f = 0, f0 = 0, f1 = 1;
        for (int i = 0; i <= number; i++) {
            if (i > 1) {
                f = f0 + f1;
                f0 = f1;
                f1 = f;
            } else
                f = static_cast<uint64_t>(i);
        }

        return f;
    };

    std::packaged_task<uint64_t(const int&)> task(fibonacci_task);
    std::future<uint64_t> f1 = task.get_future();
    std::thread t(std::move(task), 48);
    t.detach();

    std::future<uint64_t> f2 = std::async(std::launch::async, fibonacci_task, 48);

    std::promise<uint64_t> p;
    std::future<uint64_t> f3 = p.get_future();
    std::thread( [&p, &fibonacci_task]{
        const auto result = fibonacci_task(48);
        p.set_value_at_thread_exit(result); }).detach();

    f1.wait();
    f2.wait();
    f3.wait();

    std::cout << f1.get() << std::endl;
    std::cout << f2.get() << std::endl;
    std::cout << f3.get() << std::endl;

    return EXIT_SUCCESS;
}