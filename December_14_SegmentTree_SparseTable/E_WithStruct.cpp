#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

struct Vertex {
    ll value;

    ll lazy;
    int length;

    ll get() {
        return value + lazy * length;
    }
};

class SegmentTree {

public:

    size_t size;
    vector<Vertex> t;

    SegmentTree(size_t n)
            : size(n)
            , t(size << 2, { 0, 0, 0 })
    { }

    void push_vertex(int v, int vL, int vR) {
        t[vL].lazy += t[v].lazy;
        t[vR].lazy += t[v].lazy;
        t[v].lazy = 0;
    }

    void update_vertex(int v, int vL, int vR) {
        t[v].value = t[vL].get() + t[vR].get();
    }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = { a[l], 0, 1 };
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            build_tree(vL, l, m);
            build_tree(vR, m, r);

            t[v] = { t[vL].value + t[vR].value, 0, t[vL].length + t[vR].length };
        }
    }

    int start, end;
    int delta;

    void update_segment(int _start, int _end, int _delta) {
        start = _start;
        end = _end + 1;
        delta = _delta;

        update_tree(1, 0, size);
    }

    void update_tree(int v, int l, int r) {
        if (start <= l && r <= end) {
            t[v].lazy += delta;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            push_vertex(v, vL, vR);

            if (start < m) update_tree(vL, l, m);
            if (m < end) update_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    ll res;

    ll get_segment(int _start, int _end) {
        start = _start;
        end = _end + 1;

        res = 0;

        get_tree_segment(1, 0, size);

        return res;
    }

    void get_tree_segment(int v, int l, int r) {
        if (start <= l && r <= end) {
            res += t[v].get();
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            push_vertex(v, vL, vR);

            if (start < m) get_tree_segment(vL, l, m);
            if (m < end) get_tree_segment(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }
};

int main(){
    size_t n;
    cin >> n;

    vector<int> a(n);

    SegmentTree tree(n);
    tree.build(a);

    int m;
    cin >> m;

    while (m --> 0) {
        int type;
        cin >> type;
        int x, y;
        cin >> x >> y;
        --y;

        if (type == 1) {
            int delta;
            cin >> delta;
            tree.update_segment(x, y, delta);
        } else {
            ll answer = tree.get_segment(x, y);
            cout << answer << '\n';
        }
    }

    cout << endl;

    return 0;
}