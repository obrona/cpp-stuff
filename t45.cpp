#include <bits/stdc++.h>
using namespace std;

template<typename T, typename R, typename Transform, typename Combine>
struct SegTree {
    Transform transform;
    Combine combine;
    int len;
    vector<R> tree;

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    SegTree(const vector<T>& arr): len(arr.size()), tree(4 * len, T()) {
        build(arr);
    }

    void build(const vector<T>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = arr.size();
        if (s == e) {
            tree[p] = transform(arr[s]);
            return;
        }
        int m = mid(s, e);
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = combine(tree[left(p)], tree[right(p)]);
    }

    R query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            return tree[p];
        }

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, left(p), s, m); 
        } else if (l > m) {
            return query(l, r, right(p), m + 1, e);
        } else {
            R lres = query(l, m, left(p), s, m), rres = query(m + 1, r, right(p), m + 1, e);
            return combine(lres, rres);
        }
    }
};

void test()  {
    struct Identity {
        int operator()(int x) { return x; }
    };

    struct Sum {
        int operator()(int x, int y) { return x + y; }
    };

    vector<int> arr = {3,1,2,5,4,1,2};
    SegTree<int, int, Identity, Sum> st(arr);
    assert(st.query(0, 2) == 6);
    assert(st.query(3, 6) == 12);
}

int main() {
    test();
}