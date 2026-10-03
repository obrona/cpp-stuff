#include <generator>
#include <ranges>
#include <iostream>
#include <vector>
#include <optional>
#include <print>

std::generator<int> count_up(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;          // suspend, give i to the caller
    }
}

std::generator<int> f(int n) {
    co_yield n;
    if (n > 0) {
        co_yield std::ranges::elements_of(f(n - 1));
    }
}

std::generator<std::vector<int>> permutations(std::vector<int> arr, std::vector<int> front = {}) {
    if (arr.size() == 0) {
        co_yield front;
        co_return;
    }

    for (int i = 0; i < arr.size(); i++) {
        std::vector<int> left;
        left.insert(left.end(), arr.begin(), arr.begin() + i);
        left.insert(left.end(), arr.begin() + i + 1, arr.end());

        std::vector<int> my_front = front;
        my_front.push_back(arr[i]);
        co_yield std::ranges::elements_of(permutations(left, my_front));
    }
}

void print_arr(std::vector<int> arr) {
    std::string out = "[";
    for (int x : arr) out += std::to_string(x) + ' ';
    out.pop_back();
    out.push_back(']');
    std::println("{}", out);
}

int main() {
    for (auto v : permutations({1,2,3,4,5})) print_arr(v);
}