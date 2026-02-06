#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll sequential_sum(const vector<ll>& arr, int s, int e) {
    ll store = 0;
    for (int i = s; i <= e; i++)  {
        store += arr[i];
    }
    return store;
}

ll parallel_sum(const vector<ll>& arr, int s, int e) {
    if (e - s + 1 <= 100000) return sequential_sum(arr, s, e);
    int m = (s + e) >> 1;
    auto right = async(launch::async, parallel_sum, ref(arr), m + 1, e);
    ll left = parallel_sum(arr, s, m);
    return left + right.get();
}

int main() {
    vector<ll> arr(1000000, 1);
    for (int i = 0; i < arr.size(); i++) arr[i] = i;

    auto s1 = chrono::high_resolution_clock::now();
    ll res1 = sequential_sum(arr, 0, arr.size() - 1);
    auto e1 = chrono::high_resolution_clock::now();
    chrono::duration<double> t1 = e1 - s1;
    cout << "Ans: " << res1 << ", Time taken: " << t1.count() << endl;

    auto s2 = chrono::high_resolution_clock::now();
    ll res2 = parallel_sum(arr, 0, arr.size() - 1);
    auto e2 = chrono::high_resolution_clock::now();
    chrono::duration<double> t2 = e2 - s2;
    cout << "Ans: " << res2 << ", Time taken: " << t2.count() << endl;
}