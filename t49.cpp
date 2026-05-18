#include <future>
#include <print>
#include <vector>
using namespace std;

int f(int x) {
    this_thread::sleep_for(2s);
    return x;
}

long long parallel_sum(const vector<int>& arr) {
    const int NUM_TASKS = 4;
    vector<future<long long>> store;
    const int sz = arr.size() / NUM_TASKS;
    for (int i = 0; i < NUM_TASKS; i++) {
        store.emplace_back(
            async([&arr, i, NUM_TASKS, sz] () {
                long long sum = 0;
                for (int idx = sz * i; idx < ((i == NUM_TASKS - 1) ? arr.size() : (i + 1) * sz); idx++) sum += arr[idx];
                return sum;
            })
        );
    }

    long long res = 0;
    for (auto& fut : store) {
        long long ans = fut.get();
        println("{}", ans);
        res += ans;
    }
    return res;
}

int main() {
    vector<int> arr(9999999, 1);
    println("{}", parallel_sum(arr));
}