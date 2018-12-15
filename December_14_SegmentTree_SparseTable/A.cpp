#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

class SegmentTree {

public:

    int size;
    vector<ll> t;

    SegmentTree(int n)
            : size(n)
            , t(size << 2)
    { }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
    }

    void update_vertex(int v, int vL, int vR) {
        t[v] = t[vL] + t[vR];
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            build_tree(vL, l, m);
            build_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    int index, value;
    void update_index(int _index, int _value) {
        index = _index;
        value = _value;
        update_tree(1, 0, size);
    }

    void update_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = value;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            if (index < m) update_tree(vL, l, m);
            else update_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    int start, end;
    ll res;

    ll get_sum_segment(int _start, int _end) {
        start = _start;
        end = _end + 1;
        res = 0;
        get_tree_segment(1, 0, size);
        return res;
    }

    void get_tree_segment(int v, int l, int r) {
        if (start <= l && r <= end) {
            res += t[v];
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            if (start < m) get_tree_segment(vL, l, m);
            if (m < end) get_tree_segment(vR, m, r);
        }
    }
};

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    SegmentTree tree(n);
    tree.build(a);

    int m;
    cin >> m;

    while (m --> 0) {
        char type;
        int x, y;
        cin >> type >> x >> y;

        if (type == 'u') {
            --x;
            tree.update_index(x, y);
        } else {
            --x, --y;

            ll answer = tree.get_sum_segment(x, y);
            cout << answer << ' ';
        }
    }

    cout << endl;

    return 0;
}