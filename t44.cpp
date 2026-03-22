#include <bits/stdc++.h>
using namespace std;

template <typename T, typename R>
struct SegTree {
    int len;
    vector<T> tree;
    R reducer;

    SegTree(int len): SegTree(len, R()) {}
    
    SegTree(int len, R reducer): len(len), tree(4 * len, T()), reducer(reducer) {}

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    void update_point(int i, T val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = reducer(tree[p], val); // we need to 'add'
            return;
        }
        int m = mid(s, e);
        if (i <= m) {
            update_point(i, val, left(p), s, m);
        } else {
            update_point(i, val, right(p), m + 1, e);
        }
        tree[p] = reducer(tree[left(p)], tree[right(p)]);
    }

    T range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            return tree[p];
        }
        int m = mid(s, e);
        if (r <= m) {
            return range_query(l, r, left(p), s, m);
        } else if (l > m) {
            return range_query(l, r, right(p), m + 1, e);
        } else {
            return reducer(range_query(l, m, left(p), s, m), range_query(m + 1, r, right(p), m + 1, e));
        }
    }
};

void test_seg_tree() {
    auto sum = [](int x, int y) {return x + y;};
    SegTree<int, decltype(sum)> st(10, sum);
    st.update_point(1, 10);
    st.update_point(3, 20);
    assert(st.range_query(3, 3) == 20);
    st.update_point(3, 30);
    assert(st.range_query(0, 6) == 40);
    assert(st.range_query(1, 4) == 40);
}