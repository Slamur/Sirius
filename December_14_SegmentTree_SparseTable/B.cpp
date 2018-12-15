#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

class SegmentTree {

public:

    int size;
    vector<ll> t;
    vector<ll> delta;

    SegmentTree(int n)
            : size(n)
            , tv(size << 2)
            , ti(size << 2)
    { }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
    }


    void update_vertex(int v, int vL, int vR) {
        int vBest= (tv[vL] >= tv[vR]) ? vL : vR;
        tv[v] = tv[vBest];
        ti[v] = ti[vBest];
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            tv[v] = a[l];
            ti[v] = l;
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
            tv[v] = value;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            if (index < m) update_tree(vL, l, m);
            else update_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    int start, end;

    int resIndex;
    ll resValue;

    int get_segment(int _start, int _end) {
        start = _start;
        end = _end + 1;

        resValue = -1;
        resIndex = -1;

        get_tree_segment(1, 0, size);

        return resIndex;
    }

    void get_tree_segment(int v, int l, int r) {
        if (start <= l && r <= end) {
            ll tValue = tv[v];
            int tIndex = ti[v];
            if (resValue < tValue) {
                resValue = tValue;
                resIndex = tIndex;
            }
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
        int x, y;
        cin >> x >> y;

        --x, --y;

        int answer = tree.get_segment(x, y);
        cout << answer + 1 << ' ';
    }

    cout << endl;

    return 0;
}