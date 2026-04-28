#include <bits/stdc++.h>
using namespace std;

void f(int& x) { x++; }

void g(int& x) { x++; }

int main() {
    int x = 0;
    {
        jthread(f, ref(x));
        jthread(g, x);
    }
    cout << x << endl;
}