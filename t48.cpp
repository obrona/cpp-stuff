#include <print>
using namespace std;

template <typename T>
T add(T val) {
    return val;
}

template <typename T, typename... Ts>
T add(T val, Ts... rest) {
    return val + add(rest...);
}

template <typename... Ts>
auto add2(Ts... rest) {
    return (... + rest);
}

template <typename F, typename G>
auto compose(F f, G g) {
    return [=] (auto x) { return f(g(x)); };
}

template <typename F, typename... Fs>
auto compose(F f, Fs... fs) {
    return [=] (auto x) { return f(compose(fs...)(x)); };
}

template <typename F, typename G>
auto operator*(F f, G g) {
    return [=] (auto x) { return f(g(x)); };
}

// the other version with the parameter pack (like in compose) is not needed.

int main() {
    //println("{}", add(1, 2, 3, 4, 5));
    //println("{}", add("hello"s, " "s, "world"s));
    //println("{}", add2(2, 3, 4));

    auto f1 = [] (int x) { println("f1"); return 2 * x; };
    auto f2 = [] (int x) { println("f2"); return x + 1; };
    auto f3 = [] (int x) { println("f3"); return x * x; };

    //println("{}", compose(f1, f2, f3)(2));

    // this is processed as (f1 * f2) * f3
    println("{}", (f1 * f2 * f3)(2));
}