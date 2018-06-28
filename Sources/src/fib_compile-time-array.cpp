/* Problem solution: Use compile time 2 */

#include <iostream>
#include <array>

template <std::size_t N, std::size_t NN>
struct Fibonacci_Array{
    enum : unsigned long long{ value = Fibonacci_Array<N-1, NN>::value + Fibonacci_Array<N-2, NN>::value };
    static void add_values(std::array<unsigned long long, NN>& v){
        Fibonacci_Array<N-1, NN>::add_values(v);
        v[N-1] = value; }
};

template <std::size_t N>
struct Fibonacci_Array<0, N>{
    enum : unsigned long long{ value = 0 };
    static void add_values(std::array<unsigned long long, N>& v){
        v[0] = value; }
};

template <std::size_t N>
struct Fibonacci_Array<1, N>{
    enum : unsigned long long{ value = 1 };
    static void add_values(std::array<unsigned long long, N>& v){
        Fibonacci_Array<0, N>::add_values(v);
        v[1] = value; }
};

template <std::size_t N>
struct Array{
    static void fill(std::array<unsigned long long, N>& array){
        Fibonacci_Array<N, N>::add_values(array); };
};

int main(int argc, const char* argv[]) {
    const unsigned long long array_size = 48;
    std::array<unsigned long long, array_size> array;
    Array<array_size>::fill(array);

    std::cout << array[47] << std::endl;

    return 0;
}

