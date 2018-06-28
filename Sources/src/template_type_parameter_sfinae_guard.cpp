#include <iostream>
#include <map>
#include <functional>
#include <type_traits>
#include <tuple>

template <typename Func,
        typename = typename std::enable_if<
                std::is_same<typename std::function<Func>::result_type, bool>::value
        >::type
>
class Test
{
    std::function<Func> foo;

public:
    Test(Func foo) : foo(foo) {}
    template <typename... Args>
    bool operator()(Args... args) { return foo(std::forward<Args>(args)...); }
};

int main() {
    std::map<int, Test<bool()>> m;
//    std::map<int, Test<int()>> m; // <-- compile error

    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(1),
              std::forward_as_tuple([]{return false;}));

    std::cout << m.at(1)() << std::endl;

    return 0;
}


