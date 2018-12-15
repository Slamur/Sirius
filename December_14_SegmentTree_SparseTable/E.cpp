#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

class SegmentTree {

public:

    int size;
    vector<ll> t;
    vector<ll> lazy;
    vector<int> len;

    SegmentTree(int n)
            : size(n)
            , t(size << 2, 0)
            , lazy(size << 2, 0)
            , len(size << 2, 0)
    { }

    ll get_vertex(int v) {
        return t[v] + lazy[v] * len[v];
    }

    void push_vertex(int v, int vL, int vR) {
        if (lazy[v] != 0) {
            lazy[vL] += lazy[v];
            lazy[vR] += lazy[v];

            lazy[v] = 0;
        }
    }

    void update_vertex(int v, int vL, int vR) {
        t[v] = get_vertex(vL) + get_vertex(vR);
    }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = a[l];
            lazy[v] = 0;
            len[v] = 1;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            build_tree(vL, l, m);
            build_tree(vR, m, r);

            len[v] = len[vL] + len[vR];
            t[v] = t[vL] + t[vR];
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
            lazy[v] += delta;
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
            res += get_vertex(v);
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
    int n;
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