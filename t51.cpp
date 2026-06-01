#include <bits/stdc++.h>
using namespace std;


int main() {

    vector<int> v{1,2,3};

    auto view = v | views::filter([] (int x) { return x > 1; });

    static_assert(std::ranges::forward_range<decltype(view)>);
    
    for (int x : view) cout << x << " "; cout << endl;
    for (int x : view) cout << x << " "; cout << endl;
}



