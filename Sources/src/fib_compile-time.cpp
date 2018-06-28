/* Problem solution: Use compile time 1 */

#include <iostream>

template<int n>
struct fibonacci
{
    static constexpr unsigned long long value = fibonacci<n-1>::value + fibonacci<n-2>::value;
};
template<>
struct fibonacci<0>
{
    static constexpr unsigned long long value = 0;
};
template<>
struct fibonacci<1>
{
    static constexpr unsigned long long value = 1;
};

int main(int argc, const char* argv[]) {
    std::cout << fibonacci<48>::value << std::endl;
    return 0;
}

