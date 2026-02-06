#include <bits/stdc++.h>
using namespace std;

struct A {
    A() {
        cout << "I am constructed" << endl;
    }

    ~A() {
        cout << "I am destroyed" << endl;
    }
};

mutex m;

int f() {
    unique_lock lk(m);
    throw logic_error("illogical");
    return 0;
}

int g() {
    m.lock();
    cout << "g enters" << endl;
    m.unlock();
    return 0;
}

int main() {
    try {
        f();
    } catch (exception& e) {}
    g(); 
};

