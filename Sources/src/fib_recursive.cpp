/* Common implementation 1: Recursive algorithm */

#include <iostream>

constexpr unsigned long long fibonacci(const int& n)
{
    if(n <= 1)
        return static_cast<unsigned long long>(n);
    else
        return fibonacci(n - 2) + fibonacci(n - 1);
}

int main(int argc, const char* argv[]) {
    (void)argc;
    (void)argv;

    const auto result = ::fibonacci(48);
    std::cout << result << std::endl;
    return 0;
}

