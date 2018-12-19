#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

template <class T>
vector<int> compress(vector<T> values) {
    vector<T> sorted = values; // copying
    sort(sorted.begin(), sorted.end());
    sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());

    vector<int> result(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result[i] = lower_bound(sorted.begin(), sorted.end(), values[i]) - sorted.begin();
    }

    return result;
}

class SegmentTree {

public:

    size_t size;
    vector<int> t;

    SegmentTree(size_t n)
            : size(n)
            , t(size << 2, 0)
    { }

    void update_vertex(int v, int vL, int vR) {
        t[v] = max(t[vL], t[vR]);
    }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
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

    int index;
    int delta;

    void update_index(int _index, int _delta) {
        index = _index;
        delta = _delta;

        update_tree(1, 0, size);
    }

    void update_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] -= delta;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            if (index < m) update_tree(vL, l, m);
            else update_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    int value;
    int res;

    int get_index(int _value) {
        value = _value;

        res = -2;

        if (value <= t[1]) {
            get_tree_segment(1, 0, size);
        }

        return res;
    }

    void get_tree_segment(int v, int l, int r) {
        if (l + 1 == r) {
            res = l;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            if (value <= t[vL]) get_tree_segment(vL, l, m);
            else get_tree_segment(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }
};



int main(){
    size_t h, w;
    size_t n;

    cin >> h >> w >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }


    h = min(n, h);

    SegmentTree tree(h);

    vector<int> desk(h, w);
    tree.build(desk);

    vector<int> answers(n);

    for (int i = 0; i < n; ++i) {
        int value = a[i];
        int row = answers[i] = tree.get_index(value);
        if (row != -2) {
            tree.update_index(row, value);
        }
    }

    for (int answer : answers) {
        cout << (answer + 1) << '\n';
    }
    cout << endl;

    return 0;
}