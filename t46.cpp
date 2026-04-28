#include <bits/stdc++.h>
using namespace std;

auto cmp = [] (int a, int b)  { return a > b; };

int main() {
    set<int, function<bool(int, int)>> st(cmp);
    st.insert(5);
    st.insert(6);
    st.insert(4);

    for (int x : st) cout << x <<  ' ';
    cout << endl;
}