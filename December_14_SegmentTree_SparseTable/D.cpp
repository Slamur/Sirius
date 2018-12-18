#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

class SegmentTree {

public:

    size_t size;
    vector<int> t;

    SegmentTree(size_t n)
            : size(n)
            , t(size << 2, 0)
    { }

    void update_vertex(int v, int vL, int vR) {
        t[v] = t[vL] + t[vR];
    }

    void build() {
        build_tree(1, 0, size);
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = 0;
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            build_tree(vL, l, m);
            build_tree(vR, m, r);

            t[v] = 0;
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
            t[v] += delta;
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

    ll get_segment(int _start, int _end) {
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

            update_vertex(v, vL, vR);
        }
    }
};

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

int main(){
    size_t n;
    ll length;

    cin >> n >> length;

    vector<ll> times(n);
    for (int i = 0; i < n; ++i){
        ll timeUnit;
        cin >> timeUnit;

        times[i] = i + length * timeUnit;
    }

    vector<int> a = compress(times);

    SegmentTree tree(n);
    tree.build();

    ll answer = 0;

    for (int i = n - 1; i >= 0; --i) {
        int value = a[i];
        answer += tree.get_segment(0, value - 1);
        tree.update_index(a[i], 1);
    }

    cout << answer << endl;

    return 0;
}