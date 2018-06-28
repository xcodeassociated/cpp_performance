#include <string>

#include <vector>
#include <array>
#include <list>

#include <type_traits>

// ===================================================================

struct foo {
    typedef float foobar;
    std::size_t size() const { return 0; }
    //static std::size_t size() { return 0; } //OR
    int x;
};

// ===================================================================

template<typename T>
class IsClass {
private:
    typedef char One;
    typedef struct { char a[2]; } Two;
    template<typename C> static One test(int C::*);
    template<typename C> static Two test(...);
    enum { Yes = sizeof(IsClass<T>::test<T>(0)) == 1 };
    enum { No = !Yes };
public:
    static const bool value = IsClass<T>::Yes;
};

// ===================================================================

template <typename T>
struct has_typedef_foobar {
    typedef char yes[1];
    typedef char no[2];

    template <typename C>
    static yes& test(typename C::foobar*);

    template <typename>
    static no& test(...);
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
};

// ===================================================================

template <typename T>
class has_size {
private:
    typedef char Yes;
    typedef Yes No[2];
    template <typename U, U> struct really_has;
    // NOTE: both `const` and `non-const` "size(void)" method
    template <typename C> static Yes& Test(really_has <size_t (C::*)() const, &C::size>*);
    template <typename C> static Yes& Test(really_has <size_t (C::*)(), &C::size>*);
    template <typename> static No& Test(...);
public:
    static bool const value = sizeof(Test<T>(0)) == sizeof(Yes);
};

// ===================================================================

template<typename T> struct HasX {
    struct Fallback { int x; }; // introduce member name "x"
    struct Derived : T, Fallback { };
    template<typename C, C> struct ChT;
    template<typename C> static char (&f(ChT<int Fallback::*, &C::x>*))[1];
    template<typename C> static char (&f(...))[2];

    static bool const value = sizeof(f<Derived>(0)) == 2;
};

// ===================================================================

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename ... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        std::conditional_t<
                false,
                is_container_helper<
                        typename T::value_type,
                        typename T::size_type,
                        typename T::allocator_type,
                        typename T::iterator,
                        typename T::const_iterator,
                        decltype(std::declval<T>().size()),
                        decltype(std::declval<T>().begin()),
                        decltype(std::declval<T>().end()),
                        decltype(std::declval<T>().cbegin()),
                        decltype(std::declval<T>().cend())
                >,
                void
        >
> : public std::true_type {};

// ===================================================================

template<typename T, typename = void>
struct is_iterator{
    static constexpr bool value = false;
};
template<typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<
        typename std::iterator_traits<T>::value_type, void>::value>::type>{
    static constexpr bool value = true;
};

// ===================================================================


int main(int argc, const char* argv[]) {

    static_assert(IsClass< foo >::value);
    static_assert(!IsClass< int >::value);

    static_assert(!has_typedef_foobar< int >::value);
    static_assert(has_typedef_foobar< foo >::value);

    static_assert(!has_size< int >::value);
    static_assert(has_size< foo >::value);

    static_assert(HasX< foo >::value);
    static_assert(HasX< double >::value); // "required from here"

    static_assert(is_container< std::vector<int> >::value);
    static_assert(is_container< std::array<int, 10> >::value);
    static_assert(is_container< std::list<int> >::value);
    static_assert(!is_container< foo >::value);

    static_assert(!is_iterator<int>::value);
    static_assert(is_iterator<int*>::value); // <--- warning!
    static_assert(is_iterator< std::vector<int>::iterator >::value);
    static_assert(is_iterator< std::array<int, 10>::iterator >::value);
    static_assert(is_iterator< std::list<int>::iterator >::value);

    return 0;
}