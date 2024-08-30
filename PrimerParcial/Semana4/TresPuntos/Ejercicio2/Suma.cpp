#include <iostream>

template<typename T>
T sum(T t) {
    return t;
}

template<typename T, typename... Args>
T sum(T t, Args... args) {
    return t + sum(args...);
}

int main() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum(1.1, 2.2, 3.3) << std::endl;
    return 0;
}
