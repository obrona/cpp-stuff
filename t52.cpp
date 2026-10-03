#include <bits/stdc++.h>
using namespace std;

int main() {
    auto f = [x = 0] () mutable { cout << x++ << endl; };
    auto& g = f;
    f();
    f();
    g();
}